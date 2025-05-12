# 📄 Descrição oficial da linguagem "RPGMakerLang"

## RPGMakerLang — Linguagem de Programação para RPG de Mesa

### Descrição

RPGMakerLang é uma linguagem temática criada para simular campanhas de RPG de mesa.  
Nela, o usuário pode criar personagens, monstros e itens, além de controlar o fluxo do jogo através de estruturas de decisão (`se`/`senao`) e repetição (`enquanto`).  
A linguagem é simples, intuitiva e usa termos próprios do universo de RPG para tornar a programação mais divertida e imersiva.

### Principais características

- **Criação de entidades**: personagens, monstros e itens.
- **Definição de variáveis**: números inteiros, strings e valores booleanos.
- **Comandos de narrativa**: impressão de eventos com o comando `narre`.
- **Condições**: `se` e `senao` para lógica de decisão.
- **Loops**: `enquanto` para repetições baseadas em condições.
- **Rolagem de dados**: função `rolar_dado(x)` para simular sorteios, como em jogos de RPG.

### Estrutura básica do programa

- Todo programa começa com `Campanha` e termina com `FimCampanha`.
- Dentro do programa, podem ser criadas entidades, variáveis, condições, loops e narrativas.

# Análise Léxica e Sintática

Este projeto utiliza Flex e Bison para realizar a análise léxica e sintática de uma nova linguagem definida em ebnf.txt.

## Compilação

Para compilar o projeto, execute o comando `make` no terminal.

## Execução

Após a compilação, execute o programa com `./main` e forneça um arquivo de entrada.

## Exemplo

O arquivo `example.camp` contém um exemplo de código na nova linguagem.
