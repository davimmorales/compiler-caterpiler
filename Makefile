compiler:
	bison -d -v -g cminus.y
	flex cminus.l
	gcc -o cminus *.c -ly -lfl -g
