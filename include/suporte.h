#ifndef SUPORTE_H
#define SUPORTE_H

//limpar o buffer de entrada 
void limparBuffer(); 

//verifica se o valor informado pelo usuário é válido
int validaInteiro(int valor, int min, int max);

//verifica se uma substring esta contida em outra string 
int contemSubstring(const char *str, const char *substr);

//converte de segundos para minutos e segundos 
void segundosParaMinutos(int totalSegundos, int *min, int *seg);

#endif