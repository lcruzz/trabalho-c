#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#pragma once

#include "gerenciar_livros.h"

int gerenciarLivros();

int cadastrarLivro();

void clear();

void clearBuffer();

void tratarString(char *str);

void retirarEspacoDasBordas(char *str);

#endif