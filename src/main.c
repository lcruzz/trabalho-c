#include <stdio.h>
#include <stdlib.h>
#include "../include/biblioteca.h"

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void clearBuffer(){
    while (getchar() != '\n');
}


int main() {
    int response = 0;
    
    while (1) {
        printf("==========================================\n");
        printf("  Sistema de Gerenciamento de Biblioteca  \n");
        printf("==========================================\n");
    
        printf("[1] Gerenciar Livros \n");
        printf("[2] Gerenciar usuários \n");
        printf("[3] Realizar empréstimo \n");
        printf("[4] Registrar devolução \n");
        printf("[5] Relatórios \n");
        printf("[0] Sair \n\n");
    
        if (!(scanf("%d", &response)) || response > 5 || response < 0) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número válido.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        }

        switch (response) {
            case 1:
                printf("Gerenciando livros...\n");
                return 0;
            case 2:
                printf("Gerenciando usuários...\n");
                return 0;
            case 3:
                printf("Realizando empréstimo...\n");
                return 0;
            case 4:
                printf("Registrando devolução...\n");
                return 0;
            case 5:
                printf("Gerando relatórios...\n");
                return 0;
            case 0:
                printf("Saindo do sistema. Até logo!\n");
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