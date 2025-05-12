%{
#include "parser.tab.h"
%}

%%
"Campanha"          { return CAMPANHA; }
"FimCampanha"      { return FIM_CAMPANHA; }
"criar"            { return CRIAR; }
"personagem"       { return PERSONAGEM; }
"monstro"          { return MONSTRO; }
"item"             { return ITEM; }
"definir"          { return DEFINIR; }
"narre"            { return NARRE; }
"se"               { return SE; }
"senao"            { return SENAO; }
"enquanto"         { return ENQUANTO; }
"{"                { return '{'; }
"}"                { return '}'; }
"("                { return '('; }
")"                { return ')'; }
"="                { return '='; }
"ou"              { return OU; }
"e"               { return E; }
"<"                { return '<'; }
">"                { return '>'; }
"igual"            { return IGUAL; }
"!="               { return NEQ; }
[0-9]+             { yylval.intval = atoi(yytext); return INTEGER; }
\"([^\\"]|\\.)*\"  { yylval.strval = strdup(yytext); return STRING; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.idval = strdup(yytext); return IDENTIFIER; }
[ \t\n]+           { /* ignore whitespace */ }
.                  { return yytext[0]; }
%% 