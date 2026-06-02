#ifndef GERENCIAR_LIVROS_H
#define GERENCIAR_LIVROS_H

#pragma once

#define TAMANHO_TITULO 128
#define TAMANHO_AUTOR 128

typedef struct {
    int id;
    char titulo[TAMANHO_TITULO];
    char autor[TAMANHO_AUTOR];
    int anoPublicacao;
    int quantidadeDisponivel;
} Livro;

#endif