#ifndef DADOS_H
#define DADOS_H

#include "playlist.h"

//carrega as playlists já salvas no arquivo para a memória do programa
int carregarPlaylists(const char *nomeArquivo, Playlist *playlists, int *quantidade);

//salvar no arquivo as playlists criadas ou modificadas pelo usuário
int salvarPlaylists(const char *nomeArquivo, Playlist *playlists, int quantidade);

#endif