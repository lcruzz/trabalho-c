#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/biblioteca.h"

int gerenciarLivros(int *quantidadeDeLivros, Livro **livros) {
    int resposta = 0;

    while(1) {
        imprimirArquivo("menus/menu-livros.txt");

        printf(NEGRITO BRANCO "Informe a opção que deseja: " RESET);

        if (!(scanf(" %d", &resposta)) || resposta < 0 || resposta > 5) {
            clearBuffer();
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
                listarLivros(quantidadeDeLivros, livros);
                break;
            case 3:
                clear();
                buscarLivro(quantidadeDeLivros, livros);
                break;
            case 4:
                clear();
                atualizarLivro(quantidadeDeLivros, livros);
                break;
            case 5:
                clear();
                removerLivro(quantidadeDeLivros, livros);
                break;
            case 0:
                clear();
                return 0;
            default:
                clearBuffer();
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

    time_t horario = time(NULL);
    struct tm data = *localtime(&horario);
    int anoAtual = data.tm_year +1900;

    Livro *livro = (Livro *) realloc(*livros, *quantidadeDeLivros * sizeof(Livro));

    if (livro == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro\n");
        return -1;
    }

    *livros = livro;

    clearBuffer();

    while(1){
        imprimirArquivo("menus/livros.txt");
        printf("            Cadastrar Livro\n");
        printf("_______________________________________\n\n");
    
        if(codigo > 0){
            (*livros)[codigo].id = (*livros)[codigo - 1].id + 1;
        } else{
            (*livros)[codigo].id = *quantidadeDeLivros;
        }

        printf("Digite o título do livro: ");
        fgets((*livros)[codigo].titulo, sizeof((*livros)[codigo].titulo), stdin);
        (*livros)[codigo].titulo[strcspn((*livros)[codigo].titulo, "\n")] = '\0';
    
        printf("Digite o autor do livro: ");
        fgets((*livros)[codigo].autor, sizeof((*livros)[codigo].autor), stdin);
        (*livros)[codigo].autor[strcspn((*livros)[codigo].autor, "\n")] = '\0';
    
        printf("Digite o gênero do livro: ");
        fgets((*livros)[codigo].genero, sizeof((*livros)[codigo].genero), stdin);
        (*livros)[codigo].genero[strcspn((*livros)[codigo].genero, "\n")] = '\0';
    
        printf("Digite o ano de publicação do livro: ");
    
        if(!(scanf("%d", &(*livros)[codigo].anoPublicacao)) || (*livros)[codigo].anoPublicacao < 0 || (*livros)[codigo].anoPublicacao > anoAtual) {
            clearBuffer();
    
            mensagem("Entrada inválida. Por favor, insira um número para o ano de publicação.");
            continue;
        }
    
        printf("Digite a quantidade disponível do livro: ");
    
        if(!(scanf(" %d", &(*livros)[codigo].quantidadeDisponivel)) || (*livros)[codigo].quantidadeDisponivel < 0) {
            clearBuffer();
            
            mensagem("Entrada inválida. Por favor, insira um número para a quantidade disponível.\n");
            continue;
        }
        
        break;
    }

    tratarString((*livros)[codigo].titulo);
    tratarString((*livros)[codigo].autor);
    tratarString((*livros)[codigo].genero);

    if (buscarNomeDoLivro(*quantidadeDeLivros - 1, *livros, (*livros)[codigo].titulo, "verificar") >= 1) {
        (*quantidadeDeLivros)--;

        livro = (Livro *) realloc(*livros, *quantidadeDeLivros * sizeof(Livro));

        if (livro == NULL) {
            printf("Ocorreu um erro na alocação do ponteiro\n");
            return -1;
        }

        *livros = livro;

        clearBuffer();
        mensagem("Livro já existe no acervo.");
        return 0;
    }

    (*livros)[codigo].quantidadeDeEmprestimo = 0;

    clearBuffer();
    mensagem("Livro cadastrado com sucesso!");
    return 0;
}

// Função para listar todos os livros do sistema
int listarLivros(int *quantidadeDeLivros, Livro **livros) {
    imprimirArquivo("menus/livros.txt");
    printf("          Livros da Biblioteca\n");
    printf("_______________________________________\n\n");

    clearBuffer();

    for (int i = 0; i < *quantidadeDeLivros; i++) {
        printf(VERDE "\nCódigo: " RESET "%d\n"
               NEGRITO BRANCO "Título: " RESET "%s\n"
               NEGRITO BRANCO "Autor: " RESET "%s\n"
               NEGRITO BRANCO "Gênero: " RESET "%s\n"
               NEGRITO BRANCO "Ano de Lançamento: " RESET "%d\n"
               NEGRITO BRANCO "Quantidade Disponível: " RESET "%d\n"
               NEGRITO BRANCO "Quantidade de Empréstimos: " RESET "%d\n\n",
                (*livros)[i].id,
                (*livros)[i].titulo,
                (*livros)[i].autor,
                (*livros)[i].genero,
                (*livros)[i].anoPublicacao,
                (*livros)[i].quantidadeDisponivel,
                (*livros)[i].quantidadeDeEmprestimo);
    }

    mensagem("Todos os livros foram listados.");

    return 0;
}

// Função para buscar livros: busca parcial e busca completa
int buscarLivro(int *quantidadeDeLivros, Livro **livros) {
    int resposta;

    while (1) {
        imprimirArquivo("menus/livros.txt");
        printf("            Buscar Livro\n");
        printf("_______________________________________\n\n");

        printf(" [1] Buscar livro por código \n");
        printf(" [2] Buscar livro por nome \n");
        printf(" [0] Voltar \n");
        printf("_______________________________________\n\n");

        printf(NEGRITO BRANCO "Informe a opção que deseja: " RESET);

        if (!(scanf(" %d", &resposta)) || resposta > 2 || resposta < 0) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número.");
            getchar();
            clear();
            continue;
        }

        clearBuffer();

        switch (resposta) {
            case 1: {
                int codigo;

                printf("\nInforme o código do livro: ");
                scanf("%d", &codigo);
                clearBuffer();

                int indice = buscarCodigoLivro(codigo, *quantidadeDeLivros, *livros);

                if (indice != -1) {
                    printf(VERDE "\nCódigo: " RESET "%d\n"
                           NEGRITO BRANCO "Título: " RESET "%s\n"
                           NEGRITO BRANCO "Autor: " RESET "%s\n"
                           NEGRITO BRANCO "Gênero: " RESET "%s\n"
                           NEGRITO BRANCO "Ano de Lançamento: " RESET "%d\n"
                           NEGRITO BRANCO "Quantidade Disponível: " RESET "%d\n"
                           NEGRITO BRANCO "Quantidade de Empréstimos: " RESET "%d\n\n",
                            (*livros)[indice].id, (*livros)[indice].titulo, (*livros)[indice].autor,
                            (*livros)[indice].genero, (*livros)[indice].anoPublicacao,
                            (*livros)[indice].quantidadeDisponivel, (*livros)[indice].quantidadeDeEmprestimo);

                    mensagem("Livro encontrado com sucesso!");
                } else {
                    mensagem("O livro não foi encontrado ou não existe no sistema.");
                }
                break;
            }
            case 2: {
                char nome[TAMANHO_TITULO];

                printf("\nInforme o nome do livro: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int encontrados = buscarNomeDoLivro(*quantidadeDeLivros, *livros, nome, "listar");

                if (encontrados > 0) {
                    mensagem("Livro(s) encontrado(s) com sucesso!");
                } else {
                    mensagem("O livro não foi encontrado ou não existe no sistema.");
                }
                break;
            }
            case 0:
                clear();
                return 0;
            default:
                mensagem("Entrada inválida. Por favor, informe um número válido");
                continue;
        }
    }

    return 0;
}

// Função para atualizar informações de um livro existente
int atualizarLivro(int *quantidadeDeLivros, Livro **livros) {
    int resposta, codigo, indice;

    time_t horario = time(NULL);
    struct tm data = *localtime(&horario);
    int anoAtual = data.tm_year + 1900;

    while (1) {
        imprimirArquivo("menus/livros.txt");
        printf("              Atualizar Livro\n");
        printf("_________________________________________________\n\n");

        printf(" [1] Atualizar Título \n");
        printf(" [2] Atualizar Autor \n");
        printf(" [3] Atualizar Gênero \n");
        printf(" [4] Atualizar Ano de Lançamento \n");
        printf(" [5] Atualizar Quantidade de exemplares do livro\n");
        printf(" [0] Voltar \n");
        printf("_________________________________________________\n\n");

        printf(NEGRITO BRANCO "Informe a opção que deseja: " RESET);

        if (!(scanf("%d", &resposta)) || resposta < 0 || resposta > 5) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, informe um número válido.");
            continue;
        }

        if (resposta == 0) {
            break;
        }

        printf("\nInforme o código do livro: ");

        if (!(scanf("%d", &codigo))) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, informe um código válido");
            continue;
        }

        indice = buscarCodigoLivro(codigo, *quantidadeDeLivros, *livros);

        clearBuffer();

        if (indice == -1) {
            mensagem("O livro não foi encontrado ou não existe no sistema.");
            continue;
        }

        switch (resposta) {
            case 1:
                printf("\nInforme o novo título: ");
                fgets((*livros)[indice].titulo, sizeof((*livros)[indice].titulo), stdin);
                (*livros)[indice].titulo[strcspn((*livros)[indice].titulo, "\n")] = '\0';

                tratarString((*livros)[indice].titulo);
                
                mensagem("Título atualizado com sucesso!");
                continue;
            case 2:
                printf("\nInforme o novo nome do autor: ");
                fgets((*livros)[indice].autor, sizeof((*livros)[indice].autor), stdin);
                (*livros)[indice].autor[strcspn((*livros)[indice].autor, "\n")] = '\0';

                tratarString((*livros)[indice].autor);
                
                mensagem("Autor atualizado com sucesso!");
                continue;
            case 3:
                printf("\nInforme o novo gênero literário: ");
                fgets((*livros)[indice].genero, sizeof((*livros)[indice].genero), stdin);
                (*livros)[indice].genero[strcspn((*livros)[indice].genero, "\n")] = '\0';

                tratarString((*livros)[indice].genero);
                
                mensagem("Gênero literário atualizado com sucesso!");
                continue;
            case 4:
                printf("\nInforme o novo ano de lançamento: ");

                if (!(scanf("%d", &(*livros)[indice].anoPublicacao)) || (*livros)[indice].anoPublicacao < 0 || (*livros)[indice].anoPublicacao > anoAtual){
                    clearBuffer();
                    mensagem("Entrada inválida. Por favor, informe uma resposta válida");
                }
                
                clearBuffer();
                mensagem("Ano de lançamento atualizado com sucesso!");

                continue;
            case 5:
                int novaQtdDeLivros, opcao;

                printf("\nAtualizar quantidade de exemplares do livro\n");
                printf("  [1] Adicionar mais exemplares. \n  [2] Remover exemplares. \n  [0] Voltar");
                printf("\n_____________________________________________________");
                printf(NEGRITO BRANCO "\n\nInforme a opção que deseja: " RESET);
                
                if (!(scanf("%d", &opcao)) || opcao < 0 || opcao > 2){
                        clearBuffer();
                        mensagem("Entrada inválida. Por favor, informe uma opção válida");

                        continue;
                    }

                if(opcao == 1){
                    printf("\nInforme a quantidade de exemplares que deseja adicionar: ");

                    if (!(scanf("%d", &novaQtdDeLivros)) || novaQtdDeLivros < 0){
                        clearBuffer();
                        mensagem("Quantidade inválida. Por favor, informe uma quantidade válida");

                        continue;
                    }
                    
                    (*livros)[indice].quantidadeDisponivel += novaQtdDeLivros;

                    clearBuffer();
                    mensagem("Quantidade atualizada com sucesso!");

                    continue;

                } else if(opcao == 2){
                    printf("\nInforme a quantidade de exemplares que deseja remover: ");

                    if (!(scanf("%d", &novaQtdDeLivros)) || novaQtdDeLivros < 0 || (*livros)[indice].quantidadeDisponivel < novaQtdDeLivros){
                        clearBuffer();
                        mensagem("Quantidade inválida. Por favor, informe uma quantidade válida");

                        continue;
                    } 

                    (*livros)[indice].quantidadeDisponivel -= novaQtdDeLivros;

                    clearBuffer();
                    mensagem("Quantidade atualizada com sucesso!");

                    continue;

                } else{
                    return 0;
                }

            default:
                mensagem("Entrada inválida. Por favor, informe um número válido");
                continue;
        }
    }

    return 0;
}

// Função para remover livro do sistema
int removerLivro(int *quantidadeDeLivros, Livro **livros) {
    int codigo = 0;

    while (1) {
        imprimirArquivo("menus/livros.txt");
        printf("            Remover Livro\n");
        printf("_______________________________________\n\n");

        printf("Informe o código do livro: ");
        if (!(scanf("%d", &codigo)) || codigo < 0) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um código válido.");
            continue;
        }

        int indice = buscarCodigoLivro(codigo, *quantidadeDeLivros, *livros);

        clearBuffer();

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