#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#pragma once

#include "gerenciar-livros.h"
#include "gerenciar-usuarios.h"


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

// --------------------------------------------------------------------------------

// Funções para gerenciar usuários
int gerenciarUsuarios();

// --------------------------------------------------------------------------------

// Funções para gerenciar empréstimos e devoluções
int emprestimosDevolucoes();

// --------------------------------------------------------------------------------

// Funções utilitárias
void clear();

void clearBuffer();

void tratarString(char *str);


void mensagem(char mensagem[]);

#endif