#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/biblioteca.h"

int gerenciarLivros(int *quantidadeDeLivros, Livro **livros) {
    int resposta = 0;

    while(1) {
        printf("==================================\n");
        printf("  Gerenciar Livros da Biblioteca  \n");
        printf("==================================\n\n");
    
        printf("[1] Cadastrar Livro \n");
        printf("[2] Remover Livro \n");
        printf("[3] Listar Todos os Livros \n");
        printf("[4] Buscar Livro \n");
        printf("[5] Atualizar Informações de um Livro \n");
        printf("[0] Voltar ao Menu Principal \n\n");
    
        if (!(scanf(" %d", &resposta)) || resposta < 0 || resposta > 5) {
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        };

        switch (resposta) {
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
                clear();
                atualizarLivro(quantidadeDeLivros, livros);
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
    int codigo = *quantidadeDeLivros - 1;

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
    
    (*livros)[codigo].id =  *quantidadeDeLivros - 1;
    
    printf("Digite o título do livro: ");
    fgets((*livros)[codigo].titulo, sizeof((*livros)[codigo].titulo), stdin);
    (*livros)[codigo].titulo[strcspn((*livros)[codigo].titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets((*livros)[codigo].autor, sizeof((*livros)[codigo].autor), stdin);
    (*livros)[codigo].autor[strcspn((*livros)[codigo].autor, "\n")] = '\0';

    printf("Digite o ano de publicação do livro: ");
    while (!(scanf(" %d", &(*livros)[codigo].anoPublicacao))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para o ano de publicação.\n");
        printf("Digite o ano de publicação do livro: ");
    }

    printf("Digite a quantidade disponível do livro: ");
    while (!(scanf(" %d", &(*livros)[codigo].quantidadeDisponivel))) {
        clearBuffer();
        printf("Entrada inválida. Por favor, insira um número para a quantidade disponível.\n");
        printf("Digite a quantidade disponível do livro: ");
    }

    (*livros)[codigo].quantidadeDeEmprestimo = 0;

    tratarString((*livros)[codigo].titulo);
    tratarString((*livros)[codigo].autor);

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
        if(!(scanf("%d", &codigo)) || codigo < 0 || codigo > *quantidadeDeLivros - 1) {
            mensagem("Entrada inválida. Por favor, insira um código válido.");
            continue;
        };
    
        indice = buscaBinariaLivros(codigo,  *quantidadeDeLivros, *livros);
    
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
    int codigo, indice;

    printf("============================\n");
    printf("        Buscar Livro        \n");
    printf("============================\n\n");

    printf("Informe o código do livro: ");

    if(!(scanf("%d", &codigo)) || codigo < 0 || codigo > *quantidadeDeLivros - 1) {
        mensagem("Entrada inválida. Por favor, informe um código válido.");
    }

    indice = buscaBinariaLivros(codigo, quantidadeDeLivros, *livros);

    if (indice > -1) {
        printf("Código: %d | Título: %s | Autor: %s | Ano de Lançamento: %d | Quantidade Disponível: %d\n",
                        (*livros)[indice].id,
                        (*livros)[indice].titulo,
                        (*livros)[indice].autor,
                        (*livros)[indice].anoPublicacao,
                        (*livros)[indice].quantidadeDisponivel);
        mensagem("Livro encontrado com sucesso");
        return 0;
    }

    mensagem("O livro não foi encontrado ou não existe no sistema.");
    
    return 0;
}

// Função para atualizar informações de um livro existente
int atualizarLivro(int *quantidadeDeLivros, Livro **livros) {
    int resposta, codigo;

    while (1) {
        printf("===============================\n");
        printf("        Atualizar Livro        \n");
        printf("===============================\n\n");
    
        printf("[1] Atualizar Título \n");
        printf("[2] Atualizar Autor \n");
        printf("[3] Atualizar Ano de Lançamento \n");
        printf("[4] Atualizar Quantidade Disponível \n");
        printf("[0] Voltar para Gerenciar Livros \n\n");

        printf("Informe o campo do livro: ");
    
        if (!(scanf("%d", &resposta)) || resposta < 0 || resposta > 4) {
            mensagem("Entrada inválida. Por favor, informe um número válido.");
            continue;
        }

        if (resposta == 0) {
            break;
        }
    
        printf("Informe o código do livro: ");
    
        if (!(scanf("%d", &codigo)) || codigo < 0 || codigo > *quantidadeDeLivros - 1) {
            mensagem("Entrada inválida. Por favor, informe um código válido");
            continue;
        }

        clearBuffer();

        switch (resposta) {
            case 1:
                printf("Título: ");
                fgets((*livros)[codigo].titulo, sizeof((*livros)[codigo].titulo), stdin);
                clear();
                continue;
            case 2:
                printf("Autor: ");
                fgets((*livros)[codigo].autor, sizeof((*livros)[codigo].autor), stdin);
                clear();
                continue;
            case 3:
                printf("Ano de Lançamento: ");
                if (!(scanf("%d", &(*livros)[codigo].anoPublicacao))) mensagem("Entrada inválida. Por favor, informe um código válido");
                clear();
                continue;
            case 4:
                printf("Quantidade Disponível: ");
                if (!(scanf("%d", &(*livros)[codigo].quantidadeDisponivel))) mensagem("Entrada inválida. Por favor, informe um código válido");
                clear();
                continue;
            default:
                mensagem("Entrada inválida. Por favor, informe um número válido");
                continue;
        }
    }

    return 0;
}