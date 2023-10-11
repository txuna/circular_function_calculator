all: program 

program: lex.yy.o parse.tab.o main.o node.o
	gcc -o program -g lex.yy.o parse.tab.o main.o node.o -lm


main.o: main.h main.c 
	gcc -c -o main.o main.c

node.o: main.h node.c 
	gcc -c -o node.o node.c

lex.yy.o: main.h lex.yy.c 
	gcc -c -o lex.yy.o lex.yy.c

parse.tab.o: main.h parse.tab.c
	gcc -c -o parse.tab.o parse.tab.c


clean: 
	rm *.o program