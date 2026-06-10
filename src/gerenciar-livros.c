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
        printf("[5] Informar Empréstimo \n");
        printf("[6] Atualizar Informações de um Livro \n");
        printf("[0] Voltar ao Menu Principal \n\n");
    
        if (!(scanf(" %d", &response)) || response > 6 || response < 0) {
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        };

        switch (response) {
            case 1:
                clear();
                cadastrarLivro(quantidadeDeLivros, livros);
                break;
            case 2:
                clear();
                removerLivro(quantidadeDeLivros, livros);
                break;
            case 3:
                clear();
                listarLivros(quantidadeDeLivros, livros);
                break;
            case 4:
                clear();
                buscarLivro(quantidadeDeLivros, livros);
                break;
            case 5:
                break;
            case 6:
                break;
            case 0:
                clear();
                return 0;
            default:
                mensagem("Entrada inválida. Por favor, insira um número válido.");
                break;
        }

        clear();

    }
    
    return 0;
}

// Função para cadastrar um livro no sistema
int cadastrarLivro(int *quantidadeDeLivros, Livro **livros) {
    (*quantidadeDeLivros)++;
    int indice = *quantidadeDeLivros - 1;

    // Realoca a memória no ponteiro *livro com a quantidade necessária para alocar mais um livro
    Livro *livro = (Livro *) realloc(*livros, *quantidadeDeLivros * sizeof(Livro));

    if (livro == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro\n");
        return -1;
    }

    *livros = livro;

    printf("===============================\n");
    printf("        Cadastrar Livro        \n");
    printf("===============================\n\n");

    clearBuffer();
    
    (*livros)[indice].id =  *quantidadeDeLivros - 1;
    
    printf("Digite o título do livro: ");
    fgets((*livros)[indice].titulo, sizeof((*livros)[indice].titulo), stdin);
    (*livros)[indice].titulo[strcspn((*livros)[indice].titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets((*livros)[indice].autor, sizeof((*livros)[indice].autor), stdin);
    (*livros)[indice].autor[strcspn((*livros)[indice].autor, "\n")] = '\0';

    printf("Digite o ano de publicação do livro: ");
    while (!(scanf(" %d", &(*livros)[indice].anoPublicacao))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para o ano de publicação.\n");
        printf("Digite o ano de publicação do livro: ");
    }

    printf("Digite a quantidade disponível do livro: ");
    while (!(scanf(" %d", &(*livros)[indice].quantidadeDisponivel))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para a quantidade disponível.\n");
        printf("Digite a quantidade disponível do livro: ");
    }

    (*livros)[indice].quantidadeDeEmprestimo = 0;

    tratarString((*livros)[indice].titulo);
    tratarString((*livros)[indice].autor);

    mensagem("Livro cadastrado com sucesso.");

    return 0;
}

// Função para remover livro do sistema
int removerLivro(int *quantidadeDeLivros, Livro **livros) {
    int codigo = 0, indice = -1;

    while (1) {
        printf("=============================\n");
        printf("        Remover Livro        \n");
        printf("=============================\n\n");
    
        printf("Informe o código do livro: ");
        if(!(scanf("%d", &codigo)) || codigo < 0 || codigo > 9999) {
            mensagem("Entrada inválida. Por favor, insira um código válido.");
            continue;
        };
    
        for (int i = 0; i < *quantidadeDeLivros; i++) {
            if (codigo == (*livros)[i].id) {
                indice = i;
            }
        }
    
        if (indice > -1) {
            if ((*livros)[indice].quantidadeDeEmprestimo > 0) {
                mensagem("O livro não pode ser removido do sistema.");
    
                return 0;
            } else {
                for (int i = indice; i < *quantidadeDeLivros - 1; i++) {
                    (*livros)[i] = (*livros)[i + 1];
                }
            }
        } else {
            mensagem("Entrada inválida. Por favor, insira um código válido.");
            continue;
        }
    
        (*quantidadeDeLivros)--;
    
        Livro *livro = (Livro *) realloc(*livros, *quantidadeDeLivros * sizeof(Livro));
    
        if (livro == NULL) {
            printf("Ocorreu um erro na alocação do ponteiro\n");
            return -1;
        }
    
        *livros = livro;
    
        mensagem("Livro removido com sucesso.");
    
        return 0;
    }
}

// Função para listar todos os livros do sistema
int listarLivros(int *quantidadeDeLivros, Livro **livros) {
    printf("====================================\n");
    printf("        Livros da Biblioteca        \n");
    printf("====================================\n\n");

    for(int i = 0; i < *quantidadeDeLivros; i++) {
        printf("Código: %d | Título: %s | Autor: %s | Ano de Lançamento: %d | Quantidade Disponível: %d\n",
                (*livros)[i].id,
                (*livros)[i].titulo,
                (*livros)[i].autor,
                (*livros)[i].anoPublicacao,
                (*livros)[i].quantidadeDisponivel);
    };

    mensagem("Todos os livros foram listados.");

    return 0;
}

// Função para buscar livros: busca parcial e busca completa
int buscarLivro(int *quantidadeDeLivros, Livro **livros) {
    int codigo, esquerda, direita, meio;

    esquerda = 0;
    direita = *quantidadeDeLivros - 1;

    printf("============================\n");
    printf("        Buscar Livro        \n");
    printf("============================\n\n");

    printf("Informe o código do livro: ");

    if(!(scanf("%d", &codigo)) || codigo < 0 || codigo > 9999) {
        mensagem("Entrada inválida. Por favor, informe um código válido.");
    }

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;

        if ((*livros)[meio].id == codigo) {
            printf("Código: %d | Título: %s | Autor: %s | Ano de Lançamento: %d | Quantidade Disponível: %d\n",
                    (*livros)[meio].id,
                    (*livros)[meio].titulo,
                    (*livros)[meio].autor,
                    (*livros)[meio].anoPublicacao,
                    (*livros)[meio].quantidadeDisponivel);

            mensagem("Livro encontrado com sucesso.");
            return 0;
        } else if ((*livros)[meio].id < codigo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    mensagem("O livro não foi encontrado ou não existe no sistema.");
    return 0;
}