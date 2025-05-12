#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

int main(void) {
    printf("Iniciando a análise...\n");
    if (yyparse() == 0) {
        printf("Análise concluída com sucesso.\n");
    } else {
        printf("Erros encontrados durante a análise.\n");
    }
    return 0;
}