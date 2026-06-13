#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <../include/biblioteca.h>

// Função que pega a quantidade de usuarios presente no arquivo
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

    fread(usuarios, sizeof(Usuarios), quantidadeDeUsuarios, arquivo);

    fclose(arquivo);
    return 0;
}

// Função para salvar usuarios no arquivo "usuarios.txt"
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

// função de buscar usuario pela matricula
void buscarMatricula(int quantidadeDeUsuarios, Usuarios *usuarios, int codigo) {
    int esquerda = 0, 
    direita = quantidadeDeUsuarios - 1,
    meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;

        if (usuarios[meio].matricula == codigo) {
            printf("Matrícula: %d | Nome: %s | Curso: %s | Emprestimos ativos: %d\n",
                usuarios[meio].matricula, usuarios[meio].nome, usuarios[meio].curso,
                usuarios[meio].emprestimosAtivos);

            mensagem("Usuário encontrado com sucesso!");
            return;
        } else if (usuarios[meio].matricula < codigo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    mensagem("O usuário não foi encontrado ou não existe no sistema.");
}

// função de buscar usuario pelo nome
void buscarNomeDoUsuario(int quantidadeDeUsuarios, Usuarios *usuarios, char *nome) {
    int esquerda, direita, meio, cmp, encontrou = 0;

    // cria cópia e ordena por título
    Usuarios *copia = (Usuarios *) malloc(quantidadeDeUsuarios * sizeof(Usuarios));
    if (copia == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro.\n");
        return;
    }
    for (int i = 0; i < quantidadeDeUsuarios; i++)
        copia[i] = usuarios[i];

    Usuarios *temp = (Usuarios *) malloc(sizeof(Usuarios));
    if (temp == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro.\n");
        free(copia);
        return;
    }

    for (int i = 0; i < quantidadeDeUsuarios; i++) {
        for (int j = 0; j < quantidadeDeUsuarios; j++) {
            if (strcmp(copia[i].nome, copia[j].nome) < 0) {
                *temp = copia[j];
                copia[j] = copia[i];
                copia[i] = *temp;
            }
        }
    }
    free(temp);

    // busca binária (exata)
    esquerda = 0;
    direita = quantidadeDeUsuarios - 1;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        cmp = strcmp(copia[meio].nome, nome);

        if (cmp == 0) {
            printf("Matrícula: %d | Nome: %s | Curso: %s | Emprestimos ativos: %d\n", 
                copia[meio].matricula, copia[meio].nome, copia[meio].curso, 
                copia[meio].emprestimosAtivos);

            encontrou = 1;
            free(copia);
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    // busca parcial
    for (int i = 0; i < quantidadeDeUsuarios; i++) {
        if (strstr(usuarios[i].nome, nome) != NULL) {
            printf("Matrícula: %d | Nome: %s | Curso: %s | Emprestimos ativos: %d\n", 
                usuarios[i].matricula, usuarios[i].nome, usuarios[i].curso, 
                usuarios[i].emprestimosAtivos);

            encontrou = 1;
        }
    }

    if (!encontrou){
        mensagem("O usuário não foi encontrado ou não existe no sistema.");
    } else if(encontrou == 1){
        mensagem("Usuário encontrado com sucesso!");
    }

    free(copia);
}