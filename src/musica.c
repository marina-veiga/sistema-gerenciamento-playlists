/* MUSICA.C (implementação do módulo de músicas) */

/*Ele contém a lógica concreta das funções que lidam
diretamente com as operações sobre as músicas nas playlists*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // Para tolower()
#include "musica.h"
#include "playlist.h"  // Para ter a definição completa de Playlist
#include "suporte.h"

// FUNÇÔES PRINCIPAIS

void exibirMusica(Musica m) {
    int minutos, segundos;
    
    // Converte duração
    segundosParaMinutos(m.duracao, &minutos, &segundos);
    
    // Exibe os dados
    printf("\nEXBIR MUSICA:\n");
    printf("Titulo:   %s\n", m.titulo);
    printf("Artista:  %s\n", m.artista);
    printf("Duracao:  %02d:%02d\n", minutos, segundos);
    printf("Genero:   %s\n", m.genero);
    
    // InforExtra
    if (m.tipoInfo == 1) {
        printf("Ano de Lancamento: %d\n", m.info.anoLancamento);
    } else if (m.tipoInfo == 2) {
        printf("Volume do Album: %d\n", m.info.volumeAlbum);
    }
    printf("\n");
}

// função que busca música pelo título
int buscarMusicaPorTitulo(Musica *catalogo, int quantidade, char *titulo) {
    // remove o \n do final, se tiver
    titulo[strcspn(titulo, "\n")] = '\0';

    // cria uma cópia do título e coloca em minúsculas
    char tituloMinusculo[100];
    int i = 0;
    while (titulo[i] != '\0') {
        tituloMinusculo[i] = titulo[i];
        i++;
    }
    tituloMinusculo[i] = '\0';
    paraMinusculo(tituloMinusculo);

    // percorre todo o catálogo
    for (int j = 0; j < quantidade; j++) {
        // cria uma cópia do título do catálogo e coloca em minúsculas
        char catalogoMinusculo[100];
        i = 0;
        while (catalogo[j].titulo[i] != '\0') {
            catalogoMinusculo[i] = catalogo[j].titulo[i];
            i++;
        }
        catalogoMinusculo[i] = '\0';
        paraMinusculo(catalogoMinusculo);

        // compara as strings
        int igual = 1; // assume que são iguais
        i = 0;
        while (tituloMinusculo[i] != '\0' || catalogoMinusculo[i] != '\0') {
            if (tituloMinusculo[i] != catalogoMinusculo[i]) {
                igual = 0; // se algum caractere for diferente, não são iguais
                break;
            }
            i++;
        }

        if (igual == 1) {
            return j; // encontrou e retorna o índice
        }
    }

    return -1; // não encontrou
}

int buscarMusicaPorArtista(Musica *catalogo, int qtdMusicas, char *artista) {
    artista[strcspn(artista, "\n")] = '\0';

    char artistaMinusculo[100];
    strcpy(artistaMinusculo, artista);
    paraMinusculo(artistaMinusculo);

    for (int i = 0; i < qtdMusicas; i++) {
        char catalogoArtistaMinusculo[100];
        strcpy(catalogoArtistaMinusculo, catalogo[i].artista);
        paraMinusculo(catalogoArtistaMinusculo);

        if (contemSubstring(catalogoArtistaMinusculo, artistaMinusculo)) {
            return i; // retorna o índice da primeira música encontrada
            exibirMusica(catalogo[i]);
        }
    }

    return -1; 
}
static int compararParaOrdenarTitulo(const void *elem1, const void *elem2) {

    // Converte os elementos genéricos para Musica
    Musica *musica1 = (Musica *)elem1;
    Musica *musica2 = (Musica *)elem2;

    // Compara os títulos das duas músicas
    return compararStrings(musica1->titulo, musica2->titulo);
}
void ordenarMusicasPorTitulo(Musica *catalogo, int qtdMusicas) {
    qsort(catalogo, qtdMusicas, sizeof(Musica), compararParaOrdenarTitulo);
    printf("Catalogo ordenado por titulo com sucesso!\n");
}


static int compararParaOrdenarDuracao(const void *elem1, const void *elem2) {
    Musica *musica1 = (Musica *)elem1;
    Musica *musica2 = (Musica *)elem2;

    return musica1->duracao - musica2->duracao;
}

void ordenarMusicasPorDuracao(Musica *catalogo, int qtdMusicas) {
    qsort(catalogo, qtdMusicas, sizeof(Musica), compararParaOrdenarDuracao);
    printf("Catalogo ordenado por duracao com sucesso!\n");
}

void exibirTodasMusicasDaPlaylist(Playlist *playlist, Musica *catalogo, int qtdMusicas) {

    // Verifica se a playlist existe e se a lista de IDs foi criada
    if (playlist == NULL || playlist->idsMusicas == NULL) {
        printf("Playlist invalida!\n");
        return;
    }

    // Verifica se a playlist esta vazia
    if (playlist->quantidade == 0) {
        printf("Playlist vazia!\n");
        return;
    }

    // Mostra o nome da playlist e a quantidade de musicas
    printf("\nPLAYLIST: %s (%d musicas)\n", playlist->nome, playlist->quantidade);
    printf("----------------------------------\n");

    // Percorre todas as musicas que estao na playlist
    for (int i = 0; i < playlist->quantidade; i++) {

        // Pega o ID da musica guardado nessa posicao da playlist
        int idDaMusica = playlist->idsMusicas[i];

        // Verifica se o ID da musica existe dentro do catalogo
        if (idDaMusica >= 0 && idDaMusica < qtdMusicas) {

            // Mostra o numero da musica na playlist
            printf("\n[%d]\n", i + 1);

            // Exibe os dados da musica correta usando o catalogo
            exibirMusica(catalogo[idDaMusica]);

        } else {
            // Caso o ID nao seja valido
            printf("\n[%d] Musica invalida (ID %d)\n",
                   i + 1, idDaMusica);
        }
    }
}
