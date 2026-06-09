#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/biblioteca.h"

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


// -----------------------------------------------------------------------------


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

// Função para retirar espaços duplicados entre palavras
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
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

// Função para tratar strings, removendo espaços extras e convertendo para minúsculas
void tratarString(char *str) {
    retirarEspacoDasBordas(str);
    retirarEspacoDoMeio(str);
    converterParaMinusculo(str);
}


// -----------------------------------------------------------------------------------


// Função que pega a quantidade de livros presente no arquivo
int lerQuantidadeDeLivros(char *nomeArquivo) {
    int quantidadeDeLivros = 0;
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    fread(&quantidadeDeLivros, sizeof(int), 1, arquivo);

    fclose(arquivo);

    return quantidadeDeLivros;
}

// Função para ler uma linha de um arquivo e armazenar os dados em uma struct Livro
int lerArquivoDeLivros(char *nomeArquivo, int quantidadeDeLivros, Livro livros[]) {
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    // Ignora a primeira posição do arquivo
    fseek(arquivo, sizeof(int), SEEK_SET);

    fread(livros, sizeof(Livro), quantidadeDeLivros, arquivo);

    fclose(arquivo);
    return 0;
}

// Função para salvar livros no arquivo "livros.txt"
void salvarLivros(char *nomeArquivo, int quantidadeDeLivros, Livro livros[]) {
    FILE *arquivo = fopen(nomeArquivo, "wb");

    fwrite(&quantidadeDeLivros, sizeof(int), 1, arquivo);

    fwrite(livros, sizeof(Livro), quantidadeDeLivros, arquivo);

    free(livros);

    fclose(arquivo);
}


// -------------------------------------------------------------------------------------


// Função que gera um código único entre 1 e 9999
int gerarCodigo(int quantidadeDeLivros, Livro livros[]) {
    int verificador, codigo = 0;

    do {
        verificador = 0;

        codigo = rand() % 10000;

        for(int i = 0; i < quantidadeDeLivros; i++) {
            if (codigo == livros[i].id) {
                verificador = 1;
            }
        }
    } while (verificador);

    return codigo;
}