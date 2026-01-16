#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "musica.h"

#define MAX_PLAYLIST 50 // Quantas playlist o sistema aguenta 
#define CAPACIDADE_INICIAL 50

typedef struct 
{
    char nome[MAX_NOME];
    Musica *musicas; // Ponteiro para a array dinãmico
    int quantidade; // Quantas musicas tem na playlist
    int capacidade; // Tamanho atual da array alocado
    int duracaoTotal; // em segundos
    /* data */
}Playlist;

//funções do modulo
void criarPlaylist(Playlist *ptrPLay, char *nomePlay);
void adicionarMusicaPlaylist(Playlist *ptrPlay);
void listarPlaylists(Playlist *ptrListaPlay, int total);

#endif
