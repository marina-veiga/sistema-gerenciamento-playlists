//Nalu

#ifndef MUSICA_H
#define MUSICA_H

#define MAX_NOME 100
#define MAX_ARTISTA 50
#define MAX_GENERO 30

// Declaração forward para Playlist
typedef struct Playlist Playlist;

// Union InfoExtra
typedef union InfoExtra {
    int anoLancamento;
    int numeroAlbum;
} InfoExtra;

// Struct Musica
typedef struct Musica {
    char titulo[MAX_NOME];
    char artista[MAX_ARTISTA];
    int duracao; // Em segundos
    char genero[MAX_GENERO];
    InfoExtra info;
} Musica;

// Protótipos
void exibirMusica(Musica m);
int buscarMusicaPorTitulo(Playlist *p, char *titulo);
int buscarMusicaPorArtista(Playlist *p, char *artista);
void ordenarMusicasPorTitulo(Playlist *p);
void ordenarMusicasPorDuracao(Playlist *p);

#endif // MUSICA_H
