#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/biblioteca.h"

int relatorios(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios){
    int resposta = 0;

    while (1) {
        imprimirArquivo("data/menus/menu-relatorios.txt");

        printf(NEGRITO BRANCO "Informe o relatório que deseja gerar: " RESET);
        
        if (!(scanf(" %d", &resposta)) || resposta > 5 || resposta < 0) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        }

        switch (resposta) {
            case 1:
                clear();
                livrosMaisEmprestados(quantidadeDeLivros, livros);
                break;
            case 2:
                clear();
                usuariosEmprestimosAtrasados(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
                break;
            case 3:
                clear();
                livrosDisponiveis(quantidadeDeLivros, livros);
                break;
            case 4:
                clear();
                usuarioHistoricoDeEmprestimos(quantidadeDeEmprestimos, emprestimos, quantidadeDeLivros, livros, quantidadeDeUsuarios, usuarios);
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

// Função de gerar relatório de livros mais emprestados
int livrosMaisEmprestados(int *quantidadeDeLivros, Livro **livros) {
    clearBuffer();

    if (*quantidadeDeLivros == 0) {
        mensagem("Nenhum livro cadastrado no sistema.");
        return 0;
    }

    int *indices = (int *) malloc(*quantidadeDeLivros * sizeof(int));
    if (indices == NULL) {
        printf("Erro na alocação de memória.\n");
        return -1;
    }

    for (int i = 0; i < *quantidadeDeLivros; i++){
        indices[i] = i;
    }

    for (int i = 0; i < *quantidadeDeLivros - 1; i++){
        for (int j = 0; j < *quantidadeDeLivros - i - 1; j++){
            if ((*livros)[indices[j]].quantidadeDeEmprestimo < (*livros)[indices[j+1]].quantidadeDeEmprestimo){
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    FILE *arquivo = fopen("relatorios/livros-mais-emprestados.txt", "w");
    if (arquivo == NULL) {
        mensagem("Erro ao criar o arquivo de relatório.");
        free(indices);
        return -1;
    }

    time_t horario = time(NULL);
    struct tm *data = localtime(&horario);

    fprintf(arquivo, "RELATÓRIO - LIVROS MAIS EMPRESTADOS\n");
    fprintf(arquivo, "-------------------------------------\n");
    fprintf(arquivo, "Gerado em: %02d/%02d/%04d %02d:%02d:%02d\n\n",
            data->tm_mday, data->tm_mon + 1, data->tm_year + 1900,
            data->tm_hour, data->tm_min, data->tm_sec);

    int limite = (*quantidadeDeLivros < 50) ? *quantidadeDeLivros : 50;

    for (int i = 0; i < limite; i++) {
        int idx = indices[i];
        fprintf(arquivo, "%d.\n"
                         "TÍTULO: %s\n"
                         "AUTOR': %s\n"
                         "CÓDIGO DO LIVRO: %d\n"
                         "TOTAL DE EMPRÉSTIMOS: %d\n"
                         "-------------------------------------------------\n\n",
                            i + 1,
                            (*livros)[idx].titulo,
                            (*livros)[idx].autor,
                            (*livros)[idx].id,
                            (*livros)[idx].quantidadeDeEmprestimo);
    }

    fclose(arquivo);
    free(indices);

    int resposta;

    while(1){
        imprimirArquivo("data/menus/relatorios.txt");

        printf(VERDE "Relatório gerado com sucesso!\n\n" RESET);
        printf("Deseja exibi-lo na tela?\n");
        printf("  [1] Sim. \n  [2] Não.");
        printf("\n_____________________________________________________");
        printf(NEGRITO BRANCO "\n\nInforme a opção que deseja: " RESET);

        if (!(scanf(" %d", &resposta)) || resposta > 2 || resposta < 1) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        }

        clearBuffer();
        
        if(resposta == 1){
            clear();
            imprimirArquivo("relatorios/livros-mais-emprestados.txt");
            mensagem("Relatório exibido com sucesso!");
            break;
        } else{
            clear();
            imprimirArquivo("data/menus/relatorios.txt");
            mensagem("Acesse o arquivo do relatório em: biblioteca/relatorios/livros-mais-emprestados.txt");
            break;
        }

    }
    
    return 0;
}

// Função para gerar relatórios de livros disponíveis para emprestimo
int livrosDisponiveis(int *quantidadeDeLivros, Livro **livros) {
    clearBuffer();

    if (*quantidadeDeLivros == 0) {
        mensagem("Nenhum livro cadastrado no sistema.");
        return 0;
    }

    FILE *arquivo = fopen("relatorios/livros-disponiveis.txt", "w");
    if (arquivo == NULL) {
        mensagem("Erro ao criar o arquivo de relatório.");
        return -1;
    }

    time_t horario = time(NULL);
    struct tm *data = localtime(&horario);

    fprintf(arquivo, "RELATÓRIO - LIVROS DISPONÍVEIS PARA EMPRÉSTIMO\n");
    fprintf(arquivo, "--------------------------------------------------\n");
    fprintf(arquivo, "Gerado em: %02d/%02d/%04d %02d:%02d:%02d\n\n",
            data->tm_mday, data->tm_mon + 1, data->tm_year + 1900,
            data->tm_hour, data->tm_min, data->tm_sec);

    int contador = 0;

    for (int i = 0; i < *quantidadeDeLivros; i++) {
        if ((*livros)[i].quantidadeDisponivel > 0) {
            contador++;
            fprintf(arquivo, "%d.\n"
                             "TÍTULO: %s\n"
                             "AUTOR: %s\n"
                             "CÓDIGO DO LIVRO: %d\n"
                             "UNIDADES DISPONÍVEIS: %d\n"
                             "-------------------------------------------------\n\n",
                    contador,
                    (*livros)[i].titulo,
                    (*livros)[i].autor,
                    (*livros)[i].id,
                    (*livros)[i].quantidadeDisponivel);
        }
    }

    if (contador == 0) {
        fprintf(arquivo, "Nenhum livro disponível para empréstimo no momento.\n");
    }

    fclose(arquivo);

    int resposta;

    while (1) {
        imprimirArquivo("data/menus/relatorios.txt");

        printf(VERDE "Relatório gerado com sucesso!\n\n" RESET);
        printf("Deseja exibi-lo na tela?\n");
        printf("  [1] Sim. \n  [2] Não.");
        printf("\n_____________________________________________________");
        printf(NEGRITO BRANCO "\n\nInforme a opção que deseja: " RESET);

        if (!(scanf(" %d", &resposta)) || resposta > 2 || resposta < 1) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        }

        clearBuffer();

        if (resposta == 1) {
            clear();
            imprimirArquivo("relatorios/livros-disponiveis.txt");
            mensagem("Relatório exibido com sucesso!");
            break;
        } else {
            clear();
            imprimirArquivo("data/menus/relatorios.txt");
            mensagem("Acesse o arquivo do relatório em: biblioteca/relatorios/livros-disponiveis.txt");
            break;
        }
    }

    return 0;
}

int usuariosEmprestimosAtrasados(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    clearBuffer();

    if (*quantidadeDeEmprestimos == 0) {
        mensagem("Nenhum empréstimo cadastrado no sistema.");
        return 0;
    }

    FILE *arquivo = fopen("relatorios/usuarios-emprestimos-atrasados.txt", "w");
    if (arquivo == NULL) {
        mensagem("Erro ao criar o arquivo de relatório.");
        return -1;
    }

    time_t horario = time(NULL);
    struct tm dataRetirada, dataPrevista, dataDevolucao;
    struct tm dataAtual = *localtime(&horario);
    int indiceLivro, indiceUsuario;

    fprintf(arquivo, "RELATÓRIO - USUÁRIOS COM EMPRÉSTIMOS ATRASADOS\n");
    fprintf(arquivo, "--------------------------------------------------\n");
    fprintf(arquivo, "Gerado em: %02d/%02d/%04d %02d:%02d:%02d\n\n",
            dataAtual.tm_mday, dataAtual.tm_mon + 1, dataAtual.tm_year + 1900,
            dataAtual.tm_hour, dataAtual.tm_min, dataAtual.tm_sec);

    int contador = 0;

    for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
        if (difftime((*emprestimos)[i].dataPrevista, horario) < 0 && (*emprestimos)[i].dataDevolucao == 0) {

            indiceLivro = buscarCodigoLivro((*emprestimos)[i].idLivro, *quantidadeDeLivros, *livros);
            indiceUsuario = buscarMatricula((*emprestimos)[i].matriculaUsuario, *quantidadeDeUsuarios, *usuarios);

            if (indiceLivro < 0 || indiceLivro >= *quantidadeDeLivros ||
                indiceUsuario < 0 || indiceUsuario >= *quantidadeDeUsuarios) {
                continue;
            }

            // Converte datas apenas para exibição no relatório
            dataRetirada = *localtime(&(*emprestimos)[i].dataRetirada);
            dataPrevista = *localtime(&(*emprestimos)[i].dataPrevista);

            contador++;

            fprintf(arquivo, "%d.\n"
                             "NOME DO USUÁRIO: %s\n"
                             "CÓDIGO DO EMPRÉSTIMO: %d\n"
                             "TÍTULO DO LIVRO: %s\n"
                             "DATA DE EMPRÉSTIMO: %02d/%02d/%04d\n"
                             "DATA PREVISTA: %02d/%02d/%04d\n"
                             "-------------------------------------------------\n\n",
                    contador,
                    (*usuarios)[indiceUsuario].nome,
                    (*emprestimos)[i].id,
                    (*livros)[indiceLivro].titulo,
                    dataRetirada.tm_mday, dataRetirada.tm_mon + 1, dataRetirada.tm_year + 1900,
                    dataPrevista.tm_mday, dataPrevista.tm_mon + 1, dataPrevista.tm_year + 1900);
        }
    }

    if (contador == 0) {
        fprintf(arquivo, "Nenhum usuário com emprestimo em atraso encontrado.\n");
    }

    fclose(arquivo);

    int resposta;

    while (1) {
        imprimirArquivo("data/menus/relatorios.txt");

        printf(VERDE "Relatório gerado com sucesso!\n\n" RESET);
        printf("Deseja exibi-lo na tela?\n");
        printf("  [1] Sim. \n  [2] Não.");
        printf("\n_____________________________________________________");
        printf(NEGRITO BRANCO "\n\nInforme a opção que deseja: " RESET);

        if (!(scanf(" %d", &resposta)) || resposta > 2 || resposta < 1) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        }

        clearBuffer();

        if (resposta == 1) {
            clear();
            imprimirArquivo("relatorios/usuarios-emprestimos-atrasados.txt");
            mensagem("Relatório exibido com sucesso!");
            break;
        } else {
            clear();
            imprimirArquivo("data/menus/relatorios.txt");
            mensagem("Acesse o arquivo do relatório em: biblioteca/relatorios/usuarios-emprestimos-atrasados.txt");
            break;
        }
    }

    return 0;
}

// Função para gerar relatório de um usuário com emprestimo em atraso
int usuarioHistoricoDeEmprestimos(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios) {
    clearBuffer();

    if (*quantidadeDeEmprestimos == 0) {
        mensagem("Nenhum empréstimo cadastrado no sistema.");
        return 0;
    }

    if (*quantidadeDeUsuarios == 0) {
        mensagem("Nenhum usuário cadastrado no sistema.");
        return 0;
    }

    int matricula;
    imprimirArquivo("data/menus/relatorios.txt");
    printf(NEGRITO BRANCO "\nInforme a matrícula do usuário: " RESET);

    if (!(scanf(" %d", &matricula))) {
        clearBuffer();
        mensagem("Entrada inválida. Por favor, insira uma matrícula válida.");
        return -1;
    }

    int indiceUsuario = buscarMatricula(matricula, *quantidadeDeUsuarios, *usuarios);

    if (indiceUsuario < 0 || indiceUsuario >= *quantidadeDeUsuarios) {
        clearBuffer();
        mensagem("Usuário não encontrado.");
        return -1;
    }

    char nomeArquivo[128];
    sprintf(nomeArquivo, "relatorios/historico-usuario-%d.txt", matricula);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        mensagem("Erro ao criar o arquivo de relatório.");
        return -1;
    }

    time_t horario = time(NULL);
    struct tm dataAtual = *localtime(&horario);
    struct tm dataRetirada, dataPrevista, dataDevolucao;
    int indiceLivro;

    fprintf(arquivo, "RELATÓRIO - HISTÓRICO DE EMPRÉSTIMOS DO USUÁRIO\n");
    fprintf(arquivo, "--------------------------------------------------\n");
    fprintf(arquivo, "Gerado em: %02d/%02d/%04d %02d:%02d:%02d\n\n",
            dataAtual.tm_mday, dataAtual.tm_mon + 1, dataAtual.tm_year + 1900,
            dataAtual.tm_hour, dataAtual.tm_min, dataAtual.tm_sec);
    fprintf(arquivo, "NOME: %s\n", (*usuarios)[indiceUsuario].nome);
    fprintf(arquivo, "MATRÍCULA: %d\n", (*usuarios)[indiceUsuario].matricula);
    fprintf(arquivo, "CURSO: %s\n", (*usuarios)[indiceUsuario].curso);
    fprintf(arquivo, "--------------------------------------------------\n\n");

    int contador = 0;

    for (int i = 0; i < *quantidadeDeEmprestimos; i++) {
        if ((*emprestimos)[i].matriculaUsuario != matricula) {
            continue;
        }

        indiceLivro = buscarCodigoLivro((*emprestimos)[i].idLivro, *quantidadeDeLivros, *livros);

        if (indiceLivro < 0 || indiceLivro >= *quantidadeDeLivros) {
            continue;
        }

        dataRetirada = *localtime(&(*emprestimos)[i].dataRetirada);
        dataPrevista = *localtime(&(*emprestimos)[i].dataPrevista);

        contador++;

        if ((*emprestimos)[i].dataDevolucao != 0) {
            dataDevolucao = *localtime(&(*emprestimos)[i].dataDevolucao);

            fprintf(arquivo, "%d.\n"
                             "CÓDIGO DO EMPRÉSTIMO: %d\n"
                             "TÍTULO DO LIVRO: %s\n"
                             "DATA DE EMPRÉSTIMO: %02d/%02d/%04d\n"
                             "DATA PREVISTA: %02d/%02d/%04d\n"
                             "DATA DE DEVOLUÇÃO: %02d/%02d/%04d\n"
                             "STATUS: Devolvido\n"
                             "-------------------------------------------------\n\n",
                    contador,
                    (*emprestimos)[i].id,
                    (*livros)[indiceLivro].titulo,
                    dataRetirada.tm_mday, dataRetirada.tm_mon + 1, dataRetirada.tm_year + 1900,
                    dataPrevista.tm_mday, dataPrevista.tm_mon + 1, dataPrevista.tm_year + 1900,
                    dataDevolucao.tm_mday, dataDevolucao.tm_mon + 1, dataDevolucao.tm_year + 1900);
        } else {
            // Verifica se está em atraso
            char *status = (difftime((*emprestimos)[i].dataPrevista, horario) < 0) ? "Em atraso" : "Em andamento";

            fprintf(arquivo, "%d.\n"
                             "CÓDIGO DO EMPRÉSTIMO: %d\n"
                             "TÍTULO DO LIVRO: %s\n"
                             "DATA DE EMPRÉSTIMO: %02d/%02d/%04d\n"
                             "DATA PREVISTA: %02d/%02d/%04d\n"
                             "DATA DE DEVOLUÇÃO: -\n"
                             "STATUS: %s\n"
                             "-------------------------------------------------\n\n",
                    contador,
                    (*emprestimos)[i].id,
                    (*livros)[indiceLivro].titulo,
                    dataRetirada.tm_mday, dataRetirada.tm_mon + 1, dataRetirada.tm_year + 1900,
                    dataPrevista.tm_mday, dataPrevista.tm_mon + 1, dataPrevista.tm_year + 1900,
                    status);
        }
    }

    if (contador == 0) {
        fprintf(arquivo, "Nenhum empréstimo encontrado para este usuário.\n");
    }

    fclose(arquivo);

    int resposta;

    while (1) {
        imprimirArquivo("data/menus/relatorios.txt");

        printf(VERDE "Relatório gerado com sucesso!\n\n" RESET);
        printf("Deseja exibi-lo na tela?\n");
        printf("  [1] Sim. \n  [2] Não.");
        printf("\n_____________________________________________________");
        printf(NEGRITO BRANCO "\n\nInforme a opção que deseja: " RESET);

        if (!(scanf(" %d", &resposta)) || resposta > 2 || resposta < 1) {
            clearBuffer();
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        }

        clearBuffer();

        if (resposta == 1) {
            clear();
            imprimirArquivo(nomeArquivo);
            mensagem("Relatório exibido com sucesso!");
            break;
        } else {
            clear();
            imprimirArquivo("data/menus/relatorios.txt");

            char msgArquivo[180] = "Acesse o arquivo do relatório em: biblioteca/";
            strcat(msgArquivo, nomeArquivo);
            mensagem(msgArquivo);
            break;
        }
    }

    return 0;
}