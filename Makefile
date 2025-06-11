CC = gcc
CFLAGS = -Wall -g -Isrc
LEX = flex
YACC = bison
LEX_SRC = src/lexer.l
YACC_SRC = src/parser.y
MAIN_SRC = src/main.c
OUTPUT = rpgmakerlang

all: $(OUTPUT)

$(OUTPUT): $(MAIN_SRC) lex.yy.c parser.tab.c
	$(CC) $(CFLAGS) -o $(OUTPUT) $(MAIN_SRC) lex.yy.c parser.tab.c

lex.yy.c: $(LEX_SRC)
	$(LEX) $(LEX_SRC)

parser.tab.c: $(YACC_SRC)
	$(YACC) -d $(YACC_SRC)

clean:
	rm -f $(OUTPUT) lex.yy.c parser.tab.c parser.tab.h

.PHONY: all clean