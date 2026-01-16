/* MUSICA.C (implementação do módulo de músicas) */

/*Ele contém a lógica concreta das funções que lidam
diretamente com as operações sobre as músicas nas playlists*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // Para tolower()
#include "musica.h"
#include "playlist.h"  // Para ter a definição completa de Playlist

// FUNÇÔES PRINCIPAIS

void exibirMusica(Musica m) {
    int minutos, segundos;
    
    // Converte duração
    converterSegundosParaMinutos(m.duracao, &minutos, &segundos);
    
    // Exibe os dados
    printf("\nEXBIR MUSICA:\n");
    printf("Titulo:   %s\n", m.titulo);
    printf("Artista:  %s\n", m.artista);
    printf("Duracao:  %02d:%02d\n", minutos, segundos);
    printf("Genero:   %s\n", m.genero);
    
    // InforExtra
    if (m.info.anoLancamento != 0) {
        printf("Ano de Lancamento:      %d\n", m.info.anoLancamento);
    }
    printf("\n");
}

int buscarMusicaPorTitulo(Playlist *p, char *titulo) {
    // Verifica se a playlist é válida
    if (p == NULL || p->musicas == NULL) {
        printf("Playlist inválida!\n");
        return -1;
    }
    
    if (p->quantidade == 0) {
        printf("Playlist vazia!\n");
        return -1;
    }
    
    // Remove possível \n do final
    titulo[strcspn(titulo, "\n")] = '\0';
    
    // Busca a música
    for (int i = 0; i < p->quantidade; i++) {
        if (compararStringsInsensitivo(p->musicas[i].titulo, titulo) == 0) {
            printf("Música encontrada na posição %d\n", i + 1);
            return i; // Retorna o índice
        }
    }
    
    printf("Música '%s' não encontrada!\n", titulo);
    return -1; // Não encontrou
}


int buscarMusicaPorArtista(Playlist *p, char *artista) {
    // Verifica se a playlist é válida
    if (p == NULL || p->musicas == NULL) {
        printf("Playlist inválida!\n");
        return -1;
    }
    
    if (p->quantidade == 0) {
        printf("Playlist vazia!\n");
        return -1;
    }
    
    // Remove possível \n do final
    artista[strcspn(artista, "\n")] = '\0';
    
    // Busca a música
    for (int i = 0; i < p->quantidade; i++) {
        if (compararStringsInsensitivo(p->musicas[i].artista, artista) == 0) {
            printf("Música do artista encontrada na posição %d\n", i + 1);
            return i; // Retorna o índice da primeira encontrada
        }
    }
    
    printf("Nenhuma música do artista '%s' encontrada!\n", artista);
    return -1; // Não encontrou
}


static int compararParaOrdenarTitulo(const void *a, const void *b) {
    const Musica *musicaA = (const Musica *)a;
    const Musica *musicaB = (const Musica *)b;
    
    return compararStringsInsensitivo(musicaA->titulo, musicaB->titulo);
}

void ordenarMusicasPorTitulo(Playlist *p) {
    if (p == NULL || p->musicas == NULL) {
        printf("Playlist inválida!\n");
        return;
    }
    
    if (p->quantidade < 2) {
        printf("Playlist tem apenas %d música. Nada para ordenar.\n", p->quantidade);
        return;
    }
    
    // Usa qsort para ordenar
    qsort(p->musicas, p->quantidade, sizeof(Musica), compararParaOrdenarTitulo);
    
    printf("Playlist ordenada por título com sucesso!\n");
}


static int compararParaOrdenarDuracao(const void *a, const void *b) {
    const Musica *musicaA = (const Musica *)a;
    const Musica *musicaB = (const Musica *)b;
    
    // Ordena do menor para o maior (crescente)
    return musicaA->duracao - musicaB->duracao;
}


void ordenarMusicasPorDuracao(Playlist *p) {
    if (p == NULL || p->musicas == NULL) {
        printf("Playlist inválida!\n");
        return;
    }
    
    if (p->quantidade < 2) {
        printf("ℹPlaylist tem apenas %d música. Nada para ordenar.\n", p->quantidade);
        return;
    }
    
    // Usa qsort para ordenar
    qsort(p->musicas, p->quantidade, sizeof(Musica), compararParaOrdenarDuracao);
    
    printf("Playlist ordenada por duração (crescente) com sucesso!\n");
}

void exibirTodasMusicasDaPlaylist(Playlist *p) {
    if (p == NULL || p->musicas == NULL) {
        printf("Playlist inválida!\n");
        return;
    }
    
    if (p->quantidade == 0) {
        printf("Playlist vazia!\n");
        return;
    }
    
    printf("\nPLAYLIST: %s (%d músicas)\n", p->nome, p->quantidade);
    printf("\n");
    
    for (int i = 0; i < p->quantidade; i++) {
        printf("\n[%d] ", i + 1);
        exibirMusica(p->musicas[i]);
    }
}


