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

        clearBuffer();

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
                buscarUsuario(quantidadeDeUsuarios, usuarios);
                break;
            case 4:
                clear();
                atualizarUsuario(quantidadeDeUsuarios, usuarios);
                break;
            case 5:
                clear();
                removerUsuario(quantidadeDeUsuarios, usuarios);
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

    // Realoca a memória no ponteiro *usuario com a quantidade necessária para alocar mais um usuario
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

int atualizarUsuario(int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int resposta, codigo;

    while (1) {
        printf("===============================\n");
        printf("       Atualizar Usario        \n");
        printf("===============================\n\n");
    
        printf("[1] Atualizar Nome \n");
        printf("[2] Atualizar Curso \n");
        printf("[0] Voltar para Gerenciar Usuarios \n\n");

        printf("Informe o campo do usuario: ");
    
        if (!(scanf("%d", &resposta)) || resposta < 0 || resposta > 4) {
            mensagem("Entrada inválida. Por favor, informe um número válido.");
            continue;
        }

        if (resposta == 0) {
            break;
        }
    
        printf("Informe o a matrícula do usuario: ");
    
        if (!(scanf("%d", &codigo)) || codigo < 0 || codigo > *quantidadeDeUsuarios - 1) {
            mensagem("Entrada inválida. Por favor, informe um código válido");
            continue;
        }

        clearBuffer();
        
        switch (resposta) {
            case 1:
                printf("Informe o nome: ");
                fgets((*usuarios)[codigo].nome, sizeof((*usuarios)[codigo].nome), stdin);
                (*usuarios)[codigo].nome[strcspn((*usuarios)[codigo].nome, "\n")] = '\0';
                clear();
                continue;
            case 2:
                printf("Informe o curso: ");
                fgets((*usuarios)[codigo].curso, sizeof((*usuarios)[codigo].curso), stdin);
                (*usuarios)[codigo].curso[strcspn((*usuarios)[codigo].curso, "\n")] = '\0';
                clear();
                continue;
            default:
                mensagem("Entrada inválida. Por favor, informe um número válido");
                continue;
        }

    }
    
    return 0;
}

int removerUsuario(int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int codigo = 0, indice = -1;

    while (1) {
        printf("=============================\n");
        printf("        Remover Usuario        \n");
        printf("=============================\n\n");
    
        printf("Informe a matrícula do aluno: ");
        if(!(scanf("%d", &codigo)) || codigo < 0 || codigo > *quantidadeDeUsuarios - 1) {
            mensagem("Entrada inválida. Por favor, insira um código válido.");
            continue;
        };
    
        for (int i = 0; i < *quantidadeDeUsuarios; i++) {
            if (codigo == (*usuarios)[i].matricula) {
                indice = i;
            }
        }
    
        if (indice > -1) {
            if ((*usuarios)[indice].emprestimosAtivos > 0) {
                mensagem("O usuário não pode ser removido do sistema, pois possui empréstimos ativos.");
    
                return 0;
            } else {
                for (int i = indice; i < *quantidadeDeUsuarios - 1; i++) {
                    (*usuarios)[i] = (*usuarios)[i + 1];
                }
            }
        } else {
            mensagem("Entrada inválida. Por favor, insira um código válido.");
            continue;
        }
    
        (*quantidadeDeUsuarios)--;
    
        Usuarios *usuario = (Usuarios *) realloc(*usuarios, *quantidadeDeUsuarios * sizeof(Usuarios));
    
        if (usuario == NULL) {
            printf("Ocorreu um erro na alocação do ponteiro\n");
            return -1;
        }
    
        *usuarios = usuario;
    
        mensagem("Usuario removido com sucesso.");
    
        return 0;
    }
}

int buscarUsuario(int *quantidadeDeUsuarios, Usuarios **usuarios) {
    int resposta;

    while(1){
        printf("====================================\n");
        printf("           Buscar Usuário           \n");
        printf("====================================\n\n");
        printf("[1] Buscar usuário por matricula \n");
        printf("[2] Buscar usuário por nome \n");
        printf("[0] Voltar \n");
    
        if (!(scanf(" %d", &resposta)) || resposta > 2 || resposta < 0) {
            clearBuffer();
            printf("Entrada inválida. Por favor, insira um número.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            clear();
            continue;
        }

        clearBuffer();

        if (resposta == 0) {
            break;

        } else if (resposta == 1) {
            int codigo;
            printf("\nInforme a matrícula do usuário: ");
            scanf("%d", &codigo);
            clearBuffer();
            
            buscarMatricula(*quantidadeDeUsuarios, *usuarios, codigo);
            
        } else if (resposta == 2) {
            char nome[100];
            printf("\nInforme o nome do usuário: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            buscarNomeDoUsuario(*quantidadeDeUsuarios, *usuarios, nome);
        }

        return 0;
    }
}