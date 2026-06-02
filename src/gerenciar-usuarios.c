#include <stdio.h>
#include <stdlib.h>
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
                printf("Cadastrando usuário...");
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