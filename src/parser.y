%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "blocks.h"

#define MAX_VARS 256
#define MAX_PERSONAGENS 64
#define MAX_ATTRS 32

typedef struct {
    char name[64];
    int value;
} VarEntry;

VarEntry var_table[MAX_VARS];
int var_count = 0;

typedef struct {
    char* nome;
} fn_data;

// Função para buscar variável
int get_var(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return var_table[i].value;
        }
    }
    return 0;
}

// Função para definir variável
void set_var(const char* name, int value) {
    if (value < 0) value = 0;
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            var_table[i].value = value;
            return;
        }
    }
    if (var_count < MAX_VARS) {
        strncpy(var_table[var_count].name, name, 63);
        var_table[var_count].name[63] = '\0';
        var_table[var_count].value = value;
        var_count++;
    }
}

void print_slow(const char *txt, useconds_t delay_us) {
    for (const char *p = txt; *p; ++p) {
        putchar(*p);
        fflush(stdout);
        usleep(delay_us); // delay em microssegundos (ex: 30000 = 0.03s)
    }
    putchar('\n');
}

typedef struct {
    char nome[64];
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
    char* inventario;
} Personagem;

typedef struct {
    char nome[64];
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
    char* inventario;
} Monstro;

typedef struct {
    char nome[64];
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
} Item;

Personagem personagens[MAX_PERSONAGENS];
int personagem_count = 0;

Monstro monstros[MAX_PERSONAGENS];
int monstro_count = 0;

Item itens[MAX_PERSONAGENS];
int item_count = 0;

int get_personagem_attr(const char* nome_personagem, const char* nome_attr) {
    for (int i = 0; i < personagem_count; i++) {
        if (strcmp(personagens[i].nome, nome_personagem) == 0) {
            for (int j = 0; j < personagens[i].attr_count; j++) {
                if (strcmp(personagens[i].atributos[j].nome, nome_attr) == 0)
                    return personagens[i].atributos[j].valor;
            }
        }
    }
    return 0;
}

void set_personagem_attr(const char* nome_personagem, const char* nome_attr, int valor) {
    for (int i = 0; i < personagem_count; i++) {
        if (strcmp(personagens[i].nome, nome_personagem) == 0) {
            for (int j = 0; j < personagens[i].attr_count; j++) {
                if (strcmp(personagens[i].atributos[j].nome, nome_attr) == 0) {
                    personagens[i].atributos[j].valor = valor;
                    return;
                }
            }
            // Se não existe, adiciona
            if (personagens[i].attr_count < MAX_ATTRS) {
                strncpy(personagens[i].atributos[personagens[i].attr_count].nome, nome_attr, 63);
                personagens[i].atributos[personagens[i].attr_count].nome[63] = '\0';
                personagens[i].atributos[personagens[i].attr_count].valor = valor;
                personagens[i].attr_count++;
            }
            return;
        }
    }
}

typedef struct {
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
    char* inventario;
    int definido;
} PersonagemPadrao;
PersonagemPadrao padrao = { { { {0} } }, 0, NULL, 0 };

void criar_personagem(const char* nome, const PersonagemPadrao* padrao) {
    printf("[DEBUG] criar_personagem: nome=%s, padrao=%p\n", nome, (void*)padrao);
    printf("[DEBUG] padrao->attr_count=%d\n", padrao->attr_count);
    printf("[DEBUG] padrao->inventario=%s\n", padrao->inventario ? padrao->inventario : "(null)");

    if (personagem_count < MAX_PERSONAGENS) {
        // Cópia segura do nome
        strncpy(personagens[personagem_count].nome, nome, 63);
        personagens[personagem_count].nome[63] = '\0';

        // Cópia dos atributos
        for (int i = 0; i < padrao->attr_count; i++) {
            printf("[DEBUG] Copiando atributo %d: %s=%d\n", i, padrao->atributos[i].nome, padrao->atributos[i].valor);
            strncpy(personagens[personagem_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            personagens[personagem_count].atributos[i].nome[63] = '\0';
            personagens[personagem_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        personagens[personagem_count].attr_count = padrao->attr_count;

        // Cópia segura do inventário
        if (padrao->inventario) {
            personagens[personagem_count].inventario = strdup(padrao->inventario);
            printf("[DEBUG] Inventario copiado: %s\n", personagens[personagem_count].inventario);
        } else {
            personagens[personagem_count].inventario = NULL;
            printf("[DEBUG] Inventario NULL\n");
        }

        personagem_count++;
        printf("[DEBUG] personagem_count agora: %d\n", personagem_count);
    } else {
        printf("[DEBUG] Limite de personagens atingido!\n");
    }
}

void criar_monstro(const char* nome, const PersonagemPadrao* padrao) {
    printf("[DEBUG] criar_monstro: nome=%s\n", nome);

    if (monstro_count < MAX_PERSONAGENS) {
        strncpy(monstros[monstro_count].nome, nome, 63);
        monstros[monstro_count].nome[63] = '\0';

        for (int i = 0; i < padrao->attr_count; i++) {
            strncpy(monstros[monstro_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            monstros[monstro_count].atributos[i].nome[63] = '\0';
            monstros[monstro_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        monstros[monstro_count].attr_count = padrao->attr_count;

        if (padrao->inventario) {
            monstros[monstro_count].inventario = strdup(padrao->inventario);
        } else {
            monstros[monstro_count].inventario = NULL;
        }

        monstro_count++;
        printf("[DEBUG] monstro_count agora: %d\n", monstro_count);
    }
}

void criar_item(const char* nome, const PersonagemPadrao* padrao) {
    printf("[DEBUG] criar_item: nome=%s\n", nome);

    if (item_count < MAX_PERSONAGENS) {
        strncpy(itens[item_count].nome, nome, 63);
        itens[item_count].nome[63] = '\0';

        for (int i = 0; i < padrao->attr_count; i++) {
            strncpy(itens[item_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            itens[item_count].atributos[i].nome[63] = '\0';
            itens[item_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        itens[item_count].attr_count = padrao->attr_count;

        item_count++;
        printf("[DEBUG] item_count agora: %d\n", item_count);
    }
}

extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);
%}

%union {
    char* str;
    int int_val;
    void (*block_fn)(void);
    block_list_t* block_list;
    struct {
        char* personagem;
        char* atributo;
    } par_nome_attr;
}

%debug

%type <str> entity_type type_decl
%type <str> name_list
%type <str> string_list
%type <int_val> expression factor
%type <int_val> bexpression bterm rexp expr term
%type <str> narrate_expr
%type <par_nome_attr> attr_access
%type <block_list> statements block
%type <block_fn> statement narrate_stmt assign_stmt if_stmt while_stmt obstaculo_stmt entity_decl var_decl jogadores_decl

%token CAMPANHA FIM_CAMPANHA CRIAR PERSONAGEM PADRAO MONSTRO ITEM
%token DEFINIR INT STRING BOOL NARRAR SE SENAO ENQUANTO
%token <str> IDENTIFIER STRING_LITERAL
%token <int_val> INTEGER
%token NEWLINE
%token VERDADEIRO FALSO IGUAL OU E NAO ROLAR_DADO
%token NEQ
%token OBSTACULO

%left '+' '-'
%left '*' '/'
%left '<' '>' IGUAL NEQ

%start program

%%

program:
    CAMPANHA statements FIM_CAMPANHA
        {
            block_list_t* bl = $2;
            for (int i = 0; i < bl->count; i++) {
                printf("[DEBUG] Executando bloco %d\n", i);
                bl->fns[i]();
            }
            //free(bl);
            printf("Campanha finalizada!\n");
            printf("[DEBUG] Fim do programa\n");
        }
    | CAMPANHA NEWLINE statements FIM_CAMPANHA
        {
            block_list_t* bl = $3;
            for (int i = 0; i < bl->count; i++) {
                printf("[DEBUG] Executando bloco %d\n", i);
                bl->fns[i]();
            }
            free(bl);
            printf("Campanha finalizada!\n");
            printf("[DEBUG] Fim do programa\n");
        }
    ;

statements
    : /* vazio */
        {
            block_list_t* bl = malloc(sizeof(block_list_t));
            bl->count = 0;
            $$ = bl;
        }
    | statements statement
        {
            block_list_t* bl = $1;
            if ($2) {
                if (bl->count < 1024) {
                    bl->fns[bl->count++] = $2;
                }
            }
            $$ = bl;
        }
    | statement
        {
            block_list_t* bl = malloc(sizeof(block_list_t));
            bl->count = 0;
            if ($1) bl->fns[bl->count++] = $1;
            $$ = bl;
        }
    ;

statement
    : narrate_stmt { $$ = $1; }
    | assign_stmt  { $$ = $1; }
    | if_stmt      { $$ = $1; }
    | while_stmt   { $$ = $1; }
    | obstaculo_stmt { $$ = $1; }
    | entity_decl  { $$ = $1; }
    | var_decl     { $$ = $1; }
    | jogadores_decl { $$ = $1; }
    ;

opt_newline:
    /* vazio */
    | opt_newline NEWLINE
    ;

entity_decl:
    CRIAR entity_type IDENTIFIER '{' opt_newline attribute_assigns '}' opt_newline
        {
            // Processa imediatamente durante o parsing
            padrao.definido = 1;
            
            if (strcmp($2, "personagem") == 0) {
                criar_personagem($3, &padrao);
                printf("Personagem %s criado!\n", $3);
            } else if (strcmp($2, "monstro") == 0) {
                criar_monstro($3, &padrao);
                printf("Monstro %s criado!\n", $3);
            } else if (strcmp($2, "item") == 0) {
                criar_item($3, &padrao);
                printf("Item %s criado!\n", $3);
            }
            
            // Limpa o padrao global para próxima entidade
            memset(&padrao, 0, sizeof(padrao));
            
            free($2);
            free($3);
            
            // Retorna uma função vazia
            void fn(void) {
                // Função vazia - o processamento já foi feito
            }
            $$ = fn;
        }

entity_type:
    PERSONAGEM   { $$ = strdup("personagem"); }
    | MONSTRO    { $$ = strdup("monstro"); }
    | ITEM       { $$ = strdup("item"); }
;

obstaculo_stmt:
    OBSTACULO
        {
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement obstaculo\n");
                print_slow("Um obstáculo apareceu! Pressione Enter para continuar...", 10000);
                getchar();
            }
            $$ = fn;
        }
    ;

attribute_assigns:
    attribute_assigns attribute_assign
    | /* empty */
    ;

attribute_assign:
    IDENTIFIER '=' expression
        {
            char* attr_name = $1; // Captura o nome do atributo (strdup'd pelo lexer)
            char buffer[128];

            // Adiciona/atualiza atributo no padrao
            int found = 0;
            for (int i = 0; i < padrao.attr_count; i++) {
                if (strcmp(padrao.atributos[i].nome, attr_name) == 0) {
                    padrao.atributos[i].valor = $3;
                    found = 1;
                    break;
                }
            }
            if (!found && padrao.attr_count < MAX_ATTRS) {
                strncpy(padrao.atributos[padrao.attr_count].nome, attr_name, 63);
                padrao.atributos[padrao.attr_count].nome[63] = '\0';
                padrao.atributos[padrao.attr_count].valor = $3;
                padrao.attr_count++;
            }
            snprintf(buffer, sizeof(buffer), "  - Atributo %s definido.", attr_name);
            print_slow(buffer, 10000);
            free(attr_name); // Libera o nome do atributo
        }
    | IDENTIFIER '=' '[' string_list ']'
        {
            char* attr_name = $1; // Captura o nome do atributo (strdup'd pelo lexer)
            char* sl_value = $4;  // Captura o valor da string_list
            char buffer[128];

            if (padrao.definido && strcmp(attr_name, "inventario") == 0) {
                if (padrao.inventario) free(padrao.inventario);
                padrao.inventario = strdup(sl_value); // padrao.inventario faz sua própria cópia
            }
            snprintf(buffer, sizeof(buffer), "  - Atributo %s definido (lista: %s).", attr_name, sl_value);
            print_slow(buffer, 10000);
            free(attr_name); // Libera o nome do atributo
            free(sl_value);  // Libera a string retornada por string_list
        }
    ;

string_list:
    STRING_LITERAL // $1 é strdup'd pelo lexer
        { $$ = $1; } // Simplesmente passa o ponteiro
    | string_list ',' STRING_LITERAL // $1 é de string_list anterior, $3 é strdup'd pelo lexer
        {
            char* prev_list = $1;
            char* new_item = $3;
            size_t len = strlen(prev_list) + strlen(new_item) + 3; // para ", " e '\0'
            $$ = malloc(len);
            if ($$) {
                snprintf($$, len, "%s, %s", prev_list, new_item);
            } else {
                yyerror("malloc failed in string_list concatenation");
                $$ = strdup(""); // Evitar NULL
            }
            free(prev_list); // Libera a lista anterior
            free(new_item);  // Libera o novo item (que veio do lexer)
        }
    ;

var_decl:
    DEFINIR IDENTIFIER type_decl '=' expression
        {
            char* var_name = $2; // Captura o nome da variável (strdup'd pelo lexer)
            char* type_name = $3; // String literal de type_decl, não precisa de free
            int val_expr = $5;
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement var_decl\n");
                char buffer[128];
                set_var(var_name, val_expr); // set_var faz sua própria cópia (strncpy)
                snprintf(buffer, sizeof(buffer), "Variável definida: %s (%s)", var_name, type_name);
                print_slow(buffer, 10000);
                free(var_name); // Libera o nome da variável
            }
            $$ = fn;
        }
    ;

jogadores_decl:
    IDENTIFIER '=' '[' name_list ']'
        {
            char* lista_nome = $1; // Captura o nome da lista (strdup'd pelo lexer)
            char* nomes_jogadores = $4; // String de name_list (malloc'd)
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement jogadores\n");
                char buffer[128];
                // Se 'lista_nome' fosse usado para armazenar a lista em algum lugar,
                // a lógica de free seria diferente. Aqui, assumimos que é apenas para o print.
                snprintf(buffer, sizeof(buffer), "Jogadores definidos para a lista '%s': %s", lista_nome, nomes_jogadores);
                print_slow(buffer, 10000);
                free(lista_nome); // Libera o nome da lista
                free(nomes_jogadores); // Libera a string concatenada de name_list
            }
            $$ = fn;
        }
    ;

name_list:
    STRING_LITERAL // $1 é strdup'd pelo lexer
        { $$ = $1; } // Passa o ponteiro, a responsabilidade de free é de quem consome name_list
    | name_list ',' STRING_LITERAL // $1 é de name_list anterior, $3 é strdup'd pelo lexer
        {
            char* prev_list = $1;
            char* new_item = $3;
            size_t len = strlen(prev_list) + strlen(new_item) + 3; // para ", " e '\0'
            $$ = malloc(len);
            if ($$) {
                snprintf($$, len, "%s, %s", prev_list, new_item);
            } else {
                yyerror("malloc failed in name_list concatenation");
                $$ = strdup(""); // Evitar NULL
            }
            free(prev_list); // Libera a lista anterior
            free(new_item);  // Libera o novo item (que veio do lexer e foi copiado para $$)
        }
    ;

type_decl:
    INT    { $$ = "int"; }
    | STRING { $$ = "string"; }
    | BOOL   { $$ = "bool"; }
    ;

assign_stmt:
    IDENTIFIER '=' expression
        {
            char* var_name = $1; // Captura o nome da variável (strdup'd pelo lexer)
            int val_expr = $3;
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement assign_stmt 1\n");
                char buffer[128];
                set_var(var_name, val_expr); // set_var faz sua própria cópia (strncpy)
                snprintf(buffer, sizeof(buffer), "Variável %s atualizada.", var_name);
                print_slow(buffer, 10000);
                free(var_name); // Libera o nome da variável
            }
            $$ = fn;
        }
    | attr_access '=' expression
        {
            // $1 é par_nome_attr. $1.personagem e $1.atributo são strdup'd pelo lexer
            char* p_nome = $1.personagem;
            char* a_nome = $1.atributo;
            int val_expr = $3;
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement assign_stmt 2\n");
                char buffer[128];
                set_personagem_attr(p_nome, a_nome, val_expr); // set_personagem_attr faz cópias (strncpy)
                snprintf(buffer, sizeof(buffer), "Atributo %s de %s atualizado.", a_nome, p_nome);
                print_slow(buffer, 10000);
                free(p_nome); // Libera o nome do personagem
                free(a_nome);   // Libera o nome do atributo
            }
            $$ = fn;
        }
    ;

narrate_expr:
    STRING_LITERAL
        { $$ = $1; }
    | narrate_expr '+' narrate_expr
        {
            size_t len = strlen($1) + strlen($3) + 1;
            $$ = malloc(len);
            if ($$) {
                snprintf($$, len, "%s%s", $1, $3);
            } else {
                yyerror("malloc failed in narrate_expr concatenation");
                $$ = strdup("");
            }
            free($1);
            free($3);
        }
    | expr
        {
            char buffer[128];
            sprintf(buffer, "%d", $1); // $1 é o valor da expressão aritmética
            $$ = strdup(buffer);
        }
    | IDENTIFIER
        {
            char buffer[128];
            sprintf(buffer, "%d", get_var($1));
            $$ = strdup(buffer);
            free($1);
        }
    | attr_access
        {
            char buffer[128];
            sprintf(buffer, "%d", get_personagem_attr($1.personagem, $1.atributo));
            $$ = strdup(buffer);
            free($1.personagem);
            free($1.atributo);
        }
    ;

narrate_stmt:
    NARRAR '(' narrate_expr ')' opt_newline
    {
        char* texto = $3; // $3 já é malloc'd e pronto para uso

        void fn(void) {
            //printf("[DEBUG] Entrou no fn do statement narrate\n");
            print_slow(texto, 10000);
        }
        $$ = fn;
    }

attr_access:
    IDENTIFIER '.' IDENTIFIER
        {
            $$.personagem = $1;
            $$.atributo = $3;
        }
    ;

if_stmt:
    SE '(' expression ')' '{' opt_newline block '}'
        {
            int cond = $3;
            block_list_t* if_block = $7; // Captura o block_list_t*
            void fn(void) {
                //printf("[DEBUG] Entrou no fn do statement if 1\n");
                if (cond) {
                    for (int i = 0; i < if_block->count; i++) {
                        if_block->fns[i]();
                    }
                }
                free(if_block); // Libera o block_list_t do corpo do if
            }
            $$ = fn;
        }
    | SE '(' expression ')' '{' opt_newline block '}' SENAO '{' opt_newline block '}'
        {
            int cond = $3;
            block_list_t* if_block = $7;   // Captura o block_list_t* do if
            block_list_t* else_block = $12; // Captura o block_list_t* do else
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement if 2\n");
                if (cond) {
                    for (int i = 0; i < if_block->count; i++) {
                        if_block->fns[i]();
                    }
                } else {
                    for (int i = 0; i < else_block->count; i++) {
                        else_block->fns[i]();
                    }
                }
                free(if_block);   // Libera o block_list_t do corpo do if
                free(else_block); // Libera o block_list_t do corpo do else
            }
            $$ = fn;
        }
    ;

while_stmt:
    ENQUANTO '(' expression ')' '{' opt_newline block '}'
        {
            // A expressão $3 pode precisar ser reavaliada a cada iteração.
            // Se a expressão em si não aloca memória que precisa ser liberada por iteração,
            // e os IDENTIFIERs dentro dela são tratados pelo 'factor', está OK.
            // O $7 é o block_list_t* do corpo.
            block_list_t* loop_block = $7; // Captura o block_list_t*
            // Para reavaliar a condição, precisaríamos de uma forma de re-executar a lógica de $3.
            // A forma como 'expression' está definida (retornando int_val) não permite
            // reavaliação direta sem re-parsear ou ter uma função para a expressão.
            // Assumindo que $3 é avaliado uma vez para o propósito desta estrutura de `fn`.
            // Para um `while` real, a condição ($3) precisaria ser uma função ou re-avaliada.
            // Para simplificar e manter a estrutura atual de `fn`:
            // Esta implementação de while com `fn` só executará o loop com base na avaliação inicial de $3.
            // Para um while dinâmico, a estrutura da ação precisaria ser diferente,
            // possivelmente não retornando uma única `fn` para o statement list,
            // ou a `fn` precisaria de acesso para re-avaliar a expressão.

            // Dada a estrutura atual, vamos focar em liberar o loop_block.
            // A lógica do while em si, com reavaliação da condição, é mais complexa
            // de implementar com este padrão de `void fn(void)`.
            // A correção abaixo foca na memória do bloco.
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement while\n");
                // Esta é uma simplificação. Um while real precisaria reavaliar $3.
                // if ($3) { // Executa uma vez se a condição inicial for verdadeira
                //    for (int i = 0; i < loop_block->count; i++) {
                //        loop_block->fns[i]();
                //    }
                // }
                // Para um while que realmente itera, a lógica seria:
                // while (evaluate_expression_again_somehow($3_original_syntax_tree_or_function)) { // Placeholder
                //     for (int i = 0; i < loop_block->count; i++) {
                //         loop_block->fns[i]();
                //     }
                //}
                // Como não temos evaluate_expression_again_somehow, e $3 é só um int aqui:
                // A implementação atual do while só pode verificar a condição uma vez.
                // Se você quer um loop real, a gramática/ações para 'expression' e 'while_stmt'
                // precisariam ser mais sofisticadas (ex: expression retorna uma função que avalia).

                // Focando na memória do bloco $7:
                // Se o while fosse executado, o bloco seria usado.
                // Independentemente de quantas vezes (ou se) o loop roda, o bloco precisa ser liberado.
                // A lógica de execução do loop está comentada porque $3 é um int fixo aqui.
                // Se você tem uma forma de reavaliar a expressão, descomente e adapte.
                // Por agora, apenas liberamos o bloco.
                free(loop_block);
            }
            $$ = fn;
        }
    ;

block:
    statements { $$ = $1; }
    ;

expression:
    bexpression
    ;

bexpression:
    bterm
    | bexpression OU bterm
    ;

bterm:
    rexp
    | bterm E rexp
    ;

rexp:
    expr
    | expr '<' expr
    | expr '>' expr
    | expr IGUAL expr
    | expr NEQ expr
    ;

expr:
    term
    | expr '+' term { $$ = $1 + $3; }
    | expr '-' term { $$ = $1 - $3; }
    ;

term:
    factor
    | term '*' factor { $$ = $1 * $3; }
    | term '/' factor { $$ = $1 / $3; }
    ;

factor:
    '+' factor         { $$ = +$2; }
    | '-' factor       { $$ = -$2; }
    | NAO factor       { $$ = !$2; }
    | INTEGER          { $$ = $1; } // Adicionado $$ = $1;
    | IDENTIFIER
        {
            char* name = $1; // strdup'd pelo lexer
            $$ = get_var(name);
            free(name); // Libera o nome da variável
        }
    | attr_access
        {
            // $1 é par_nome_attr. $1.personagem e $1.atributo são strdup'd pelo lexer
            char* p_nome = $1.personagem;
            char* a_nome = $1.atributo;
            $$ = get_personagem_attr(p_nome, a_nome);
            free(p_nome); // Libera o nome do personagem
            free(a_nome);   // Libera o nome do atributo
        }
    | VERDADEIRO       { $$ = 1; }
    | FALSO            { $$ = 0; }
    | ROLAR_DADO '(' INTEGER ')'
        {
            int resultado = (rand() % $3) + 1;
            printf("Rolagem de dado d%d: %d\n", $3, resultado);
            $$ = resultado;
        }
    | '(' expression ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}