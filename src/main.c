#include <stdio.h>
#include <stdlib.h>
#include "../include/biblioteca.h"


int main() {
    int response = 0;
    int quantidadeDeLivros = lerQuantidadeDeLivros("data/livros.bin");
    Livro *livros = (Livro *) malloc(lerQuantidadeDeLivros("data/livros.bin") * sizeof(Livro));

    lerArquivoDeLivros("data/livros.bin", quantidadeDeLivros, livros);

    if (quantidadeDeLivros > 0) {
        for (int i = 0; i < quantidadeDeLivros; i++) {
            printf("código: %d | título: %s | autor: %s | ano de lançamento: %d | quantidade: %d\n", livros[i].id, livros[i].titulo, livros[i].autor, livros[i].anoPublicacao, livros[i].quantidadeDisponivel);
        }
    }

    while (1) {
        printf("==========================================\n");
        printf("  Sistema de Gerenciamento de Biblioteca  \n");
        printf("==========================================\n\n");
    
        printf("[1] Gerenciar Livros \n");
        printf("[2] Gerenciar Usuários \n");
        printf("[3] Gerenciar Empréstimos e Devoluções \n");
        printf("[4] Relatórios \n");
        printf("[0] Sair \n\n");
    
        if (!(scanf(" %d", &response)) || response > 4 || response < 0) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número válido.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        }

        switch (response) {
            case 1:
                clear();
                gerenciarLivros(&quantidadeDeLivros, &livros);
                break;
            case 2:
                clear();
                gerenciarUsuarios();
                break;
            case 3:
                clear();
                emprestimosDevolucoes();
                break;
            case 4:
                break;
            case 0:
                salvarLivros("data/livros.bin", quantidadeDeLivros, livros);
                printf("Saindo do sistema. Até logo!\n");
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