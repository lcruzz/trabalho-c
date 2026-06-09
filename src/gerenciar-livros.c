#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/biblioteca.h"

int gerenciarLivros(int *quantidadeDeLivros, Livro **livros) {
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
                cadastrarLivro(quantidadeDeLivros, livros);
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

int cadastrarLivro(int *quantidadeDeLivros, Livro **livros) {
    (*quantidadeDeLivros)++;
    int elemento = *quantidadeDeLivros - 1;

    // Realoca a memória no ponteiro *livro com a quantidade necessária para alocar mais um livro
    Livro *livro = (Livro *) realloc(*livros, *quantidadeDeLivros * sizeof(Livro));

    if (livro == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro\n");
        return -1;
    }

    *livros = livro;

    printf("===========================\n");
    printf("      Cadastrar Livro      \n");
    printf("===========================\n\n");

    clearBuffer();
    
    (*livros)[elemento].id =  gerarCodigo(*quantidadeDeLivros, *livros);
    
    printf("Digite o título do livro: ");
    fgets((*livros)[elemento].titulo, sizeof((*livros)[elemento].titulo), stdin);
    (*livros)[elemento].titulo[strcspn((*livros)[elemento].titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets((*livros)[elemento].autor, sizeof((*livros)[elemento].autor), stdin);
    (*livros)[elemento].autor[strcspn((*livros)[elemento].autor, "\n")] = '\0';

    printf("Digite o ano de publicação do livro: ");
    while (!(scanf(" %d", &(*livros)[elemento].anoPublicacao))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para o ano de publicação.\n");
        printf("Digite o ano de publicação do livro: ");
    }

    printf("Digite a quantidade disponível do livro: ");
    while (!(scanf(" %d", &(*livros)[elemento].quantidadeDisponivel))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para a quantidade disponível.\n");
        printf("Digite a quantidade disponível do livro: ");
    }

    (*livros)[elemento].quantidadeDeEmprestimo = 0;

    tratarString((*livros)[elemento].titulo);
    tratarString((*livros)[elemento].autor);

    return 0;
}

int removerLivro() {


    return 0;
}