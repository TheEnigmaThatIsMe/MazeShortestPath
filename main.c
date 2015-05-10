/*
  MAIN.C

  Main function for maze solver
*/

#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "solve.h"


int main(int argc, char *argv[]) {
    struct maze maze;

    if ( argc < 2 ) {
        puts("You must specify the filename of your maze");
        return EXIT_FAILURE;
    }
    else if ( argc > 2 ) {
        puts("Too many command line arguments");
        return EXIT_FAILURE;
    }

    GetMazeFromFile(argv[1], &maze);

	// Success on reading the array
	printf("Start Found: %i, %i \n", maze.startx, maze.starty);
	printf("Exit Found: %i, %i \n", maze.exitx, maze.exity);
	printf("Grid Size: %i, %i \n", maze.numrows, maze.numcols);

//    if ( solve(&maze) == MAZE_FOUNDEXIT )
//        puts("Found exit!");
//    else
//        puts("Can't reach exit!");
    PrintMaze(&maze);
	findPath(&maze);
    PrintMaze(&maze);
    FreeMaze(&maze);

    return EXIT_SUCCESS;
}
