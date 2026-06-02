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
    int inicio = 0, j = 0;
    int fim = strlen(str) - 1;

    while (str[inicio] == ' ') inicio++;

    while (fim > inicio && str[fim] == ' ') fim--;

    for (int i = inicio; i <= fim; i++) {
        str[j++] = str[i];
    }

    str[j] = '\0';
}

void retirarEspacoDoMeio(char *str) {
    int i = 0, j = 0;
    int dentro_espaco = 0;
    
    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
            dentro_espaco = 0;
        } else if (!dentro_espaco) {
            str[j++] = ' ';
            dentro_espaco = 1;
        }
        i++;
    }
    str[j] = '\0';
}

// Função para converter uma string para minúsculas
void converterParaMinusculo(char *str) {
    for (int i = 0; i < strlen(str) - 1; i++) {
        str[i] = tolower(str[i]);
    }
}

// Função para tratar strings, removendo espaços extras e convertendo para minúsculas
void tratarString(char *str) {
    retirarEspacoDasBordas(str);
    retirarEspacoDoMeio(str);
    converterParaMinusculo(str);
}

// Função para pegar a matricula do ultimo aluno
void pegaUltimaMatricula(){
    FILE *arq;
    char linha[200];
    int ultimaMatricula = 0;
    
    arq = fopen("data/usuarios.txt", "r");
    
    if (arq == NULL) {
        return 0;
    }
    while (fgets(linha, sizeof(linha), arq) != NULL) {
        int camposLidos = sscanf(linha, "%d", &ultimaMatricula);
    }
    
    fclose(arq);
    
    return ultimaMatricula;
}
