#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/biblioteca.h"

// Função que pega a quantidade de livros presente no arquivo
int lerQuantidadeDeEmprestimos(char *nomeArquivo) {
    int quantidadeDeEmprestimos = 0;
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    fread(&quantidadeDeEmprestimos, sizeof(int), 1, arquivo);

    fclose(arquivo);

    return quantidadeDeEmprestimos;
}

// Função para ler uma linha de um arquivo e armazenar os dados em uma struct Livro
int lerArquivoDeEmprestimos(char *nomeArquivo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]) {
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    // Ignora a primeira posição do arquivo
    fseek(arquivo, sizeof(int), SEEK_SET);

    fread(emprestimos, sizeof(Emprestimo), quantidadeDeEmprestimos, arquivo);

    fclose(arquivo);
    return 0;
}

// Função para salvar livros no arquivo "livros.txt"
int salvarEmprestimos(char *nomeArquivo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]) {
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("Não foi possível salvar as informações do emprestimo.\n");
        return -1;
    }

    fwrite(&quantidadeDeEmprestimos, sizeof(int), 1, arquivo);

    fwrite(emprestimos, sizeof(Emprestimo), quantidadeDeEmprestimos, arquivo);

    free(emprestimos);

    fclose(arquivo);
    return 0;
}

// Função de ordenação de array
int ordenarEmprestimos(int quantidadeDeEmprestimos, Emprestimo emprestimos[]) {
    Emprestimo *emprestimo = (Emprestimo *) malloc(sizeof(Emprestimo));

    if (emprestimo == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro.\n");
        return -1;
    }

    for (int i = 0; i < quantidadeDeEmprestimos; i++) {
        for (int j = 0; j < quantidadeDeEmprestimos; j++) {
            if (emprestimos[i].id < emprestimos[j].id) {
                *emprestimo = emprestimos[j];
                emprestimos[j] = emprestimos[i];
                emprestimos[i] = *emprestimo;
            }
        }
    }

    free(emprestimo);
    return 0;
}

// Função para a busca binária de emprestimos
int buscarCodigoEmprestimo(int codigo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]) {
    int meio, esquerda = 0, direita = quantidadeDeEmprestimos - 1;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;

        if (emprestimos[meio].id == codigo) {
            return meio;
        } else if (emprestimos[meio].id < codigo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}