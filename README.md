# Trabalho Final - Sistema de Gerenciamento (PA) 📚 
Sistema de Gerenciamento de Biblioteca desenvolvido em C para cadastro, busca, listagem e persistência das informações sobre usuários, livros e empréstimos, além de oferecer relatórios.

## Índice
- [Visão Geral](#visão-geral)
- [Instalação e Execução](#instalação-e-execução)
- [Funcionalidades](#funcionalidades)
- [Como Usar](#como-usar)
- [Estrutura](#estrutura)

## Visão Geral
- Menu Principal ( Livros, Usuários, Empréstimos e Relatórios)
- Gerenciamento de Livros
- Gerenciamento de Usuários
- Gerenciamento de Empréstimos
- Criação de Relatórios


## Instalação e Execução
**Requisitos**: GCC ≥ 15.2.0 | Windows 11 / Linux Policorp | Make

```text
git clone https://github.com/lcruzz/trabalho-c.git
cd trabalho-c
make
./trabalho-c
```

## Funcionalidades
- Livros: cadastrar, remover, listar, atualizar e buscar livros
- Usuários: cadastrar, remover, listar, atualizar e buscar usuários
- Empréstimos e Devoluções: retirar, devolver, listar, listar atrasos e listar empréstimos de um livro
- Relatórios: listar livros disponíveis, mais emprestados e em atraso

## Como usar
### Cadastrar Livro
> **Título**: Crime e Castigo<br>
> **Autor**: Fiódor Dostoiévski<br>
> **Ano de Lançamento**: 1866<br>
> **Quantidade Disponível**: 26<br>

## Estrutura

```text
SISTEMA-GERENCIAMENTO-BIBLIOTECA/
├── data/
│   └── menus/
│       ├── emprestimos.bin
│       ├── livros.bin
│       └── usuarios.bin
├── include/
│   ├── biblioteca.h
│   ├── emprestimos-devolucoes.h
│   ├── gerenciar-livros.h
│   └── gerenciar-usuarios.h
├── relatorios/
│   ├── livros-disponiveis.txt
│   └── livros-mais-emprestados.txt
├── src/
│   ├── emprestimos-devolucoes.c
│   ├── gerar-relatorios.c
│   ├── gerenciar-livros.c
│   ├── gerenciar-usuarios.c
│   ├── main.c
│   ├── utils-emprestimos-devolucoes.c
│   ├── utils-livros.c
│   ├── utils-usuarios.c
│   └── utils.c
├── .gitignore
└── README.md
```

## Licença
UECE © 2026 Tiago e Lin