#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/biblioteca.h"

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
int salvarLivros(char *nomeArquivo, int quantidadeDeLivros, Livro livros[]) {
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("Não foi possível salvar as informações do livro.\n");
        return -1;
    }

    fwrite(&quantidadeDeLivros, sizeof(int), 1, arquivo);

    fwrite(livros, sizeof(Livro), quantidadeDeLivros, arquivo);

    free(livros);

    fclose(arquivo);
    return 0;
}

// Função de ordenação de array
int ordenarLivros(int quantidadeDeLivros, Livro livros[]) {
    Livro *livro = (Livro *) malloc(sizeof(Livro));

    if (livro == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro.\n");
        return -1;
    }

    for (int i = 0; i < quantidadeDeLivros; i++) {
        for (int j = 0; j < quantidadeDeLivros; j++) {
            if (livros[i].id < livros[j].id) {
                *livro = livros[j];
                livros[j] = livros[i];
                livros[i] = *livro;
            }
        }
    }

    free(livro);
    return 0;
}

// Função para a busca binária de livros
int buscarCodigoLivro(int codigo, int quantidadeDeLivros, Livro livros[]) {
    int meio, esquerda = 0, direita = quantidadeDeLivros - 1;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;

        if (livros[meio].id == codigo) {
            return meio;
        } else if (livros[meio].id < codigo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}

int buscarNomeDoLivro(int quantidadeDeLivros, Livro livros[], char *nome) {
    int encontrou = 0;

    tratarString(nome);

    for (int i = 0; i < quantidadeDeLivros; i++) {
        if (strstr(livros[i].titulo, nome) != NULL) {
            printf(VERDE "\nCódigo: " RESET "%d\n"
                   NEGRITO BRANCO "Título: " RESET "%s\n"
                   NEGRITO BRANCO "Autor: " RESET "%s\n"
                   NEGRITO BRANCO "Ano de Lançamento: " RESET "%d\n"
                   NEGRITO BRANCO "Quantidade Disponível: " RESET "%d\n\n",
                    livros[i].id, livros[i].titulo, livros[i].autor,
                    livros[i].anoPublicacao, livros[i].quantidadeDisponivel);
                    
            encontrou++;
        }
    }

    return encontrou;
}