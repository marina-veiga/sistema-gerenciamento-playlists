#include <stdio.h>
#include <string.h>
#include "suporte.h"

//limpar o buffer de entrada 
void limparBuffer(){
    int caractere; //armazena cada caractere lido do buffer

    // lê o primeiro caractere do buffer
    caractere = getchar(); 

    //enquanto o caractere lido não for '\n' (enter) e não for fim do arquivo(EOF), continua limpando o buffer
    while (caractere!= '\n' && caractere != EOF){
        caractere = getchar(); 
        
    }
}

//verifica se o valor informado pelo usuário é válido
int validaInteiro(int valor, int min, int max){
    int auxValor = valor; // cópia do valor recebido

    // enquanto o valor estiver fora do intervalo, pede novo valor
    while(auxValor < min || auxValor > max){
        printf("Valor invalido! Informe um valor entre %d e %d: ", min, max);
        scanf("%d",&auxValor);
        limparBuffer();
        
    }

    // quando sair do loop, retorna o valor válido
    return auxValor;

}

//verifica se uma substring esta contida em outra string 
//retorna 1 se encontrar a substring, 0 caso contrário
int contemSubstring(const char *str, const char *substr){
    const char *ptrAux = str; //ponteiro para percorrer a string maior

    //loop que percorre a string maior
    while(*ptrAux != '\0'){
        const char *ptrTemp = ptrAux; //ponteiro temporário começando na posição atual da string maior
        const char *ptrAuxSub= substr; //ponteiro aux para a substring

        //loop que compara todos os caracteres da substring com a string maior
        while(*ptrTemp != '\0' && *ptrAuxSub != '\0' && *ptrTemp == *ptrAuxSub){
            ptrTemp++;
            ptrAuxSub++;
        }

        // se chegar ao final da substring, todos os caracteres coincidiram
        if(*ptrAuxSub == '\0'){
            return 1; //substring encontrada
        }

        ptrAux++; // avança na string maior para o próximo caractere
    }
    
    return 0; //se percorreu toda a string maior e não encontrou a substring completa, significa que a substring não está contida nela
}

//converte de segundos para minutos e segundos 
void segundosParaMinutos(int totalSegundos, int *min, int *seg){
    int minutos = totalSegundos/ 60; //calcula minutos completos
    int segundos = totalSegundos % 60; //calcula os segundos restantes

    *min = minutos;  //armazena os minutos no ponteiro min
    *seg = segundos; //armazena os segundo no ponteiro seg
}