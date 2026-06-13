#include <stdio.h>
#include <stdlib.h>
#include "../include/biblioteca.h"


int main() {
    int resposta = 0;
    int quantidadeDeLivros = lerQuantidadeDeLivros("data/livros.bin");
    int quantidadeDeUsuarios = lerQuantidadeDeUsuarios("data/usuarios.bin");
    int quantidadeDeEmprestimos = lerQuantidadeDeEmprestimos("data/emprestimos.bin");

    Livro *livros = (Livro *) malloc(quantidadeDeLivros * sizeof(Livro));
    Usuarios *usuarios = (Usuarios *) malloc(quantidadeDeUsuarios * sizeof(Usuarios));
    Emprestimo *emprestimos = (Emprestimo *) malloc(quantidadeDeEmprestimos * sizeof(Emprestimo));

    lerArquivoDeLivros("data/livros.bin", quantidadeDeLivros, livros);
    ordenarLivros(quantidadeDeLivros, livros);

    lerArquivoDeUsuarios("data/usuarios.bin", quantidadeDeUsuarios, usuarios);
    ordenarUsuarios(quantidadeDeUsuarios, usuarios);

    lerArquivoDeEmprestimos("data/emprestimos.bin", quantidadeDeEmprestimos, emprestimos);
    ordenarEmprestimos(quantidadeDeEmprestimos, emprestimos);

    if (quantidadeDeEmprestimos > 0) {
        for (int i = 0; i < quantidadeDeEmprestimos; i++)    {
            printf("Código: %d | Data de Retirada: %d | Data Prevista: %d\n", emprestimos[i].id, emprestimos[i].dataRetirada, emprestimos[i].dataPrevista);
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
                emprestimosDevolucoes(&quantidadeDeEmprestimos, &emprestimos, &quantidadeDeLivros, &livros, &quantidadeDeUsuarios, &usuarios);
                break;
            case 4:
                break;
            case 0:
                salvarLivros("data/livros.bin", quantidadeDeLivros, livros);
                salvarUsuarios("data/usuarios.bin", quantidadeDeUsuarios, usuarios);
                salvarEmprestimos("data/emprestimos.bin", quantidadeDeEmprestimos, emprestimos);
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