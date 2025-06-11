%{
#include "blocks.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
%}

%option noyywrap

%%

"Campanha"          { return CAMPANHA; }
"FimCampanha"       { return FIM_CAMPANHA; }
"criar"             { return CRIAR; }
"personagem"        { return PERSONAGEM; }
"monstro"           { return MONSTRO; }
"item"              { return ITEM; }
"definir"           { return DEFINIR; }
"int"               { return INT; }
"string"            { return STRING; }
"bool"              { return BOOL; }
"narre"             { return NARRAR; }
"se"                { return SE; }
"senao"             { return SENAO; }
"enquanto"          { return ENQUANTO; }
"verdadeiro"        { return VERDADEIRO; }
"falso"             { return FALSO; }
"igual"             { return IGUAL; }
"ou"                { return OU; }
"e"                 { return E; }
"nao"               { return NAO; }
"rolar_dado"        { return ROLAR_DADO; }
"padrao"            { return PADRAO; }
"obstaculo"    { return OBSTACULO; }

"{"                 { return '{'; }
"}"                 { return '}'; }
"("                 { return '('; }
")"                 { return ')'; }
"="                 { return '='; }
"<"                 { return '<'; }
">"                 { return '>'; }
"!="                { return NEQ; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"["                 { return '['; }
"]"                 { return ']'; }
","                 { return ','; }
"."                 { return '.'; }

\"[^\"\n]*\"            {
                            char* s = strdup(yytext + 1); // Pula a primeira aspa
                            s[strlen(s) - 1] = '\0';    // Remove a última aspa
                            yylval.str = s;
                            return STRING_LITERAL;
                        }
[0-9]+              { yylval.int_val = atoi(yytext); return INTEGER; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFIER; }

\n                   

[ \t\r]+             
"//".*               

.

%%