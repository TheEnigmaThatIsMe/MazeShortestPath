maze: main.c maze.c solve.c maze.h solve.h
	gcc -o maze maze.c solve.c main.c -I.
	
clean: 
	rm -rf *o maze
