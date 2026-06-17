#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <../include/biblioteca.h>

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

int lerArquivoDeUsuarios(char *nomeArquivo, int quantidadeDeUsuarios, Usuarios usuarios[]) {
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    fseek(arquivo, sizeof(int), SEEK_SET);

    fread(usuarios, sizeof(Usuarios), quantidadeDeUsuarios, arquivo);

    fclose(arquivo);
    return 0;
}

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

int buscarMatricula(int codigo, int quantidadeDeUsuarios, Usuarios usuarios[]) {
    int meio, esquerda = 0, direita = quantidadeDeUsuarios - 1;

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

// busca parcial por nome
int buscarNomeDoUsuario(int quantidadeDeUsuarios, Usuarios *usuarios, char *nome) {
    int encontrou = 0;

    tratarString(nome);
    
    for (int i = 0; i < quantidadeDeUsuarios; i++) {
        if (strstr(usuarios[i].nome, nome) != NULL) {
            printf(VERDE "\nMatrícula: " RESET "%d\n"
                   NEGRITO BRANCO "Nome: " RESET "%s\n"
                   NEGRITO BRANCO "Curso: " RESET "%s\n"
                   NEGRITO BRANCO "Empréstimos ativos: " RESET "%d\n\n",
                    usuarios[i].matricula, usuarios[i].nome,
                    usuarios[i].curso, usuarios[i].emprestimosAtivos);
            encontrou++;
        }
    }

    return encontrou;
}