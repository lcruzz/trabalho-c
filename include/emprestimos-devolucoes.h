#ifndef EMPRESTIMOS_DEVOLUCOES_H
#define EMPRESTIMOS_DEVOLUCOES_H

#pragma once

#include <time.h>

typedef struct {
    int id;
    int matriculaUsuario;
    int idLivro;
    time_t dataRetirada;
    time_t dataPrevista;
    time_t dataDevolucao;
    char devolvido;
} Emprestimo;

#endif