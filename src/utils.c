#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para limpar a tela
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para limpar o buffer de entrada
void clearBuffer(){
    while (getchar() != '\n');
}

// Função para retirar espaços das bordas de uma string
void retirarEspacoDasBordas(char *str) {
    int inicio, j = 0;
    int fim = strlen(str) - 1;

    while (str[inicio] == ' ') inicio++;

    while (fim > inicio && str[fim] == ' ') fim--;

    for (int i = inicio; i <= fim; i++) {
        str[j++] = str[i];
    }

    str[j] = '\0';
}

void retirarEspacoDoMeio(char *str) {

}

// Função para tratar strings, removendo espaços extras e convertendo para manúsculas
void tratarString(char *str) {
    retirarEspacoDasBordas(str);

}
