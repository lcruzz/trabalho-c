#include <stdio.h>
#include <stdlib.h>
#include "../include/biblioteca.h"

int emprestimosDevolucoes() {
    int response = 0;

    while (1) {
        printf("============================\n");
        printf("  Empréstimos e Devoluções  \n");
        printf("============================\n\n");
        
        printf("[1] Realizar Empréstimo \n");
        printf("[2] Registrar Devolução \n");
        printf("[3] Listar Empréstimos em Atraso \n");
        printf("[0] Voltar ao Menu Principal \n\n");

        if (!(scanf(" %d", &response)) || response > 3 || response < 0) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número válido.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        }

        switch (response) {
            case 1:
                printf("Realizando empréstimo...");
                break;
            case 2:
                printf("Registrando devolução...");
                break;
            case 3:
                printf("Listando empréstimos em atraso...");
                break;
            case 0:
                clear();
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                clear();
                break;
        }

        clear();
    }

    return 0;
}