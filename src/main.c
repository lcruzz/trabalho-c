#include <stdio.h>
#include <stdlib.h>
#include "../include/biblioteca.h"


int main() {
    int resposta = 0;
    int quantidadeDeLivros = lerQuantidadeDeLivros("data/livros.bin");
    int quantidadeDeUsuarios = lerQuantidadeDeUsuarios("data/usuarios.bin");

    Livro *livros = (Livro *) malloc(lerQuantidadeDeLivros("data/livros.bin") * sizeof(Livro));
    Usuarios *usuarios = (Usuarios *) malloc(lerQuantidadeDeUsuarios("data/usuarios.bin") * sizeof(Usuarios));

    lerArquivoDeLivros("data/livros.bin", quantidadeDeLivros, livros);
    ordenarLivros(quantidadeDeLivros, livros);

    lerArquivoDeUsuarios("data/usuarios.bin", quantidadeDeUsuarios, usuarios);
    ordenarUsuarios(quantidadeDeUsuarios, usuarios);

    while (1) {
        printf("==========================================\n");
        printf("  Sistema de Gerenciamento de Biblioteca  \n");
        printf("==========================================\n\n");
    
        printf("[1] Gerenciar Livros \n");
        printf("[2] Gerenciar Usuários \n");
        printf("[3] Gerenciar Empréstimos e Devoluções \n");
        printf("[4] Relatórios \n");
        printf("[0] Sair \n\n");
    
        if (!(scanf(" %d", &resposta)) || resposta < 0 || resposta > 4) {
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        }

        switch (resposta) {
            case 1:
                clear();
                gerenciarLivros(&quantidadeDeLivros, &livros);
                break;
            case 2:
                clear();
                gerenciarUsuarios(&quantidadeDeUsuarios, &usuarios);
                break;
            case 3:
                clear();
                emprestimosDevolucoes();
                break;
            case 4:
                break;
            case 0:
                salvarLivros("data/livros.bin", quantidadeDeLivros, livros);
                salvarUsuarios("data/usuarios.bin", quantidadeDeUsuarios, usuarios);
                printf("Saindo do sistema. Até logo!\n");
                return 0;
            default:
                mensagem("Opção inválida. Por favor, insira uma opção válida.");
                break;
        }

        clear();
    }

    return 0;
}