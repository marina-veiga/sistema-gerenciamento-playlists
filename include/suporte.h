#ifndef SUPORTE_H
#define SUPORTE_H

#include "playlist.h" // precisa conhecer Playlist
#include "musica.h"   // precisa conhecer Musica

//limpar o buffer de entrada 
void limparBuffer(); 

//verifica se o valor informado pelo usuário é válido
int validaInteiro(int valor, int min, int max);

//verifica se uma substring esta contida em outra string 
int contemSubstring(const char *str, const char *substr);

//converte de segundos para minutos e segundos 
void segundosParaMinutos(int totalSegundos, int *min, int *seg);

//compara duas strings
int compararStrings(const char *str1, const char *str2);

//converter caractere pra minusculo 
void paraMinusculo(char *str);  

//menu principal
void menuPrincipal(Playlist **playlists, int *qtdPlaylists, Musica *catalogo, int qtdMusicas);

#endif