/*
  SOLVE.C
  Implementation of maze solving operation
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "solve.h"


int **make2DIntArray(int rows, int columns)
{
	int** array = (int**) malloc(rows * sizeof(int *));
	int i;
	for(i = 0; i<rows; i++) {
		array[i] = (int*) malloc(columns * sizeof(int));
		int j=0;
		for(j=0; j<columns;j++)
			array[i][j] = READY;
	}
	
	return array;
}

char getNodeContent(struct maze* maze, int iNodeNumber)
{
	int nRow = iNodeNumber / maze->numcols;
	int nCol = iNodeNumber - (nRow * maze->numcols);
	if (maze->map[nRow][nCol] == MAZE_EXIT)
		return MAZE_PATH; 
	return maze->map[nRow][nCol];
}

void changeNodeContent(struct maze* maze, int iNodeNumber, char pathChar)
{
	int nRow = iNodeNumber / maze->numcols;
	int nCol = iNodeNumber - (nRow * maze->numcols);
	maze->map[nRow][nCol] = pathChar;
}

int getNodeStatusContent(int** mazeStatus, int iNodeNumber, int cols)
{
	int nRow = iNodeNumber / cols;
	int nCol = iNodeNumber - (nRow * cols);
	return mazeStatus[nRow][nCol];
}

void changeNodeStatus(int** mazeStatus, int iNodeNumber, int cols, int status)
{
	int nRow = iNodeNumber / cols;
	int nCol = iNodeNumber - (nRow * cols);
	mazeStatus[nRow][nCol] = status;
}

void shortestPath(struct maze* maze, int nodeStart, int nodeExit)
{
	int empty = 0;
	int rows = maze->numrows;
	int cols = maze->numcols;
	int maxsize = rows * cols;
	int Queue[maxsize];
	int Origin[maxsize];
	int i;

	for(i=0; i<maxsize;i++)
	{
		Queue[i] = 0;
		Origin[i]=0;
	}
	
	int front = 0;
	int rear= 0;
	
	// create array to hold the status of each grid point we have checked
	int** mazeStatus = make2DIntArray(rows, cols);
	
	Queue[rear] = nodeStart;
	Origin[rear] = -1;
	rear++;
	
	int current, left, right, top, down;
	
	while(front != rear )  // while the queue is not empty
	{
		if (current == 157)
			left = current;
		
		if (Queue[front] == nodeExit)
			break; // maze is solved
			
		current = Queue[front];
		left = current - 1;

		if (left >=0 && left/cols==current/cols) 	//if left node exists
		{
			if (getNodeContent(maze, left) == MAZE_PATH )
			{
				if (getNodeStatusContent(mazeStatus, left, cols) == READY)
					{
						Queue[rear] = left;
						Origin[rear] = current;
						changeNodeStatus(mazeStatus, left, cols, WAITING);
						rear++;
					}	
			}
		}
		
		right = current + 1;
		if (right < maxsize &&  (right / cols) == (current / cols) )
			{
				if (getNodeContent(maze, right) == MAZE_PATH) 
				{
					if (getNodeStatusContent(mazeStatus, right, cols) == READY)
						{
							Queue[rear] = right;
							Origin[rear] = current;
							changeNodeStatus(mazeStatus, right, cols, WAITING);
							rear++;
						}	
				}
			}
		
		top = current - cols;
		if (top >= 0 && top < maxsize)
			{
				if (getNodeContent(maze, top) == MAZE_PATH) 
				{
					if (getNodeStatusContent(mazeStatus, top, cols) == READY)
						{
							Queue[rear] = top;
							Origin[rear] = current;
							changeNodeStatus(mazeStatus, top, cols, WAITING);
							rear++;
						}	
				}
			}
			
		down = current + cols;
		if (down < maxsize && down > 0 )
			{
				if (getNodeContent(maze, down) == MAZE_PATH) 
				{
					if (getNodeStatusContent(mazeStatus, down, cols) == READY)
						{
							Queue[rear] = down;
							Origin[rear] = current;
							changeNodeStatus(mazeStatus, down, cols, WAITING);
							rear++;
						}	
				}
			}
		
		changeNodeStatus(mazeStatus, current, cols, PROCESSED);
		front++;
			
	}
	
	// Update the maze with the path
	current = nodeExit;
	changeNodeContent(maze, nodeExit, MAZE_TRAIL);
	for(i=front; i>=0; i--)
			{
				if (Queue[i]==current)
				{
					current=Origin[i];
					if (current==-1)		// maze is solved
						return;
					changeNodeContent(maze, current, MAZE_TRAIL);
				}
			}
	
	return;
}

void findPath(struct maze* theMaze)
{
	int iStartNode = theMaze->starty * theMaze->numcols + theMaze->startx;
	int iExitNode = theMaze->exity * theMaze->numcols + theMaze->exitx;
	
	return (shortestPath(theMaze, iStartNode, iExitNode));
}






