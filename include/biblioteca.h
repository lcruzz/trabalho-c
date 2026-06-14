#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#pragma once

#include "gerenciar-livros.h"
#include "gerenciar-usuarios.h"
#include "emprestimos-devolucoes.h"


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

int buscaBinariaLivros(int codigo, int quantidadeDeLivros, Livro livros[]);

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

int buscarMatricula(int codigo, int *quantidadeDeUsuarios, Usuarios usuarios[]);

int buscarNomeDoUsuario(int quantidadeDeUsuarios, Usuarios *usuarios, char *nome);

// --------------------------------------------------------------------------------

// Funções para gerenciar empréstimos e devoluções
int emprestimosDevolucoes(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int realizarEmprestimo(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int registrarDevolucao(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int listarEmprestimosEmAtraso(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

int listarTodosEmprestimos(int *quantidadeDeEmprestimos, Emprestimo **emprestimos, int *quantidadeDeLivros, Livro **livros, int *quantidadeDeUsuarios, Usuarios **usuarios);

// --------------------------------------------------------------------------------

// Funções utilitárias para emprestimos e devoluções
int lerQuantidadeDeEmprestimos(char *nomeArquivo);

int lerArquivoDeEmprestimos(char *nomeArquivo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

int salvarEmprestimos(char *nomeArquivo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

int ordenarEmprestimos(int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

int buscaBinariaEmprestimos(int codigo, int quantidadeDeEmprestimos, Emprestimo emprestimos[]);

// --------------------------------------------------------------------------------

// Funções utilitárias
void clear();

void clearBuffer();

void tratarString(char *str);

void mensagem(char mensagem[]);

#endif