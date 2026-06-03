#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#pragma once

#include "gerenciar-livros.h"
#include "gerenciar-usuarios.h"

// Funções para gerenciar livros
int gerenciarLivros();

int cadastrarLivro();

// Funções para gerenciar usuários
int gerenciarUsuarios();

int cadastrarUsuarios();

int pegaUltimaMatricula();

int buscarUsuario(int tipoBusca);

int menuBuscarUsuario();

// Funções para gerenciar empréstimos e devoluções
int emprestimosDevolucoes();

// Funções utilitárias
void clear();

void clearBuffer();

void tratarString(char *str);

#endif