#ifndef EMPRESTIMOS_DEVOLUCOES_H
#define EMPRESTIMOS_DEVOLUCOES_H

#pragma once

typedef struct {
    int id;
    int matriculaUsuario;
    int idLivro;
    int dataRetirada;
    int dataPrevista;
    int dataDevolucao;
    char devolvido;
} Emprestimo;

#endif