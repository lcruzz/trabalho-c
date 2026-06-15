#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/biblioteca.h"

int relatorios(){
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
                // livrosMaisEmprestados();
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