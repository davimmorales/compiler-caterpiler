compiler:
	bison -d -v -g cminus.y
	flex cminus.l
	gcc -c lex.yy.c
	g++ cminus.tab.c lex.yy.o -o cminus 
