#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#pragma once

#include "gerenciar-livros.h"
#include "gerenciar-usuarios.h"
#include "emprestimos-devolucoes.h"

#define RESET    "\033[0m"
#define VERMELHO "\033[31m"
#define VERDE    "\033[38;2;57;255;20m"
#define AMARELO  "\033[33m"
#define AZUL     "\033[34m"
#define BRANCO   "\033[97m"
#define NEGRITO  "\033[1m"

// Funções para gerenciar livros

int gerenciarLivros(int *quantidadeDeLivros, Livro **livros);

int cadastrarLivro(int *quantidadeDeLivros, Livro **livros);

int removerLivro(int *quantidadeDeLivros, Livro **livros);

int listarLivros(int *quantidadeDeLivros, Livro **livros);

int buscarLivro(int *quantidadeDeLivros, Livro **livros);

int atualizarLivro(int *quantidadeDeLivros, Livro **livros);

// --------------------------------------------------------------------------------

// Funções utilitárias para gerenciar livros

int lerQuantidadeDeLivros(char *nomeArquivo);

int lerArquivoDeLivros(char *nomeArquivo, int quantidadeDeLivros, Livro livros[]);

int salvarLivros(char *nomeArquivo, int quantidadeDeLivros, Livro livros[]);

int ordenarLivros(int quantidadeDeLivros, Livro livros[]);

int buscarCodigoLivro(int codigo, int quantidadeDeLivros, Livro livros[]);

int buscarNomeDoLivro(int quantidadeDeLivros, Livro livros[], char *nome);

// --------------------------------------------------------------------------------

// Funções para gerenciar usuários

int gerenciarUsuarios(int *quantidadeDeUsuarios, Usuarios **usuarios);

int cadastrarUsuarios(int *quantidadeDeUsuarios, Usuarios **usuarios);

int removerUsuario(int *quantidadeDeUsuarios, Usuarios **usuarios);

int listarUsuarios(int *quantidadeDeUsuarios, Usuarios **usuarios);

int atualizarUsuario(int *quantidadeDeUsuarios, Usuarios **usuarios);

int buscarUsuario(int *quantidadeDeUsuarios, Usuarios **usuarios);

// --------------------------------------------------------------------------------

// Funções utilitárias para gerenciar usuários

int lerQuantidadeDeUsuarios(char *nomeArquivo);

int lerArquivoDeUsuarios(char *nomeArquivo, int quantidadeDeUsuarios, Usuarios usuarios[]);

int salvarUsuarios(char *nomeArquivo, int quantidadeDeUsuarios, Usuarios usuarios[]);

int ordenarUsuarios(int quantidadeDeUsuarios, Usuarios usuarios[]);

int buscarMatricula(int codigo, int quantidadeDeUsuarios, Usuarios usuarios[]);

int buscarNomeDoUsuario(int quantidadeDeUsuarios, Usuarios *usuarios, char *nome);

// --------------------------------------------------------------------------------

// Funções para gerenciar empréstimos e devoluções

int emprestimosDevolucoes(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int realizarEmprestimo(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int registrarDevolucao(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int listarEmprestimosEmAtraso(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int listarTodosEmprestimos(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int listarEmprestimosDeUmLivro(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

// --------------------------------------------------------------------------------

// Funções utilitárias para emprestimos e devoluções

int lerQuantidadeDeEmprestimos(char *nomeArquivo);

int lerArquivoDeEmprestimos(char *nomeArquivo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

int salvarEmprestimos(char *nomeArquivo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

int ordenarEmprestimos(int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

int buscarCodigoEmprestimo(int codigo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

// --------------------------------------------------------------------------------

// Funções para gerar relatórios

int relatorios();

// int livrosMaisEmprestados();

// int usuarioEmprestimosAtrasados();

// int livrosDisponiveis();

// int usuarioHistoricoDeEmprestimos();

// --------------------------------------------------------------------------------

// Funções utilitárias
void clear();

void clearBuffer();

void tratarString(char *str);

void mensagem(char mensagem[]);

void imprimirArquivo(char *nomeArquivo);

#endif