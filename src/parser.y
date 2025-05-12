%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
%}

%token CAMPANHA FIM_CAMPANHA CRIAR PERSONAGEM MONSTRO ITEM DEFINIR NARRE SE SENAO ENQUANTO
%token IDENTIFIER INTEGER STRING
%type <intval> expression

%%
program         : CAMPANHA statements FIM_CAMPANHA
               ;

statements      : statements statement
                | /* empty */
                ;

statement       : entity_decl
                | var_decl
                | assign_stmt
                | narrate_stmt
                | if_stmt
                | while_stmt
                | '{' statements '}'
                ;

entity_decl     : CRIAR entity_type IDENTIFIER '{' statements '}'
                ;

entity_type     : PERSONAGEM | MONSTRO | ITEM
                ;

var_decl        : DEFINIR IDENTIFIER type_decl '=' expression
                ;

type_decl       : "int" | "string" | "bool"
                ;

assign_stmt     : IDENTIFIER '=' expression
                ;

narrate_stmt    : NARRE '(' expression ')'
                ;

if_stmt         : SE expression '{' statements '}' SENAO '{' statements '}'
                ;

while_stmt      : ENQUANTO expression '{' statements '}'
                ;

expression      : IDENTIFIER
                | INTEGER
                | STRING
                ;

%% 

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    return yyparse();
}