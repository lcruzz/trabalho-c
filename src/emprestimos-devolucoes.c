#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/biblioteca.h"

int emprestimosDevolucoes(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int resposta = 0;

    while (1) {
        imprimirArquivo("data/menus/menu-emprestimos.txt");

        printf(NEGRITO BRANCO "Informe a opção que deseja: " RESET);
        
        if (!(scanf(" %d", &resposta)) || resposta > 5 || resposta < 0) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número válido.");
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
                clear();
                listarEmprestimosDeUmLivro(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
                break;
            case 0:
                clear();
                return 0;
            default:
                clearBuffer();
                mensagem("Opção inválida. Por favor, insira uma opção válida.");
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

    time_t horario = time(NULL);
    struct tm *data = localtime(&horario);

    // Realoca a memória do ponteiro *emprestimo com a memória necessária para alocar mais um livro
    Emprestimo *emprestimo = (Emprestimo *) realloc(*emprestimos, *quantidadeDeEmprestimos * sizeof(Emprestimo));

    if (emprestimo == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro\n");
        return -1;
    }

    *emprestimos = emprestimo;

    while (1) {
        imprimirArquivo("data/menus/emprestimos.txt");
        printf("                    Realizar Emprestimo\n");
        printf("_____________________________________________________________\n\n");

        printf("Informe a matrícula do aluno: ");

        if (!(scanf("%d", &matriculaUsuario))) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, informe um código válido.");
            continue;
        }

        indiceUsuario = buscarMatricula(matriculaUsuario, *quantidadeDeUsuarios, *usuarios);

        if (indiceUsuario == -1) {
            clearBuffer();
            mensagem("Usuário não encontrado.");
            continue;
        }

        printf("Informar o código do livro: ");

        if (!(scanf("%d", &codigoLivro))) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, informe um código válido.");
        }

        indiceLivro = buscarCodigoLivro(codigoLivro, *quantidadeDeLivros, *livros);
    
        if (indiceLivro == -1) {
            clearBuffer();
            mensagem("Livro não encontrado."); 
            continue;
        };

        (*emprestimos)[codigoEmprestimo].dataRetirada = mktime(data);
        
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
        imprimirArquivo("data/menus/emprestimos.txt");
        printf("                    Registrar Devolução\n");
        printf("_____________________________________________________________\n\n");

        printf("Informe o código do empréstimo: ");

        if (!(scanf("%d", &codigoEmprestimo)) || codigoEmprestimo < 0) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, informe um código válido.");
            continue;
        }

        indiceEmprestimo = buscarCodigoEmprestimo(codigoEmprestimo, *quantidadeDeEmprestimos, *emprestimos);

        clearBuffer();

        if (indiceEmprestimo > -1) {
            if ((*emprestimos)[indiceEmprestimo].devolvido == 's') {
                mensagem("Livro já foi devolvido.");
                continue;
            } else {
                indiceUsuario = buscarMatricula((*emprestimos)[indiceEmprestimo].matriculaUsuario, *quantidadeDeUsuarios, *usuarios);
                indiceLivro = buscarCodigoLivro((*emprestimos)[indiceEmprestimo].idLivro, *quantidadeDeLivros, *livros);

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
    time_t horario = time(NULL);
    int indiceLivro, indiceUsuario;
    struct tm dataRetirada, dataPrevista, dataDevolucao, dataAtual = *localtime(&horario);

    imprimirArquivo("data/menus/emprestimos.txt");
    printf("                   Empréstimos em Atraso\n");
    printf("_____________________________________________________________\n\n");

    for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
        dataRetirada = *localtime(&(*emprestimos)[i].dataRetirada);
        dataPrevista = *localtime(&(*emprestimos)[i].dataPrevista);

        if ((*emprestimos)[i].dataDevolucao != 0) {
            dataDevolucao = *localtime(&(*emprestimos)[i].dataDevolucao);
        } else {
            dataDevolucao.tm_mday = 0;
            dataDevolucao.tm_mon = -1;
        }

        if (difftime((*emprestimos)[i].dataPrevista, horario) < 0 && (*emprestimos)[i].dataDevolucao == 0) {
            indiceLivro = buscarCodigoLivro((*emprestimos)[i].idLivro, *quantidadeDeLivros, *livros);
            indiceUsuario = buscarMatricula((*emprestimos)[i].matriculaUsuario, *quantidadeDeUsuarios, *usuarios);
    
            printf(VERDE "Código: " RESET "%d"
                   NEGRITO BRANCO "\nTítulo do Livro: " RESET "%s"
                   NEGRITO BRANCO "\nNome do Usuário: " RESET "%s"
                   NEGRITO BRANCO "\nData de Empréstimo: " RESET "%d/%d"
                   NEGRITO BRANCO "\nData Prevista: " RESET "%d/%d"
                   NEGRITO BRANCO "\nData de Devolução: " RESET "%d/%d\n\n",
                    (*emprestimos)[i].id,
                    (*livros)[indiceLivro].titulo,
                    (*usuarios)[indiceUsuario].nome,
                    dataRetirada.tm_mday, dataRetirada.tm_mon + 1,
                    dataPrevista.tm_mday, dataPrevista.tm_mon + 1,
                    dataDevolucao.tm_mday, dataDevolucao.tm_mon + 1);
        }
    }

    clearBuffer();
    mensagem("Todos os empréstimos foram listados.");

    return 0;
}

// Função para listar todos os empréstimos
int listarTodosEmprestimos(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int indiceLivro, indiceUsuario;
    struct tm dataRetirada, dataPrevista, dataDevolucao;

    imprimirArquivo("data/menus/emprestimos.txt");
    
    for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
        dataRetirada = *localtime(&(*emprestimos)[i].dataRetirada);
        dataPrevista = *localtime(&(*emprestimos)[i].dataPrevista);

        if ((*emprestimos)[i].dataDevolucao != 0) {
            dataDevolucao = *localtime(&(*emprestimos)[i].dataDevolucao);
        } else {
            dataDevolucao.tm_mday = 0;
            dataDevolucao.tm_mon = -1;
        }


        indiceLivro  = buscarCodigoLivro((*emprestimos)[i].idLivro, *quantidadeDeLivros, *livros);
        indiceUsuario = buscarMatricula((*emprestimos)[i].matriculaUsuario, *quantidadeDeUsuarios, *usuarios);

        printf(VERDE "Código: " RESET "%d"
                NEGRITO BRANCO "\nTítulo do Livro: " RESET "%s"
                NEGRITO BRANCO "\nNome do Usuário: " RESET "%s"
                NEGRITO BRANCO "\nData de Empréstimo: " RESET "%d/%d"
                NEGRITO BRANCO "\nData Prevista: " RESET "%d/%d"
                NEGRITO BRANCO "\nData de Devolução: " RESET "%d/%d\n\n",
                    (*emprestimos)[i].id,
                    (*livros)[indiceLivro].titulo,
                    (*usuarios)[indiceUsuario].nome,
                    dataRetirada.tm_mday,dataRetirada.tm_mon + 1,
                    dataPrevista.tm_mday, dataPrevista.tm_mon + 1,
                    dataDevolucao.tm_mday, dataDevolucao.tm_mon + 1);
    }

    clearBuffer();
    mensagem("Todos os empréstimos foram listados.");

    return 0;
}

int listarEmprestimosDeUmLivro(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int indiceLivro, indiceUsuario, codigo;
    struct tm dataRetirada, dataPrevista, dataDevolucao;

    while (1) {
        imprimirArquivo("data/menus/emprestimos.txt");
    
        printf("Informe o código do livro: ");
    
        if (!(scanf("%d", &codigo)) || codigo < 0) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insirá um código válido.");
            continue;
        }
    
        indiceLivro = buscarCodigoLivro(codigo, *quantidadeDeLivros, *livros);
    
        clearBuffer();
    
        if (indiceLivro > -1) {
            for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
                dataRetirada = *localtime(&(*emprestimos)[i].dataRetirada);
                dataPrevista = *localtime(&(*emprestimos)[i].dataPrevista);
                dataDevolucao = *localtime(&(*emprestimos)[i].dataDevolucao);
        
                if ((*emprestimos)[i].idLivro == indiceLivro) {
                    indiceUsuario = buscarMatricula((*emprestimos)[i].matriculaUsuario, *quantidadeDeUsuarios, *usuarios);
            
                    printf(VERDE "Código: " RESET "%d"
                           NEGRITO BRANCO "\nTítulo do Livro: " RESET "%s"
                           NEGRITO BRANCO "\nNome do Usuário: " RESET "%s"
                           NEGRITO BRANCO "\nData de Empréstimo: " RESET "%d/%d"
                           NEGRITO BRANCO "\nData Prevista: " RESET "%d/%d"
                           NEGRITO BRANCO "\nData de Devolução: " RESET "%d/%d\n\n",
                            (*emprestimos)[i].id,
                            (*livros)[indiceLivro].titulo,
                            (*usuarios)[indiceUsuario].nome,
                            dataRetirada.tm_mday,dataRetirada.tm_mon + 1,
                            dataPrevista.tm_mday, dataPrevista.tm_mon + 1,
                            dataRetirada.tm_mday, dataDevolucao.tm_mon + 1);
                }
            }
        } else {
            mensagem("Livro não existe ou não possui nenhum empréstimo.");
            continue;
        }
    
        mensagem("Todos os empréstimos do livro foram listados.");
        return 0;
    }
}