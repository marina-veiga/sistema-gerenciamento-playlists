#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "playlist.h"

#define MaxLinhas 1000 //macro do máximo de linhas pra ler no arquivo

//carrega todas as musicas do arquivo csv para o programa
int carregarMusicas(Musica **catalogo) {

    FILE *arq;
    
    arq = fopen("data/musicas.csv", "r");

    //verifica se o arquivo não foi aberto corretamente
    if (!arq) {
        printf("Erro ao abrir musicas.csv\n");
        return 0; //nenhuma música foi carregada
    }

    int capacidade = 50; //capacidade inicial do vetor de músicas

    int total = 0;   //controla quantas músicas já foram lidas

    
    //alocação dinamica na memória reservando espaço para 50 estruturas do tipo Musica
    *catalogo = malloc(sizeof(Musica) * capacidade);

    char linha[256]; 
    fgets(linha, sizeof(linha), arq);  //lê e descarta a primeira linha (cabeçalho)


    //loop que lê o arquivo linha por linha
    while (fscanf(arq,"%d,%[^,],%[^,],%d,%[^,],%d\n", 
        &(*catalogo)[total].id, 
        (*catalogo)[total].titulo,  
        (*catalogo)[total].artista,
        &(*catalogo)[total].duracao,
        (*catalogo)[total].genero,
        &(*catalogo)[total].info.anoLancamento) == 6) { //lê 6 campos por linha
        
        int valorLido = (*catalogo)[total].info.anoLancamento;

        //decide se é ano ou volume automaticamente
        if (valorLido > 1900) {
            (*catalogo)[total].info.anoLancamento = valorLido;
            (*catalogo)[total].tipoInfo = 1; // 1 = ano
        } else {
            (*catalogo)[total].info.volumeAlbum = valorLido;
            (*catalogo)[total].tipoInfo = 2; // 2 = volume
        }

        total++; //incrementa contador de músicas

        //verifica se o vetor chegou ao limite da capacidade
        if (total == capacidade) {

            //dobra a capacidade do vetor
            capacidade *= 2;

            //realoca a memória para suportar mais músicas
            Musica *temp = realloc(*catalogo, sizeof(Musica) * capacidade);
            if (temp==NULL) { 
                printf("Erro de realocação\n"); 
                free(*catalogo);
                fclose(arq);
                return 0;
            }
            *catalogo = temp;
        }
    }

    //fecha o arquivo após terminar a leitura
    fclose(arq);

    //retorna a quantidade total de músicas carregadas
    return total;
}

//salvar no arquivo as playlists criadas ou modificadas pelo usuário
int salvarPlaylists(Playlist *playlists, int quantidade,Musica *catalogo) {

    FILE *arq;

    // abre o arquivo para escrita 
    arq = fopen("data/playlists.csv", "w");

    if (arq == NULL) {
        printf("Erro ao abrir playlists.csv para escrita\n");
        return 0; // erro ao abrir
    }

    //percorre todas as playlists
    for (int i = 0; i < quantidade; i++) {
        fprintf(arq, "%s;%d", playlists[i].nome, playlists[i].quantidade);

        // percorre todas as músicas da playlist atual
        for (int j = 0; j < playlists[i].quantidade; j++) {
            int id = playlists[i].idsMusicas[j];     //pega o id da musica
            fprintf(arq, ";%s", catalogo[id].titulo); // escreve o titulo da musica
        }
        fprintf(arq, "\n");
    }

    // fecha o arquivo
    fclose(arq);

    return 1; // salvou com sucesso
}

//carrega todas as playlists do arquivo CSV e retorna o total de playlists carregadas
int carregarPlaylists(Playlist **playlists) {
    FILE *arquivo; 
    
    arquivo = fopen("data/playlists.csv", "r");
    if (arquivo == NULL){
        printf("Arquivo nao encontrado!\n");
        return 0;
    }

    char linha[1024];   // buffer para ler cada linha do arquivo
    int totalPlaylists = 0; //contador de playlists lidas

    // lê linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        // remove o '\n'
        linha[strcspn(linha, "\n")] = '\0';

        // aloca ou realoca o vetor de playlists
        if (*playlists == NULL) { //se ainda não existe nenhuma playlist
            *playlists = malloc(sizeof(Playlist));
            if (*playlists == NULL) {
                printf("Erro de alocacao de memoria\n");
                fclose(arquivo);
                return 0;
            }
        } else { //se já existe
            Playlist *temp = realloc(*playlists, sizeof(Playlist) * (totalPlaylists + 1));
            if (temp == NULL) {
                printf("Erro de realocacao de memoria\n");
                fclose(arquivo);
                return 0;
            }
            *playlists = temp;      
        }

        // separa cada parte da linha usando strtok
        char *nomePlaylistStr = strtok(linha, ";"); //nome da playlist
        char *qtdMusicasStr = strtok(NULL, ";");  //quantidade de músicas

        // copia o nome da playlist
        strcpy((*playlists)[totalPlaylists].nome, nomePlaylistStr);

        // quantidade de músicas
        int qtdMusicas = atoi(qtdMusicasStr); //converte quantidade para inteiro
        (*playlists)[totalPlaylists].quantidade = qtdMusicas;

        //define a capacidade inicial do vetor de IDs de músicas
        if (qtdMusicas > CAPACIDADE_INICIAL) {
            (*playlists)[totalPlaylists].capacidade = qtdMusicas;  //se a quantidade for maior que a capacidade inicial, usa qtdMusicas
        } else {
            (*playlists)[totalPlaylists].capacidade = CAPACIDADE_INICIAL; //caso nao, usa a capacidade inical
        }


        // aloca espaço para os IDs das músicas
        (*playlists)[totalPlaylists].idsMusicas = malloc(sizeof(int) * (*playlists)[totalPlaylists].capacidade);
        if ((*playlists)[totalPlaylists].idsMusicas == NULL) {
            printf("Erro de alocacao de memoria para idsMusicas\n");
            fclose(arquivo);
            return 0;
        }

        // preenche os IDs das músicas
        for (int i = 0; i < qtdMusicas; i++) {
            char *idMusicaStr = strtok(NULL, ";"); //pega próximo campo
            if (idMusicaStr != NULL) {
                (*playlists)[totalPlaylists].idsMusicas[i] = atoi(idMusicaStr); //converte para inteiro
            } else {
                (*playlists)[totalPlaylists].idsMusicas[i] = -1; //se não tiver, coloca -1 (vazio)

            }
        }

        totalPlaylists++; //incrementa contador de playlists
    }

    // fecha o arquivo
    fclose(arquivo);

    return totalPlaylists;
}