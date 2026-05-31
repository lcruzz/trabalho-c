#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("[0] Voltar ao Menu Principal \n\n");
    
        if (!(scanf(" %d", &response))) {
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
                cadastrarLivro();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
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

int cadastrarLivro() {
    Livro novoLivro;

    FILE *file = fopen("../data/livros.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de livros.\n");
        return -1;
    }

    printf("Digite o título do livro: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';

    fprintf(file, "%s\n", novoLivro.titulo);
    fclose(file);

    return 0;
}