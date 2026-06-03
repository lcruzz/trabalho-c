#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <../include/biblioteca.h>

int gerenciarUsuarios() {
    int response = 0;

    while (1) {
        printf("====================================\n");
        printf("  Gerenciar Usuários da Biblioteca  \n");
        printf("====================================\n\n");

        printf("[1] Cadastrar Usuário \n");
        printf("[2] Listar Todos os Usuários \n");
        printf("[3] Buscar Usuário \n");
        printf("[4] Atualizar Informações de um Usuário \n");
        printf("[5] Remover Usuário \n");
        printf("[0] Voltar ao Menu Principal \n\n");

        if (!(scanf(" %d", &response)) || response > 5 || response < 0) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        };

        switch (response) {
            case 1:
                clear();
                cadastrarUsuarios();
                break;
            case 2:
                printf("Listando todos os usuários...");
                break;
            case 3:
                printf("Buscando usuário...");
                break;
            case 4:
                printf("Atualizando informações de um usuário...");
                break;
            case 5:
                printf("Removendo um usuário...");
                break;
            case 0:
                clear();
                return 0;
            default:
                printf("Entrada inválida. Por favor, insira um número.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                clear();
                break;
        }

        clear();
    }

    return 0;
}

int cadastrarUsuarios(){
    printf("====================================\n");
    printf("         Cadastrar Usuário          \n");
    printf("====================================\n\n");

    Usuarios novoUsuario;

    FILE *arq;
    arq = fopen("data/usuarios.txt", "r");

    if(arq == NULL){
        arq = fopen("data/usuarios.txt", "w");

        if(arq == NULL){
            printf("Erro ao abrir o arquivo de usuarios: data/usuarios.txt");
            printf("Pressione Enter para continuar...");
            clearBuffer();
            getchar();
            return -1;
        }
    }

    clearBuffer();

    fclose(arq);
    
    int ultimaMatricula = pegaUltimaMatricula();
    novoUsuario.matricula = ultimaMatricula + 1;

    arq = fopen("data/usuarios.txt", "a");
    
    printf("Informe o nome do aluno: ");
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);

    printf("Informe o curso do aluno: ");
    fgets(novoUsuario.curso, sizeof(novoUsuario.curso), stdin);
    
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0';
    novoUsuario.curso[strcspn(novoUsuario.curso, "\n")] = '\0';
    
    tratarString(novoUsuario.nome);
    tratarString(novoUsuario.curso);
    
    fprintf(arq, "Matricula: %d | ", novoUsuario.matricula);
    fprintf(arq, "Nome: %s | ", novoUsuario.nome);
    fprintf(arq, "Curso: %s | ", novoUsuario.curso);
    fprintf(arq, "\n");
    fclose(arq);

    printf("\nO aluno foi cadastrado com sucesso!\nPressione Enter para voltar ao menu...");
    getchar();
    
    return 0;
}