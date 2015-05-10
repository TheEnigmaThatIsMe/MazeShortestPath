/*
  MAZE.C

  Implementation of maze functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "maze.h"


/*  Creates a maze from a file  */
int MAX_CHARS_PER_ROW = 50;
int MAX_ROWS = 10;
int DELTA_CHARS = 10;
int DELTA_ROWS = 5;


char **make2DArray(int rows, int columns)
{
	char **array = (char**) malloc(rows * sizeof(char *));
	int i;
	for(i = 0; i<rows; i++) {
		array[i] = (char*) malloc(columns * sizeof(char));
		memset(array[i], 0, columns);
	}
	
	return array;
}

void free2DArray(char** array, int rows) {

	int n;
    for ( n = 0; n < rows; n++ )
        free(array[n]);

    free(array);
}

void GetMazeFromFile(char * filename, struct maze * maze) 
{
	int success = 0;
	int number_of_rows = 0;
	int found_start = 0;
	int found_exit = 0;
	int iLoop = 0;
	
	char** ioMaze = NULL;
	
	while (success == 0)
	{
		// Initialize start and exit positions
		found_start = 0;
		found_exit = 0;

		success = 1; // assume that the maze is read in correctly, if not, set success to 0 so it tries again.
		
		FILE* fp = fopen(filename, "r");
		if(!fp) 
			{ 
			printf("There was a problem opening the file\n"); 
			exit(0); 
			} 
  
		int maze_size = sizeof(char) * (MAX_CHARS_PER_ROW) * (MAX_ROWS);
		
		// Allocate maze size
		ioMaze = make2DArray(MAX_ROWS, MAX_CHARS_PER_ROW);
		
	    char ioLine[MAX_CHARS_PER_ROW];
	    memset(ioLine, 0, MAX_CHARS_PER_ROW);
	    
	    // fgets reads in a line, including the newline character 
	    while( fgets((char*)ioLine, sizeof(ioLine), fp) )
	    {
				// get the length of the string that was read into the array (include newline char)
	            size_t len = strlen((char *)ioLine);

				if (len == (MAX_CHARS_PER_ROW - 1))
					{ 
					// It is possible that we have a string longer than the MAX_CHARS_PER_ROW size
					// The file needs to be reset with longer line lengths
					rewind(fp);
					MAX_CHARS_PER_ROW = MAX_CHARS_PER_ROW + DELTA_CHARS;
					number_of_rows = 0;
					free2DArray(ioMaze, MAX_ROWS);
					success = 0;
					break;
					}
					
				if (number_of_rows > (MAX_ROWS-1))
					{ 
					// It is possible that we have a string longer than the MAX_CHARS_PER_ROW size
					// The file needs to be reset with longer line lengths
					rewind(fp);
					free2DArray(ioMaze, MAX_ROWS);
					MAX_ROWS = MAX_ROWS + DELTA_ROWS;
					number_of_rows = 0;
					success = 0;
					break;
					}
	
				// replace a new line character at the end of the line 
				// with a null character on the string
	            if(len > 1 &&  ioLine[len-1] == '\n')
	                ioLine[len-1] = 0;
	
	            len = strlen((char *)ioLine);

				// The line we just read in falls with-in our grid array size, so add it to the grid
				memcpy(&ioMaze[number_of_rows][0], ioLine, len);
				
				// check for start / exit in maze
				if (!found_start)
				{
					for(iLoop = 0; iLoop<len; iLoop++)
						{
							if (ioMaze[number_of_rows][iLoop] == 'S')
							{
								maze->startx = iLoop;
								maze->starty = number_of_rows;
								found_start = 1;
							}
						}
				}

				if (!found_exit)
				{
					for(iLoop = 0; iLoop<len; iLoop++)
						{
							if (ioMaze[number_of_rows][iLoop] == 'E')
							{
								maze->exitx = iLoop;
								maze->exity = number_of_rows;
								found_exit = 1;
							}
						}
				}
				
				number_of_rows++;
	            // printf("(%d) \"%s\"  ", len, ioLine);
	    }
	    
	    fclose(fp);
    
	}
	
	// rows should return number of lines read into the array
	maze->numrows = number_of_rows;
	maze->numcols = MAX_CHARS_PER_ROW;
	maze->map = ioMaze;
	
	return ;
	
}

/*  Frees memory used by a maze  */

void FreeMaze(struct maze * maze) {
    int n;

    for ( n = 0; n < maze->numrows; n++ )
        free(maze->map[n]);

    free(maze->map);
}


/*  Outputs a maze  */

void PrintMaze(struct maze * maze) {
    int n;

    for ( n = 0; n < maze->numrows; ++n )
        puts(maze->map[n]);
}
