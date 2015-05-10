/*
  MAZE.H

  Interface to maze functions
*/

#ifndef PG_MAZE_H
#define PG_MAZE_H


/*  Structure definitions  */

struct maze {
    char ** map;
    int startx, starty;
    int exitx, exity;
    int numrows;
    int numcols;
    int initdir;
};

struct pos {
    int x, y, dir;
};


/*  Macros  */

#define BUFFERSIZE (1000)

#define MAZE_ENTRANCE 'S'
#define MAZE_EXIT     'E'
#define MAZE_WALL     '#'
#define MAZE_PATH     ' '
#define MAZE_TRAIL    '@'

#define MOVE_LEFT  (0)
#define MOVE_UP    (1)
#define MOVE_RIGHT (2)
#define MOVE_DOWN  (3)

#define MAZE_NOWAY      (0)
#define MAZE_FOUNDEXIT  (1)
#define MAZE_NOEXIT    (-1)


/*  Function declarations  */

void GetMazeFromFile(char * filename, struct maze * maze);
void FreeMaze(struct maze * maze);
void PrintMaze(struct maze * maze);


#endif  /*  PG_MAZE_H  */
