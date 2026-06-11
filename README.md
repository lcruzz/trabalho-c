# Trabalho Final - Sistema de Gerenciamento (PA)

## Funcionalidades
- Cadastrar, remover, buscar e atualizar livros
- Listar todos os livros do acervo
- Informar empréstimos para um livro
- Salvar e carregar acervo em um arquivo binário

## Estrutura


```text
SISTEMA-GERENCIAMENTO-BIBLIOTECA/
│
├── data/
│   └── livros.bin                 # Arquivo binário para armazenamento dos livros
│
├── include/
│   ├── biblioteca.h               # Definições gerais do sistema
│   ├── emprestimos-devolucoes.h   # Protótipos das funções de empréstimo/devolução
│   ├── gerenciar-livros.h         # Protótipos das funções de gerenciamento de livros
│   └── gerenciar-usuarios.h       # Protótipos das funções de gerenciamento de usuários
│
├── src/
│   ├── emprestimos-devolucoes.c   # Implementação das operações de empréstimo e devolução
│   ├── gerenciar-livros.c         # Implementação do gerenciamento de livros
│   ├── gerenciar-usuarios.c       # Implementação do gerenciamento de usuários
│   ├── main.c                     # Função principal e menu do sistema
│   ├── utils-livros.c             # Funções auxiliares relacionadas aos livros
│   └── utils.c                    # Funções utilitárias gerais
│
├── .gitignore                     # Arquivos ignorados pelo Git
└── README.md                      # Documentação do projeto
```