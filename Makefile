all: main

main: lexer.o parser.o main.o
	gcc -o main lexer.o parser.o main.o -lfl

lexer.o: src/lexer.l
	flex src/lexer.l
	mv lex.yy.c src/lexer.c
	gcc -c src/lexer.c

parser.o: src/parser.y
	bison -d src/parser.y
	gcc -c src/parser.tab.c

main.o: src/main.c
	gcc -c src/main.c

clean:
	rm -f *.o main src/parser.tab.c src/parser.tab.h src/lexer.c