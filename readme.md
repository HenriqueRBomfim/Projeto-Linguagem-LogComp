# 🎲 RPGMakerLang — Linguagem de Programação para RPG de Mesa

## Motivação

RPGMakerLang nasceu da vontade de unir programação e a criatividade dos jogos de RPG de mesa. A ideia é permitir que mestres e jogadores possam **roteirizar aventuras**, criar personagens, monstros, itens e eventos de forma simples, divertida e automatizada, usando uma linguagem inspirada no próprio universo dos RPGs.

## Características

- **Criação de entidades**: personagens, monstros e itens com atributos personalizados.
- **Definição de jogadores**: defina facilmente os nomes dos participantes da campanha.
- **Definição de variáveis**: suporte a inteiros, strings, booleanos e listas de strings.
- **Comandos de narrativa**: narre eventos e situações com o comando `narre`.
- **Condições**: estruturas `se` e `senao` para lógica de decisão.
- **Loops**: estrutura `enquanto` para repetições baseadas em condições.
- **Rolagem de dados**: função `rolar_dado(x)` para simular sorteios, como em jogos de RPG.
- **Sintaxe intuitiva**: comandos e palavras-chave em português, próximos do vocabulário de RPG.
- **Estrutura clara**: todo programa começa com `Campanha` e termina com `FimCampanha`.

## Curiosidades

- A linguagem foi criada usando **Flex** e **Bison**, ferramentas clássicas de construção de compiladores.
- O projeto foi pensado para ser facilmente expandido, permitindo a adição de novas entidades, comandos e funcionalidades.
- O comando `narre` permite criar uma experiência de narrativa interativa, tornando o roteiro mais dinâmico.
- O comando `jogadores = ["Nome1", "Nome2"]` facilita a configuração inicial da mesa de jogo.

## Exemplo de código

```plaintext
Campanha

jogadores = ["Alice", "Bob", "Carol"]

criar personagem Alice {
    vida = 20
    forca = 5
    mana = 10
}

criar personagem Bob {
    vida = 18
    forca = 7
    inventario = ["Espada", "Escudo"]
}

narre("Jogadores prontos para a aventura!")

definir inimigos int = 3

narre("Três goblins aparecem na estrada.")

se inimigos > 0 {
    narre("O herói se prepara para a batalha!")
}

FimCampanha
```

## Como usar

### Compilação

No terminal, execute:

```sh
make
```

### Execução

Após compilar, rode:

```sh
./rpgmakerlang example.camp
```

## Sobre o projeto

Este projeto utiliza Flex e Bison para análise léxica e sintática. O arquivo `example.camp` contém um exemplo de roteiro para você começar a criar sua própria aventura!

Divirta-se criando e narrando suas campanhas com a RPGMakerLang! 🎲✨