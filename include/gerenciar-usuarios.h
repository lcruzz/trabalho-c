#ifndef GERENCIAR_USUARIOS_H
#define GERENCIAR_USUARIOS_H

#pragma once

#define TAMANHO_NOME 150
#define TAMANHO_CURSO 100

typedef struct{
    int matricula;
    char nome[TAMANHO_NOME];
    char curso[TAMANHO_CURSO];
    int emprestimosAtivos;
} Usuarios;

#endif