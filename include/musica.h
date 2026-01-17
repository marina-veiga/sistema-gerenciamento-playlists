#ifndef MUSICA_H
#define MUSICA_H

#define MAX_NOME 100
#define MAX_GENERO 50

// Forward declaration para resolver o problema de dependência circular
struct Playlist;

// Union para Informações Adicionais
typedef union {
    int anoLancamento;
    int volumeAlbum;
} InfoExtra;

// Struct – Música
typedef struct {
    int id;
    char titulo[MAX_NOME];
    char artista[MAX_NOME];
    int duracao;              // em segundos
    char genero[MAX_GENERO];
    InfoExtra info;
    int tipoInfo;
} Musica;


// Exibe os dados completos de uma música
void exibirMusica(Musica m);

// Busca uma música pelo título no catálogo
int buscarMusicaPorTitulo(Musica *catalogo, int qtdMusicas, char *titulo);

// Busca uma música pelo artista (substring)
int buscarMusicaPorArtista(Musica *catalogo, int qtdMusicas, char *artista);

// Ordena o catálogo de músicas por título (ordem alfabética)
void ordenarMusicasPorTitulo(Musica *catalogo, int qtdMusicas);

// Ordena o catálogo de músicas por duração (crescente)
void ordenarMusicasPorDuracao(Musica *catalogo, int qtdMusicas);

// Exibe todas as músicas de uma playlist usando o catálogo
void exibirTodasMusicasDaPlaylist(struct Playlist *playlist, Musica *catalogo, int qtdMusicas);
#endif
