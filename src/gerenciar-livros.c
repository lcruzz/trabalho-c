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
    
        if (!(scanf(" %d", &response)) || response > 6 || response < 0) {
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
    novoLivro.id = rand() % 10000; // Gera um ID aleatório para o livro (pode ser melhorado para garantir unicidade)

    FILE *file = fopen("data/livros.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de livros: ../data/livros.txt\n");
        printf("(verifique se o executável está sendo executado a partir de src/)\n");
        printf("Pressione Enter para continuar...");
        clearBuffer();
        getchar();
        return -1;
    }

    clearBuffer();

    printf("Digite o título do livro: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

    printf("Digite o ano de publicação do livro: ");
    while (!(scanf(" %d", &novoLivro.anoPublicacao))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para o ano de publicação.\n");
        printf("Digite o ano de publicação do livro: ");
    }

    printf("Digite a quantidade disponível do livro: ");
    while (!(scanf(" %d", &novoLivro.quantidadeDisponivel))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para a quantidade disponível.\n");
        printf("Digite a quantidade disponível do livro: ");
    }

    tratarString(novoLivro.titulo);
    tratarString(novoLivro.autor);

    fprintf(file, "%d,%s,%s,%d,%d\n", novoLivro.id, novoLivro.titulo, novoLivro.autor, novoLivro.anoPublicacao, novoLivro.quantidadeDisponivel);
    fclose(file);

    return 0;
}

int removerLivro() {
    return 0;
}