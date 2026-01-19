#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suporte.h"
#include "playlist.h"
#include "musica.h"
#include "dados.h"

// --- Função: criarPlaylist ---
// Objetivo: Inicializar os campos da struct e alocar a memória inicial
void criarPlaylist(Playlist *ptrPlay, char *nomePlay){
    strcpy(ptrPlay->nome, nomePlay);

    ptrPlay->quantidade = 0;
    ptrPlay ->duracaoTotal = 0;
    ptrPlay ->capacidade = CAPACIDADE_INICIAL;

    //ALOCAÇÃO DINÂMICA 
    // O malloc reserva espaço na memória RAM para 'capacidade' músicas.
    ptrPlay->idsMusicas = malloc(ptrPlay->capacidade * sizeof(int));

    // Verifica se a alocação de memória falhou
    if(ptrPlay->idsMusicas ==NULL){
        printf("Erro fatal: Memoria insuficiente para criar playlist!\n");
        exit(1);
    }


}
// --- Função: adicionarMusicaNaPlaylist ---
// Objetivo: Pedir dados ao usuário e gerenciar o array dinâmico.
void adicionarMusicaPlaylist(Playlist *ptrPlay, int idMusica, Musica *catalogo, int qtdMusicas){

    // Expande o vetor se necessário
    if(ptrPlay->quantidade >= ptrPlay->capacidade){
        ptrPlay->capacidade *= 2;
        ptrPlay->idsMusicas = realloc(ptrPlay->idsMusicas, ptrPlay->capacidade * sizeof(int));
        if(ptrPlay->idsMusicas == NULL){
            printf("Erro de alocação!\n");
            exit(1);
        }
    }

    // Atualiza a duração total usando o índice direto
    ptrPlay->duracaoTotal += catalogo[idMusica].duracao;

    // Adiciona o índice do catálogo na playlist
    ptrPlay->idsMusicas[ptrPlay->quantidade] = idMusica;
    ptrPlay->quantidade++;

    // Mensagem de sucesso
    printf("Musica adicionada com sucesso na playlist!\n");
}

// --- Função: listarPlaylists ---
// Objetivo: Mostrar o resumo de todas as playlists.
void listarPlaylists(Playlist *ptrListaPlay, int total) {
    if (total == 0) {
        printf("\nNenhuma playlist cadastrada.\n");
        return;
    }

    printf("\n=== SUAS PLAYLISTS ===\n");
    for (int i = 0; i < total; i++) {
        int min, seg;
        // Integração: Usamos suporte.c para converter segundos em Min:Seg
        segundosParaMinutos(ptrListaPlay[i].duracaoTotal, &min, &seg);
        
        printf("%d. %s [Músicas: %d | Tempo: %02d:%02d]\n", 
               i + 1, ptrListaPlay[i].nome, ptrListaPlay[i].quantidade, min, seg);
    }
}

void removerMusicaPlaylist(Playlist *ptrPlay, int idMusica) {
    int musicaEncontrada = 0;

    // Percorre o vetor de IDs da playlist
    for (int i = 0; i < ptrPlay->quantidade; i++) {
        if (ptrPlay->idsMusicas[i] == idMusica) {
            //Move todos os elementos à direita uma posição para a esquerda
            for (int j = i; j < ptrPlay->quantidade - 1; j++) {
                ptrPlay->idsMusicas[j] = ptrPlay->idsMusicas[j + 1];
            }
            ptrPlay->quantidade--; // Atualiza o tamanho lógico da playlist
            musicaEncontrada = 1;
            printf("Musica removida com sucesso!\n");
            break;
        }
    }
    if (!musicaEncontrada) {
        printf("Musica nao encontrada na playlist.\n");
    }
}

void ordenarMusicasPorTituloNaPlaylist(Playlist *ptrPlay, Musica *catalogo) {
    // Se a playlist for nula ou tiver menos de 2 músicas, não há o que ordenar
    if (ptrPlay == NULL || ptrPlay->quantidade < 2) return;

    // Laço externo do Bubble Sort
    for (int i = 0; i < ptrPlay->quantidade - 1; i++) {
        for (int j = 0; j < ptrPlay->quantidade - i - 1; j++) {
            //Acessa as structs de Música correspondentes aos IDs na posição atual e seguinte
            Musica *m1 = &catalogo[ptrPlay->idsMusicas[j]];
            Musica *m2 = &catalogo[ptrPlay->idsMusicas[j+1]];
            // Compara os títulos usando strcmp
            if (strcmp(m1->titulo, m2->titulo) > 0) {
                int temp = ptrPlay->idsMusicas[j];
                ptrPlay->idsMusicas[j] = ptrPlay->idsMusicas[j+1];
                ptrPlay->idsMusicas[j+1] = temp;
            }
        }
    }
}

//Ordena as músicas de uma playlist pela duração
void ordenarMusicasPorDuracaoNaPlaylist(Playlist *ptrPlay, Musica *catalogo) {
    if (ptrPlay == NULL || ptrPlay->quantidade < 2) return;
    // Laço externo do Bubble Sort
    for (int i = 0; i < ptrPlay->quantidade - 1; i++) {
        for (int j = 0; j < ptrPlay->quantidade - i - 1; j++) {
            // Obtém referências para as músicas no catálogo
            Musica *m1 = &catalogo[ptrPlay->idsMusicas[j]];
            Musica *m2 = &catalogo[ptrPlay->idsMusicas[j+1]];

            // Compara as durações
            if (m1->duracao > m2->duracao) {
                // Troca os IDs se a música atual for mais longa que a próxima
                int temp = ptrPlay->idsMusicas[j];
                ptrPlay->idsMusicas[j] = ptrPlay->idsMusicas[j+1];
                ptrPlay->idsMusicas[j+1] = temp;
            }
        }
    }
}



// --- Função: liberarPlaylists ---
// Objetivo: Evitar vazamento de memória (Memory Leak) ao sair.
void liberarPlaylists(Playlist *playlists, int total) {
    for(int i = 0; i < total; i++) {
        // Para cada playlist, liberamos o vetor de músicas criado com malloc
        free(playlists[i].idsMusicas);
    }

     
}   
