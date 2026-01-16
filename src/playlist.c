#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"
#include "musica.h"
#include "suporte.h"
// --- Função: criarPlaylist ---
// Objetivo: Inicializar os campos da struct e alocar a memória inicial
void criarPlaylist(Playlist *ptrPlay, char *nomePlay){
    strcpy(ptrPlay->nome, nomePlay);

    ptrPlay->quantidade = 0;
    ptrPlay ->duracaoTotal = 0;
    ptrPlay ->capacidade = CAPACIDADE_INICIAL;

    //ALOCAÇÃO DINÂMICA 
    // O malloc reserva espaço na memória RAM para 'capacidade' músicas.
    ptrPlay->musicas = (Musica *) malloc(ptrPlay->capacidade * sizeof(Musica));


    if(ptrPlay->musicas ==NULL){
        printf("Erro fatal: Memória insuficiente para criar playlist!\n");
        exit(1);
    }


}
// --- Função: adicionarMusicaNaPlaylist ---
// Objetivo: Pedir dados ao usuário e gerenciar o array dinâmico.
void adicionarMusicaPlaylist(Playlist *ptrPlay){
    if(ptrPlay->quantidade >= ptrPlay->capacidade){
        ptrPlay->capacidade *= 2;

// O realloc tenta aumentar o bloco de memória existente ou move para um novo lugar maior.
        ptrPlay->musicas = (Musica *) realloc(ptrPlay->musicas, ptrPlay->capacidade * sizeof(Musica));

       if(ptrPlay->musicas == NULL) {
            printf("Erro ao expandir memória da playlist!\n");
            return;
        }
    }
// Variável temporária para ler os dados
    Musica music;
    printf("\n--- Adicionando Música em '%s' ---\n", ptrPlay->nome);
    // 2. Coleta de dados
    printf("Titulo: ");
    fgets(music.titulo,MAX_NOME,stdin);
    music.titulo[strcspn(music.titulo, "\n")] = '\0';

    printf("Duracao da musica(em segundos): ");
    scanf("%d", music.duracao);
    limparBuffer();

    printf("Genero: ");
    fgets(music.genero,MAX_GENERO,stdin);
    music.genero[strcspn(music.genero, "\n")] = '\0';

    // 3. Lógica para a Union (InfoExtra)
    printf("Tipo (1-Album, 2-Single/Outro): ");
    int tipo;
    scanf("%d", &tipo);
    limparBuffer();

    if (tipo == 1) {
        printf("Numero do Album: ");
        scanf("%d", &music.info.numeroAlbum);
        strcpy(music.extra, "Album"); // Guardamos string para o CSV (compatibilidade dados.c)
    } else {
        printf("Ano de Lancamento: ");
        scanf("%d", &music.info.anoLancamento);
        strcpy(music.extra, "Ano");
    }
    limparBuffer();

    // 3. Lógica para a Union (InfoExtra)
    printf("Tipo (1-Album, 2-Single/Outro): ");
    int tipo;
    scanf("%d", &tipo);
    limparBuffer();

    if (tipo == 1) {
        printf("Volume do album: ");
        scanf("%d", &music.info.numeroAlbum);
        strcpy(music.extra, "Album"); // Guardamos string para o CSV (compatibilidade dados.c)
    } else {
        printf("Ano de Lancamento: ");
        scanf("%d", &music.info.anoLancamento);
        strcpy(music.extra, "Ano");
    }
    limparBuffer();

    ptrPlay->musicas[ptrPlay->quantidade] = music;
    
    // 5. Atualização de totais
    ptrPlay->duracaoTotal += music.duracao;
    ptrPlay->quantidade++; // Incrementa para a próxima vez

    printf("Música adicionada com sucesso!\n");
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

// --- Função: liberarPlaylists ---
// Objetivo: Evitar vazamento de memória (Memory Leak) ao sair.
void liberarPlaylists(Playlist *playlists, int total) {
    for(int i = 0; i < total; i++) {
        // Para cada playlist, liberamos o vetor de músicas criado com malloc
        free(playlists[i].musicas);
    }

     
}   
