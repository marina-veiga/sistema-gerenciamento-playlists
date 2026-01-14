#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "playlist.h"

#define MaxLinhas 1000 //macro do máximo de linhas pra ler no arquivo

//carrega as playlists já salvas no arquivo para a memória do programa
int carregarPlaylists(const char *nomeArquivo, Playlist *playlists, int *quantidade){ 
    FILE *arq;

    arq = fopen(nomeArquivo, "r"); //abrir o arquivo pra leitura

    if(arq == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0; //erro ao abrir
    }
    char linha[MaxLinhas];
    int contador = 0; //contar quantas playlists foram lidas

    

    // lê a primeira linha (cabeçalho) e descarta
    fgets(linha, sizeof(linha), arq);

    while(fgets(linha,sizeof(linha),arq)){ //lê cada linha do arquivo
        // remove o '\n' do final da linha
        linha[strcspn(linha, "\n")] = '\0';

        //separar campos: nomePlaylist, titulo, artista, duracao, genero, extra
        char *nomePlaylist = strtok(linha, ",");
        char *titulo = strtok(NULL, ",");
        char *artista = strtok(NULL, ",");
        char *duracaoStr = strtok(NULL, ",");
        char *genero = strtok(NULL, ",");
        char *extra = strtok(NULL, ",");

        //ignora linhas inválidas
        if (nomePlaylist == NULL || titulo == NULL || artista == NULL || duracaoStr == NULL) {
            continue; // ignora essa linha e passa para a próxima
        }

        int duracao = atoi(duracaoStr); //converte a string da duração em número inteiro

        //percorre as playlists já carregadas para ver se a playlist atual já existe
        int indexPlaylist = -1; //significa ainda não achou

        for (int i = 0; i < contador; i++){
            if (strcmp(playlists[i].nome, nomePlaylist) == 0){  //se o nome da playlist do arquivo for igual a uma playlist que já está na memória
                indexPlaylist = i; // salva o índice dessa playlist
                break;
            }
        }

        //se a playlist não foi encontrada, cria uma nova posição no array
        if (indexPlaylist == -1){
            indexPlaylist = contador; //usa a próxima posição livre do array de playlists
            strcpy(playlists[indexPlaylist].nome, nomePlaylist); //copia o nome da playlist
            playlists[indexPlaylist].numMusicas = 0; //começa sem músicas
            playlists[indexPlaylist].duracaoTotal = 0; // uração total começa em 0
            contador++;
        }

        //adicionar a música na playlist
        int posMusic = playlists[indexPlaylist].numMusicas; //posição da nova música
        strcpy(playlists[indexPlaylist].musicas[posMusic].titulo, titulo); //copia o título
        strcpy(playlists[indexPlaylist].musicas[posMusic].artista, artista); //copia o artista
        playlists[indexPlaylist].musicas[posMusic].duracao = duracao; // coloca a duração

        strcpy(playlists[indexPlaylist].musicas[posMusic].genero, genero); //copia o gênero
        strcpy(playlists[indexPlaylist].musicas[posMusic].extra, extra); //copia o extra (ano ou volume)
    
        // atualiza o número de músicas e a duração total da playlist
        playlists[indexPlaylist].numMusicas++; //aumentamos o contador de músicas
        playlists[indexPlaylist].duracaoTotal += duracao; //somamos a duração da nova música
    }
    fclose(arq); // fecha o arquivo

    *quantidade = contador;  //atualiza quantidade de playlists carregadas

    return 1; 

}   

//salvar no arquivo as playlists criadas ou modificadas pelo usuário
int salvarPlaylists(const char *nomeArquivo, Playlist *playlists, int quantidade);