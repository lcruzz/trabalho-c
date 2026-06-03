#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <../include/gerenciar-usuarios.h>
#include <../include/biblioteca.h>


// Função para pegar a matricula do ultimo aluno
int pegaUltimaMatricula(){
    FILE *arq;
    char linha[256];
    int ultimaMatricula = 1000;
    
    arq = fopen("data/usuarios.txt", "r");
    
    if (arq == NULL) {
        return 0;
    }

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if(sscanf(linha, "Matricula: %d", &ultimaMatricula) == 1){

        }
    }
    
    fclose(arq);
    
    return ultimaMatricula;
}

void pesquisarMatricula(int buscaMatricula, int *encontrado, char *linhaEncontrada) {
    FILE *arq;
    arq = fopen("data/usuarios.txt", "r");

    if(arq == NULL) {
        *encontrado = -1;
        return;
    }

    char linha[256];
    int matricula;
    *encontrado = 0;  // Inicializa como não encontrado

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if(sscanf(linha, "Matricula: %d", &matricula) == 1) {
            if(matricula == buscaMatricula) {
                strcpy(linhaEncontrada, linha);
                *encontrado = 1;
                break;
            }
        }
    }

    fclose(arq);
}

void pesquisarNome(char *buscaNome, int *encontrado, char *linhaEncontrada){
    FILE *arq;
    arq = fopen("data/usuarios.txt", "r");

    if(arq == NULL) {
        *encontrado = -1;
        return;
    }

    // Criar uma cópia para não modificar a string original se não quiser
    char nomeBuscaCopia[TAMANHO_NOME];
    strcpy(nomeBuscaCopia, buscaNome);
    tratarString(nomeBuscaCopia);
    
    char linha[256];
    char nome[TAMANHO_NOME];
    *encontrado = 0;

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if(sscanf(linha, "Matricula: %*d | Nome: %149[^|]", nome) == 1){
            // Criar cópia do nome para tratamento
            char nomeCopia[TAMANHO_NOME];
            strcpy(nomeCopia, nome);
            tratarString(nomeCopia);
            
            if(strcmp(nomeCopia, nomeBuscaCopia) == 0){
                *encontrado = 1;
                strcpy(linhaEncontrada, linha);
                break; 
            }
        }
    }

    fclose(arq);
}