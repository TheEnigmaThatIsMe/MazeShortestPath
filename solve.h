/*
  SOLVE.H

  Interface to maze solving operation
*/

#ifndef PG_SOLVE_H
#define PG_SOLVE_H

#include "maze.h"

#define READY 1
#define WAITING 2
#define PROCESSED 3


struct pathLocation {
    int x, y;
} ;

/*  Function declarations  */

int solve(struct maze * maze);
void findPath(struct maze * maze);


#endif  /*  PG_SOLVE_H  */
