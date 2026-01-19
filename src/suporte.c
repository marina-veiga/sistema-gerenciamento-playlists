#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suporte.h"
#include "playlist.h"
#include "musica.h"
#include "dados.h"

//limpar o buffer de entrada 
void limparBuffer(){
    int caractere; //armazena cada caractere lido do buffer

    // lê o primeiro caractere do buffer
    caractere = getchar(); 

    //enquanto o caractere lido não for '\n' (enter) e não for fim do arquivo(EOF), continua limpando o buffer
    while (caractere!= '\n' && caractere != EOF){
        caractere = getchar(); 
        
    }
}

//verifica se o valor informado pelo usuário é válido
int validaInteiro(int valor, int min, int max){
    int auxValor = valor; // cópia do valor recebido

    // enquanto o valor estiver fora do intervalo, pede novo valor
    while(auxValor < min || auxValor > max){
        printf("Valor invalido! Informe um valor entre %d e %d: ", min, max);
        scanf("%d",&auxValor);
        limparBuffer();
        
    }

    // quando sair do loop, retorna o valor válido
    return auxValor;

}

//verifica se uma substring esta contida em outra string 
//retorna 1 se encontrar a substring, 0 caso contrário
int contemSubstring(const char *str, const char *substr){
    const char *ptrAux = str; //ponteiro para percorrer a string maior

    //loop que percorre a string maior
    while(*ptrAux != '\0'){
        const char *ptrTemp = ptrAux; //ponteiro temporário começando na posição atual da string maior
        const char *ptrAuxSub= substr; //ponteiro aux para a substring

        //loop que compara todos os caracteres da substring com a string maior
        while(*ptrTemp != '\0' && *ptrAuxSub != '\0' && *ptrTemp == *ptrAuxSub){
            ptrTemp++;
            ptrAuxSub++;
        }

        // se chegar ao final da substring, todos os caracteres coincidiram
        if(*ptrAuxSub == '\0'){
            return 1; //substring encontrada
        }

        ptrAux++; // avança na string maior para o próximo caractere
    }
    
    return 0; //se percorreu toda a string maior e não encontrou a substring completa, significa que a substring não está contida nela
}

//converte de segundos para minutos e segundos 
void segundosParaMinutos(int totalSegundos, int *min, int *seg){
    int minutos = totalSegundos/ 60; //calcula minutos completos
    int segundos = totalSegundos % 60; //calcula os segundos restantes

    *min = minutos;  //armazena os minutos no ponteiro min
    *seg = segundos; //armazena os segundo no ponteiro seg
}

int compararStrings(const char *str1, const char *str2){
    return strcmp(str1, str2); //compara duas strings, se forem iguais retorna 0
}

void paraMinusculo(char *str){
    int i = 0; 
    while (str[i] != '\0') { 
        //verifica se é letra maiúscula
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // converte para minúsculo
        }
        i++; //próximo caractere
    }
}

void menuPrincipal(Playlist **playlists, int *qtdPlaylists, Musica *catalogo, int qtdMusicas) {
    //carrega playlists do arquivo no início
    *qtdPlaylists = carregarPlaylists(playlists);

    int opcao = -1; //opção escolhida pelo usuário no menu, inicializa com valor diferente de 0

    while (opcao != 0){ //enquanto o usuário não escolher sair 
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1 - Criar nova playlist\n");
        printf("2 - Listar playlists\n");
        printf("3 - Exibir musicas de uma playlist\n");
        printf("4 - Adicionar musica a uma playlist\n");
        printf("5 - Remover musica de uma playlist\n");
        printf("6 - Buscar musica por artista\n");
        printf("7 - Ordenar musicas por titulo\n");
        printf("8 - Ordenar musicas por duracao\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if(scanf("%d", &opcao) != 1){
        printf("Erro: Voce deve digitar apenas numeros!\n");
        limparBuffer(); // Remove o lixo (letras) que ficou no buffer
        opcao = -1;     // Reseta a opção para não sair do loop
        continue;       // Volta para o início do while

        }
        limparBuffer(); 

        opcao = validaInteiro(opcao, 0, 8);  //garante que a opção esteja no intervalo

        switch (opcao) { 

        case 1: { //criar nova playlist
            //verifica se ainda dá para criar mais playlists
            if (*qtdPlaylists >= MAX_PLAYLIST) {
                printf("Você atingiu o limite de playlists!\n");
                break; 
            }

            char nome[MAX_NOME]; //guarda o nome da nova playlist
            printf("Digite o nome da playlist: ");
            fgets(nome, MAX_NOME, stdin);     
            nome[strcspn(nome, "\n")] = '\0';    //remove o '\n'

            //aloca ou realoca espaço para o vetor de playlists
            if (*playlists == NULL) {
                *playlists = malloc(sizeof(Playlist)); //se nao existir playlitis
            } else {
                *playlists = realloc(*playlists, sizeof(Playlist) * (*qtdPlaylists + 1)); //se ja existe pelo menos uma
            }

            //verifica se deu erro na alocação
            if (*playlists == NULL) {
                printf("Erro: memória insuficiente!\n");
                exit(1);
            }

            //pega o endereço da próxima posição disponível do vetor de playlists
            criarPlaylist(&(*playlists)[*qtdPlaylists], nome);

            //atualiza a quantidade de playlists
            *qtdPlaylists = *qtdPlaylists + 1;


            printf("Playlist '%s' criada com sucesso!\n", nome);

            break; 
        }
        case 2:{ //listar playlists
            listarPlaylists(*playlists, *qtdPlaylists);
            break;
        }
        case 3:{  //exibir músicas de uma playlist
            if (*qtdPlaylists == 0) { //verifica se existe playlists
            printf("Não há playlists criadas ainda!\n");
            break;
            }

            int indice;
            printf("Digite o indice da playlist (1 a %d): ", *qtdPlaylists);
            scanf("%d", &indice);
            limparBuffer();
            indice = indice - 1; // ajusta para índice do vetor

            if (indice < 0 || indice >= *qtdPlaylists) {
                printf("Indice invalido!\n");
                break;
            }

            //mostra todas as músicas da playlist escolhida
            exibirTodasMusicasDaPlaylist(&(*playlists)[indice], catalogo, qtdMusicas);

            break;
        }
        case 4:{//adicionar música a playlist
            if (*qtdPlaylists == 0) {
            printf("Não há playlists criadas ainda!\n");
            break;
            }

            int indice;
            printf("Digite o indice da playlist: ");
            scanf("%d", &indice);
            limparBuffer();
            indice= indice - 1;

            if (indice < 0 || indice >= *qtdPlaylists) {
                printf("Indice invalido!\n");
                break;
            }

            char titulo[100];  //variável para guardar o título da música
            printf("Digite o titulo da musica que deseja adicionar: ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            int idMusica = buscarMusicaPorTitulo(catalogo, qtdMusicas, titulo);
            if (idMusica == -1) {
                printf("Musica não encontrada no catálogo!\n");
            } else {
                adicionarMusicaPlaylist(&(*playlists)[indice], idMusica, catalogo, qtdMusicas);
                salvarPlaylists(*playlists, *qtdPlaylists, catalogo); //salva alterações
                printf("Musica adicionada com sucesso na playlist!\n");
            }

            break;
        }
        case 5:{ //remover música de uma playlist
            if (*qtdPlaylists == 0) {
            printf("Não há playlists criadas ainda!\n");
            break;
            }

            int indice;
            printf("Digite o indice da playlist: ");
            scanf("%d", &indice);
            limparBuffer();
            indice = indice - 1;

            if (indice < 0 || indice >= *qtdPlaylists) {
                printf("Indice invalido!\n");
            break;
            }

            char titulo[100]; //guarda título da música
            printf("Digite o titulo da musica que deseja remover: ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            int idMusica = buscarMusicaPorTitulo(catalogo, qtdMusicas, titulo);
            if (idMusica == -1) {
                printf("Musica não encontrada no catálogo!\n");
            } else {
                removerMusicaPlaylist(&(*playlists)[indice], idMusica);
                salvarPlaylists(*playlists, *qtdPlaylists, catalogo); //salva alterações
                printf("Musica removida com sucesso!\n");
            }
            break;
        } 
        case 6: { //buscar música por artista
            char artista[100]; //variavel para nome do artista
            printf("Digite o nome do artista: ");
            fgets(artista, sizeof(artista), stdin);
            artista[strcspn(artista, "\n")] = '\0'; // remove o '\n'

            int idMusica = buscarMusicaPorArtista(catalogo, qtdMusicas, artista);
            if (idMusica == -1) {
                printf("Nenhuma musica encontrada para o artista '%s'.\n", artista);
            } else {
            printf("Musica encontrada:\n");
            exibirMusica(catalogo[idMusica]); //mostra música
            }

            break;
        }
        case 7: { // Ordenar músicas por títul

            if (*qtdPlaylists == 0) {
                printf("Nao ha playlists criadas ainda!\n");
                break;
            }

            int indice;
            printf("Digite o indice da playlist (1 a %d): ", *qtdPlaylists);
            scanf("%d", &indice);
            limparBuffer();
            indice= indice - 1;

            if (indice < 0 || indice >= *qtdPlaylists) {
                printf("Indice invalido!\n");
            break;
            }

            ordenarMusicasPorTituloNaPlaylist(&(*playlists)[indice], catalogo);
            salvarPlaylists(*playlists, *qtdPlaylists, catalogo);
            printf("Playlist ordenada por titulo com sucesso!\n");
            break;
        }
        case 8:{ //ordenar músicas por duração
            if (*qtdPlaylists == 0) {
                printf("Nao ha playlists criadas ainda!\n");
                break;
            }

            int indice;
            printf("Digite o indice da playlist (1 a %d): ", *qtdPlaylists);
            scanf("%d", &indice);
            limparBuffer();
            indice= indice -1;

            if (indice < 0 || indice >= *qtdPlaylists) {
            printf("Indice invalido!\n");
            break;
            }

            ordenarMusicasPorDuracaoNaPlaylist(&(*playlists)[indice], catalogo);
            salvarPlaylists(*playlists, *qtdPlaylists, catalogo);
            printf("Playlist ordenada por duracao com sucesso!\n");
            break;
        }
        case 0: {  //sair do program
            printf("Saindo do programa...\n");
            break;
        }
        default:{ //caso o usuário digite número inválido
            printf("Opcao invalida!\n");
            }
        }

    }
}