#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "musica.h"

#define MAX_PLAYLIST 50 // Quantas playlist o sistema aguenta 
#define CAPACIDADE_INICIAL 50

typedef struct Playlist{
    char nome[MAX_NOME];
    int *idsMusicas; // Ids das músicas do catálogo
    int quantidade; // Quantas musicas tem na playlist
    int capacidade; // Tamanho atual da array alocado
    int duracaoTotal; // em segundos
}Playlist;

struct Playlist;
//funções do modulo
void criarPlaylist(Playlist *ptrPLay, char *nomePlay);
void adicionarMusicaPlaylist(Playlist *ptrPlay,int idMusica, Musica *catalogo, int qtdMusicas);
void listarPlaylists(Playlist *ptrListaPlay, int total);
void liberarPlaylists(Playlist *p, int total);
void adicionarMusicaPlaylist(Playlist *ptrPlay, int idMusica, Musica *catalogo, int qtdMusicas);
void removerMusicaPlaylist(Playlist *ptrPlay, int idMusica);

#endif
