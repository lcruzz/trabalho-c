#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/biblioteca.h"

int gerenciarUsuarios(int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int resposta = 0;

    while (1) {
        printf("====================================\n");
        printf("  Gerenciar Usuários da Biblioteca  \n");
        printf("====================================\n\n");

        printf("[1] Cadastrar Usuário \n");
        printf("[2] Listar Todos os Usuários \n");
        printf("[3] Buscar Usuário \n");
        printf("[4] Atualizar Informações de um Usuário \n");
        printf("[5] Remover Usuário \n");
        printf("[0] Voltar ao Menu Principal \n\n");

        if (!(scanf(" %d", &resposta)) || resposta > 5 || resposta < 0) {
            mensagem("Entrada inválida. Por favor, insira um número válido.");
            continue;
        };

        switch (resposta) {
            case 1:
                clear();
                cadastrarUsuarios(quantidadeDeUsuarios, usuarios);
                break;
            case 2:
                clear();
                listarUsuarios(quantidadeDeUsuarios, usuarios);
                break;
            case 3:
                clear();
                // menuBuscarUsuario();
                break;
            case 4:
                clear();
                // atualizarUsuario(quantidadeDeUsuarios, usuarios);
                break;
            case 5:
                clear();
                // removerUsuario(quantidadeDeUsuarios, usuarios);
                break;
            case 0:
                clear();
                return 0;
            default:
                mensagem("Entrada inválida. Por favor, insira uma opção válida.");
                break;
        }

        clear();
    }

    return 0;
}

int cadastrarUsuarios(int *quantidadeDeUsuarios, Usuarios **usuarios){
    (*quantidadeDeUsuarios)++;
    int codigo = *quantidadeDeUsuarios - 1;

    // Realoca a memória no ponteiro *livro com a quantidade necessária para alocar mais um livro
    Usuarios *usuario = (Usuarios *) realloc(*usuarios, *quantidadeDeUsuarios * sizeof(Usuarios));

    if (usuario == NULL) {
        printf("Ocorreu um erro na alocação do ponteiro\n");
        return -1;
    }

    *usuarios = usuario;

    printf("===============================\n");
    printf("       Cadastrar Usuários      \n");
    printf("===============================\n\n");

    clearBuffer();
    
    (*usuarios)[codigo].matricula =  *quantidadeDeUsuarios - 1;
    
    printf("Digite o nome do aluno: ");
    fgets((*usuarios)[codigo].nome, sizeof((*usuarios)[codigo].nome), stdin);
    (*usuarios)[codigo].nome[strcspn((*usuarios)[codigo].nome, "\n")] = '\0';

    printf("Digite o curso do aluno: ");
    fgets((*usuarios)[codigo].curso, sizeof((*usuarios)[codigo].curso), stdin);
    (*usuarios)[codigo].curso[strcspn((*usuarios)[codigo].curso, "\n")] = '\0';

    (*usuarios)[codigo].emprestimosAtivos = 0;

    tratarString((*usuarios)[codigo].nome);
    tratarString((*usuarios)[codigo].curso);

    mensagem("Aluno cadastrado com sucesso!");

    return 0;
}

int listarUsuarios(int *quantidadeDeUsuarios, Usuarios **usuarios) {
    printf("====================================\n");
    printf("       Usuários da Biblioteca       \n");
    printf("====================================\n\n");

    for(int i = 0; i < *quantidadeDeUsuarios; i++) {
        printf("Matrícula: %d | Nome: %s | Curso: %s | Emprestimos ativos: %d\n",
                (*usuarios)[i].matricula,
                (*usuarios)[i].nome,
                (*usuarios)[i].curso,
                (*usuarios)[i].emprestimosAtivos);
    };

    mensagem("Todos os usuários foram listados.");

    return 0;
}

// int menuBuscarUsuario(){
//     int response = 0;

//     while(1){
//         printf("====================================\n");
//         printf("           Buscar Usuário           \n");
//         printf("====================================\n\n");
//         printf("[1] Buscar usuario por matricula \n");
//         printf("[2] Buscar usuario por nome \n");
//         printf("[0] Voltar \n");
    
//         if (!(scanf(" %d", &response)) || response > 2 || response < 0) {
//             clearBuffer();
//             printf("Entrada inválida. Por favor, insira um número.\n");
//             printf("Pressione Enter para continuar...");
//             getchar();
//             clear();
//             continue;
//         }

//         clearBuffer();

//         switch (response) {
//             case 1:
//                 clear();
//                 buscarUsuario(1);
//                 break;
//             case 2:
//                 clear();
//                 buscarUsuario(2);
//                 break;
//             case 0:
//                 clear();
//                 return 0;
//             default:
//                 printf("Entrada inválida. Por favor, insira um número.\n");
//                 printf("Pressione Enter para continuar...");
//                 getchar();
//                 clear();
//                 break;
//         }
//         clear();
//     }

//     return 0;
// }

// int buscarUsuario(int tipoBusca){
//     printf("====================================\n");
//     printf("           Buscar Usuário           \n");
//     printf("====================================\n\n");

//     char buscaNome[TAMANHO_NOME];
//     int encontrado = 0;
//     char linhaEncontrada[256];

//     if (tipoBusca == 1) {
//         int matricula;

//         printf("Informe a matricula: ");
//         scanf("%d", &matricula);
//         clearBuffer();
        
//         pesquisarMatricula(matricula, &encontrado, linhaEncontrada);

//     } else if (tipoBusca == 2) {
//         printf("Informe o nome do aluno: ");

//         fgets(buscaNome, sizeof(buscaNome), stdin);
//         buscaNome[strcspn(buscaNome, "\n")] = '\0';
        
//         pesquisarNome(buscaNome, &encontrado, linhaEncontrada);
//     }

//     // Verifica se o usuario foi encontrado
//     if(encontrado == 0){
//         printf("Usuario não encontrado.\n");

//     } else if(encontrado == 1){
//         printf("\nAluno encontrado!");
//         printf("\n%s", linhaEncontrada);

//     } else if(encontrado == -1){
//         printf("Erro ao abrir o arquivo de usuarios: data/usuarios.txt");
//     }

//     printf("\nPressione Enter para voltar ao menu...\n");
//     getchar();

//     return 0;
// }