#ifndef DADOS_H
#define DADOS_H

#include "musica.h"
#include "playlist.h"

//carrega as músicas do arquivo CSV
int carregarMusicas(Musica **catalogo);

//salvar no arquivo as playlists criadas ou modificadas pelo usuário
int salvarPlaylists(Playlist *playlists, int quantidade,Musica *catalogo); 

//carrega todas as playlists do arquivo CSV e retorna o total de playlists carregadas
int carregarPlaylists(Playlist **playlists);

#endif