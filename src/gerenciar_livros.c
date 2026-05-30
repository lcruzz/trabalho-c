#include <stdio.h>
#include <stdlib.h>
#include "../include/biblioteca.h"

int gerenciarLivros() {
    int response = 0;

    while(1) {
        printf("==================================\n");
        printf("  Gerenciar Livros da Biblioteca  \n");
        printf("==================================\n\n");
    
        printf("[1] Cadastrar Livro \n");
        printf("[2] Remover Livro \n");
        printf("[3] Listar Todos os Livros \n");
        printf("[4] Buscar Livro \n");
        printf("[5] Informar Empréstimos \n");
        printf("[6] Atualizar Informações de um Livro \n");
    
        if (!(scanf("%d", &response))) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        };

        switch (response) {
            case 1:
                printf("Cadastrando livro...\n");
                return 0;
            case 2:
                printf("Removendo livro...\n");
                return 0;
            case 3:
                printf("Listando todos os livros...\n");
                return 0;
            case 4:
                printf("Buscando livro...\n");
                return 0;
            case 5:
                printf("Informando empréstimos...\n");
                return 0;
            case 6:
                printf("Atualizando informações de um livro...\n");
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