#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <../include/biblioteca.h>

// Função que pega a quantidade de livros presente no arquivo
int lerQuantidadeDeUsuarios(char *nomeArquivo) {
    int quantidadeDeUsuarios = 0;
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    fread(&quantidadeDeUsuarios, sizeof(int), 1, arquivo);

    fclose(arquivo);

    return quantidadeDeUsuarios;
}

// Função para ler uma linha de um arquivo e armazenar os dados em uma struct Livro
int lerArquivoDeUsuarios(char *nomeArquivo, int quantidadeDeUsuarios, Usuarios usuarios[]) {
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    // Ignora a primeira posição do arquivo
    fseek(arquivo, sizeof(int), SEEK_SET);

    fread(usuarios, sizeof(Livro), quantidadeDeUsuarios, arquivo);

    fclose(arquivo);
    return 0;
}

// Função para salvar livros no arquivo "livros.txt"
int salvarUsuarios(char *nomeArquivo, int quantidadeDeUsuarios, Usuarios usuarios[]) {
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("Não foi possível salvar as informações do livro.\n");
        return -1;
    }

    fwrite(&quantidadeDeUsuarios, sizeof(int), 1, arquivo);

    fwrite(usuarios, sizeof(Usuarios), quantidadeDeUsuarios, arquivo);

    free(usuarios);

    fclose(arquivo);
    return 0;
}

// Função de ordenação de array
int ordenarUsuarios(int quantidadeDeUsuarios, Usuarios usuarios[]) {
    Usuarios *usuario = (Usuarios *) malloc(sizeof(Usuarios));

    if (usuario == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro.\n");
        return -1;
    }

    for (int i = 0; i < quantidadeDeUsuarios; i++) {
        for (int j = 0; j < quantidadeDeUsuarios; j++) {
            if (usuarios[i].matricula < usuarios[j].matricula) {
                *usuario = usuarios[j];
                usuarios[j] = usuarios[i];
                usuarios[i] = *usuario;
            }
        }
    }

    free(usuario);
    return 0;
}

// Função para a busca binária de usuarios
int buscaBinariaUsuarios(int codigo, int *quantidadeDeUsuarios, Usuarios usuarios[]) {
    int meio, esquerda = 0, direita = *quantidadeDeUsuarios - 1;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;

        if (usuarios[meio].matricula == codigo) {
            return meio;
        } else if (usuarios[meio].matricula < codigo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}      