#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/biblioteca.h"

int relatorios(int *quantidadeDeLivros, Livro **livros){
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
                // usuarioEmprestimosAtrasados();
                break;
            case 3:
                clear();
                // livrosDisponiveis();
                break;
            case 4:
                clear();
                // usuarioHistoricoDeEmprestimos();
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

    for (int i = 0; i < *quantidadeDeLivros - 1; i++) {
        for (int j = 0; j < *quantidadeDeLivros - i - 1; j++) {
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