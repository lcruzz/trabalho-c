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


// Funções utilitárias
void clear();

void clearBuffer();

void tratarString(char *str);

#endif