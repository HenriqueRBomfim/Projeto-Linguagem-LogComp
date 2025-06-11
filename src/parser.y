%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_VARS 256
#define MAX_PERSONAGENS 64
#define MAX_ATTRS 32

typedef struct {
    char name[64];
    int value;
} VarEntry;

VarEntry var_table[MAX_VARS];
int var_count = 0;

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

Personagem personagens[MAX_PERSONAGENS];
int personagem_count = 0;

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

typedef void (*block_fn_t)(void);

void criar_personagem(const char* nome, PersonagemPadrao* padrao) {
    if (personagem_count < MAX_PERSONAGENS) {
        strncpy(personagens[personagem_count].nome, nome, 63);
        personagens[personagem_count].nome[63] = '\0';
        // Copia todos os atributos do padrao para o personagem
        for (int i = 0; i < padrao->attr_count; i++) {
            strncpy(personagens[personagem_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            personagens[personagem_count].atributos[i].nome[63] = '\0';
            personagens[personagem_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        personagens[personagem_count].attr_count = padrao->attr_count;
        personagens[personagem_count].inventario = padrao->inventario ? strdup(padrao->inventario) : NULL;
        personagem_count++;
    }
}
extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);
%}

%debug

%type <str> entity_type type_decl
%type <str> name_list
%type <str> string_list
%type <int_val> expression factor
%type <int_val> bexpression bterm rexp expr term
%type <str> narrate_expr
%type <par_nome_attr> attr_access

%union {
    char* str;
    int int_val;
    struct {
        char* personagem;
        char* atributo;
    } par_nome_attr;
}

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
        { printf("Campanha finalizada!\n"); }
    | CAMPANHA NEWLINE statements FIM_CAMPANHA
        { printf("Campanha finalizada!\n"); }
    ;

statements:
    statements statement
    | /* empty */
    ;

statement:
    entity_decl opt_newline
    | var_decl opt_newline
    | assign_stmt opt_newline
    | narrate_stmt opt_newline
    | if_stmt opt_newline
    | while_stmt opt_newline
    | jogadores_decl opt_newline
    | obstaculo_stmt opt_newline
    ;

opt_newline:
    /* vazio */
    | opt_newline NEWLINE
    ;

entity_decl:
    CRIAR PERSONAGEM PADRAO '{' opt_newline attribute_assigns '}' opt_newline
        {
            padrao.definido = 1;
            print_slow("Padrão de personagem definido!", 10000);
        }
    | CRIAR PERSONAGEM PADRAO IDENTIFIER opt_newline
        {
            if (padrao.definido) {
                criar_personagem($4, &padrao);
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "Personagem %s criado com padrão.", $4);
                print_slow(buffer, 10000);
                for (int i = 0; i < padrao.attr_count; i++) {
                    snprintf(buffer, sizeof(buffer), "  - %s = %d", padrao.atributos[i].nome, padrao.atributos[i].valor);
                    print_slow(buffer, 10000);
                }
                if (padrao.inventario) {
                    snprintf(buffer, sizeof(buffer), "Inventario: [%s]", padrao.inventario);
                    print_slow(buffer, 10000);
                }
            } else {
                print_slow("Erro: padrão de personagem não definido!", 10000);
            }
        }
    | CRIAR entity_type IDENTIFIER '{' opt_newline attribute_assigns '}' opt_newline
        {
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "Entidade criada: %s (%s)", $3, $2);
            print_slow(buffer, 10000);
        }
    ;

entity_type:
    PERSONAGEM   { $$ = "personagem"; }
    | MONSTRO    { $$ = "monstro"; }
    | ITEM       { $$ = "item"; }
    ;

obstaculo_stmt:
    OBSTACULO
        {
            print_slow("Um obstáculo apareceu! Pressione Enter para continuar...", 10000);
            getchar();
        }
    ;

attribute_assigns:
    attribute_assigns attribute_assign
    | /* empty */
    ;

attribute_assign:
    IDENTIFIER '=' expression
        {
            char buffer[128];
            // Adiciona/atualiza atributo no padrao
            int found = 0;
            for (int i = 0; i < padrao.attr_count; i++) {
                if (strcmp(padrao.atributos[i].nome, $1) == 0) {
                    padrao.atributos[i].valor = $3;
                    found = 1;
                    break;
                }
            }
            if (!found && padrao.attr_count < MAX_ATTRS) {
                strncpy(padrao.atributos[padrao.attr_count].nome, $1, 63);
                padrao.atributos[padrao.attr_count].nome[63] = '\0';
                padrao.atributos[padrao.attr_count].valor = $3;
                padrao.attr_count++;
            }
            snprintf(buffer, sizeof(buffer), "  - Atributo %s definido.", $1);
            print_slow(buffer, 10000);
        }
    | IDENTIFIER '=' '[' string_list ']'
        {
            char buffer[128];
            if (padrao.definido && strcmp($1, "inventario") == 0) {
                if (padrao.inventario) free(padrao.inventario);
                padrao.inventario = strdup($4);
            }
            snprintf(buffer, sizeof(buffer), "  - Atributo %s definido (lista: %s).", $1, $4);
            print_slow(buffer, 10000);
            free($4);
        }
    ;

string_list:
    STRING_LITERAL
        { $$ = strdup($1); }
    | string_list ',' STRING_LITERAL
        {
            size_t len = strlen($1) + strlen($3) + 3;
            $$ = malloc(len);
            snprintf($$, len, "%s, %s", $1, $3);
            free($1);
        }
    ;

var_decl:
    DEFINIR IDENTIFIER type_decl '=' expression
        {
            char buffer[128];
            set_var($2, $5);
            snprintf(buffer, sizeof(buffer), "Variável definida: %s (%s)", $2, $3);
            print_slow(buffer, 10000);
        }
    ;

jogadores_decl:
    IDENTIFIER '=' '[' name_list ']'
        {
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "Jogadores definidos: %s", $4);
            print_slow(buffer, 10000);
            free($4);
        }
    ;

name_list:
    STRING_LITERAL
        { $$ = strdup($1); }
    | name_list ',' STRING_LITERAL
        {
            size_t len = strlen($1) + strlen($3) + 3;
            $$ = malloc(len);
            snprintf($$, len, "%s, %s", $1, $3);
            free($1);
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
            char buffer[128];
            set_var($1, $3);
            snprintf(buffer, sizeof(buffer), "Variável %s atualizada.", $1);
            print_slow(buffer, 10000);
        }
    | attr_access '=' expression
        {
            char buffer[128];
            set_personagem_attr($1.personagem, $1.atributo, $3);
            snprintf(buffer, sizeof(buffer), "Atributo %s de %s atualizado.", $1.atributo, $1.personagem);
            print_slow(buffer, 10000);
        }
    ;

narrate_expr:
    STRING_LITERAL
        { 
            char *txt = $1;
            if(txt && txt[0] == '"' && txt[strlen(txt)-1] == '"') {
                txt[strlen(txt)-1] = 0;
                $$ = strdup(txt+1);
            } else {
                $$ = strdup(txt);
            }
        }
    | narrate_expr '+' narrate_expr
        {
            size_t len = strlen($1) + strlen($3) + 1;
            $$ = malloc(len);
            snprintf($$, len, "%s%s", $1, $3);
            free($1); free($3);
        }
    | IDENTIFIER
        {
            char buffer[32];
            sprintf(buffer, "%d", get_var($1));
            $$ = strdup(buffer);
        }
    | attr_access
        {
            char buffer[32];
            sprintf(buffer, "%d", get_personagem_attr($1.personagem, $1.atributo));
            $$ = strdup(buffer);
        }
    ;

narrate_stmt:
    NARRAR '(' narrate_expr ')'
        {
            print_slow($3, 10000); // 10ms por caractere
            free($3);
        }
    ;

attr_access:
    IDENTIFIER '.' IDENTIFIER
        {
            $$.personagem = $1;
            $$.atributo = $3;
        }
    ;

if_stmt:
    SE '(' expression ')' '{' opt_newline statements '}'
        { if ($3) ; }
    | SE '(' expression ')' '{' opt_newline statements '}' SENAO '{' opt_newline statements '}'
        { if ($3) ; else ; }
    ;

while_stmt:
    ENQUANTO '(' expression ')' '{' opt_newline statements '}'
        { while ($3) { /* statements já executaram */ } }
    ;

block:
    statements
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
    | INTEGER
    | IDENTIFIER       { $$ = get_var($1); }
    | attr_access      { $$ = get_personagem_attr($1.personagem, $1.atributo); }
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