#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/biblioteca.h"

int emprestimosDevolucoes(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int resposta = 0;

    while (1) {
        printf("============================\n");
        printf("  Empréstimos e Devoluções  \n");
        printf("============================\n\n");

        printf("[1] Realizar Empréstimo \n");
        printf("[2] Registrar Devolução \n");
        printf("[3] Listar Empréstimos em Atraso \n");
        printf("[4] Listar Todos os Empréstimos \n");
        printf("[5] Informar Empréstimos de um Livro \n");
        printf("[0] Voltar ao Menu Principal \n\n");

        if (!(scanf(" %d", &resposta)) || resposta > 5 || resposta < 0) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número válido.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        }

        switch (resposta) {
            case 1:
                clear();
                realizarEmprestimo(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
                break;
            case 2:
                clear();
                registrarDevolucao(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
                break;
            case 3:
                clear();
                listarEmprestimosEmAtraso(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
                break;
            case 4:
                clear();
                listarTodosEmprestimos(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
                break;
            case 5:
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

int realizarEmprestimo(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    (*quantidadeDeEmprestimos)++;
    int codigoLivro, matriculaUsuario, indiceLivro, indiceUsuario;
    int codigoEmprestimo = *quantidadeDeEmprestimos - 1;

    time_t dataRetirada, horario = time(NULL);
    struct tm dataLocal = *localtime(&horario);
    struct tm *data = &dataLocal;

    Emprestimo *emprestimo = (Emprestimo *) realloc(*emprestimos, *quantidadeDeEmprestimos * sizeof(Emprestimo));

    if (emprestimo == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro\n");
        return -1;
    }

    *emprestimos = emprestimo;

    while (1) {
        printf("===================================\n");
        printf("        Realizar Emprestimo        \n");
        printf("===================================\n\n");

        printf("Informe a matrícula do aluno: ");

        if (!(scanf("%d", &matriculaUsuario))) {
            mensagem("Entrada inválida. Por favor, informe um código válido.");
        }

        indiceUsuario = buscarMatricula(matriculaUsuario, quantidadeDeUsuarios, *usuarios);

        if (indiceUsuario == -1) { mensagem("Usuário não encontrado."); continue; };

        clearBuffer();

        printf("Informar o código do livro: ");

        if (!(scanf("%d", &codigoLivro))) {
            mensagem("Entrada inválida. Por favor, informe um código válido.");
        }

        indiceLivro = buscaBinariaLivros(codigoLivro, *quantidadeDeLivros, *livros);
    
        if (indiceLivro == -1) { mensagem("Livro não encontrado."); continue; };

        dataRetirada = mktime(data);
        (*emprestimos)[codigoEmprestimo].dataRetirada = dataRetirada;
        
        (*data).tm_mday += 14;
        (*emprestimos)[codigoEmprestimo].dataPrevista = mktime(data);
        (*emprestimos)[codigoEmprestimo].id = codigoEmprestimo;
        (*emprestimos)[codigoEmprestimo].matriculaUsuario = matriculaUsuario;
        (*emprestimos)[codigoEmprestimo].idLivro = codigoLivro;
        (*emprestimos)[codigoEmprestimo].dataDevolucao = 0;
        (*emprestimos)[codigoEmprestimo].devolvido = 'n';

        (*livros)[indiceLivro].quantidadeDisponivel--;
        (*livros)[indiceLivro].quantidadeDeEmprestimo++;
        (*usuarios)[indiceUsuario].emprestimosAtivos++;

        clearBuffer();

        mensagem("Emprestimo realizado com sucesso.");

        return 0;
    }
}

int registrarDevolucao(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int codigoEmprestimo, indiceEmprestimo, indiceLivro, indiceUsuario;
    time_t horario = time(NULL);
    struct tm *data = localtime(&horario);

    while (1) {
        printf("===================================\n");
        printf("        Registrar Devolução        \n");
        printf("===================================\n\n");

        printf("Informe o código do empréstimo: ");

        if (!(scanf("%d", &codigoEmprestimo)) || codigoEmprestimo < 0) {
            mensagem("Entrada inválida. Por favor, informe um código válido.");
            continue;
        }

        indiceEmprestimo = buscaBinariaEmprestimos(codigoEmprestimo, quantidadeDeEmprestimos, *emprestimos);

        if (indiceEmprestimo > -1) {
            if ((*emprestimos)[indiceEmprestimo].devolvido == 's') {
                mensagem("Livro já foi devolvido.");
                continue;
            } else {
                indiceUsuario = buscarMatricula((*emprestimos)[indiceEmprestimo].matriculaUsuario, quantidadeDeUsuarios, *usuarios);
                indiceLivro = buscaBinariaLivros((*emprestimos)[indiceEmprestimo].idLivro, quantidadeDeLivros, *livros);

                (*emprestimos)[indiceEmprestimo].dataDevolucao = mktime(data);
                (*emprestimos)[indiceEmprestimo].devolvido = 's';
                (*usuarios)[indiceUsuario].emprestimosAtivos--;
                (*livros)[indiceLivro].quantidadeDeEmprestimo--;
                (*livros)[indiceLivro].quantidadeDisponivel++;
            }
        } else {
            mensagem("Entrada inválida. Por favor, informe um código válido.");
            continue;
        }

        mensagem("Livro devolvido com sucesso.");

        return 0;
    }
}

// Função para listar empréstimos em atraso
int listarEmprestimosEmAtraso(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int indiceLivro, indiceUsuario;

    printf("===========================\n");
    printf("        Empréstimos        \n");
    printf("===========================\n\n");

    for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
        indiceLivro = buscaBinariaLivros((*emprestimos)[i].idLivro, *quantidadeDeLivros, *livros);
        indiceUsuario = buscaBinariaUsuarios((*emprestimos)[i].matriculaUsuario, *quantidadeDeUsuarios, *usuarios);

        printf("Código: %d | Título do Livro: %s | Nome do Usuário: %s | Data de Empréstimo: %d | Data Prevista: %d | Data de Devolução: %d\n",
                (*emprestimos)[i].id,
                (*livros)[indiceLivro].titulo,
                (*usuarios)[indiceUsuario].nome,
                (*emprestimos)[i].dataRetirada,
                (*emprestimos)[i].dataPrevista,
                (*emprestimos)[i].dataDevolucao);
    }

    mensagem("Todos os empréstimos foram listados.");

    return 0;
}

// Função para listar todos os empréstimos
int listarTodosEmprestimos(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int indiceLivro, indiceUsuario;

    printf("===========================\n");
    printf("        Empréstimos        \n");
    printf("===========================\n\n");

    for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
        indiceLivro  = buscaBinariaLivros((*emprestimos)[i].idLivro, quantidadeDeLivros, *livros);
        indiceUsuario = buscarMatricula((*emprestimos)[i].matriculaUsuario, quantidadeDeUsuarios, *usuarios);

        printf("Código: %d | Título do Livro: %s | Nome do Usuário: %s | Data de Empréstimo: %ld | Data Prevista: %ld | Data de Devolução: %ld\n",
                (*emprestimos)[i].id,
                (*livros)[indiceLivro].titulo,
                (*usuarios)[indiceUsuario].nome,
                (*emprestimos)[i].dataRetirada,
                (*emprestimos)[i].dataPrevista,
                (*emprestimos)[i].dataDevolucao);
    }

    mensagem("Todos os empréstimos foram listados.");

    return 0;
}