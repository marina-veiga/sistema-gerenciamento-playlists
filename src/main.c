#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "suporte.h"
#include "playlist.h"
#include "musica.h"
#include "dados.h"

int main() {
    Musica *catalogo = NULL; // Ponteiro para armazenar todas as músicas do catálogo
    Playlist *playlists = NULL;  // Ponteiro para armazenar todas as playlists criadas
    int qtdPlaylists = 0;   // Contador de playlists carregadas/criadas


    int qtdMusicas = carregarMusicas(&catalogo); // função que carrega o catálogo (musicas.csv) e retorna a quantidade

    //se não houver músicas no catálogo, encerra o programa
    if(qtdMusicas == 0){
        printf("Nenhuma musica carregada. Encerrando.\n");
        return 0;
    }

    //mostra o menu para o usuário escolher o que fazer (criar playlist, adicionar música, etc.)
    menuPrincipal(&playlists, &qtdPlaylists, catalogo, qtdMusicas);

    //libera a memória usada pelas playlists antes de fechar o programa
    liberarPlaylists(playlists, qtdPlaylists);

    //libera a memória usada pelas músicas do catálogo antes de fechar o programa
    free(catalogo);

    return 0;
}