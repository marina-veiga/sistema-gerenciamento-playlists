#ifndef MUSICA_H
#define MUSICA_H    

#define MAX_NOME 100
#define MAX_ARTISTA 50
#define MAX_GENERO 30
#define MAX_EXTRA 20

// Union para Informações Adicionais
typedef union {
    int anoLancamento;
    int numeroAlbum;
} InfoExtra;

// Struct – Música
typedef struct {
    char titulo[MAX_NOME];
    char artista[MAX_ARTISTA];
    int duracao;              // em segundos
    char genero[MAX_GENERO];
    char extra[MAX_EXTRA];    // usado no CSV
    InfoExtra info;
} Musica;

// Declaração antecipada de Playlist
struct Playlist;
typedef struct Playlist Playlist;

// Funções exigidas no PDF
void exibirMusica(Musica m);
int buscarMusicaPorTitulo(Playlist *p, char *titulo);
int buscarMusicaPorArtista(Playlist *p, char *artista);
void ordenarMusicasPorTitulo(Playlist *p);
void ordenarMusicasPorDuracao(Playlist *p);

#endif
