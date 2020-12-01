/**
 * CS1010 Semester 1 AY20/21
 * Assignment 8: Maze
 *
 * The program would read in 2 positive integers m and n, followed by m lines and
 * n characters in each line representing the maze steup. '@' would represent where 
 * scully is in the maze, '#' are the walls and '.' is the path scully can take.
 * The program would run k iterations and display where scully is walking in the maze and
 * finally print out the total steps taken to exit the maze.
 *
 * @file: maze.c
 * @author: Roy (Group BC1A)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows of the maze.
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps) {
    cs1010_clear_screen();
    for (long i = 0; i < nrows; i += 1) {
        cs1010_println_string(maze[i]);
    }
    cs1010_println_long(steps);

    // sleep only if we are displaying in the terminal
    if (isatty(fileno(stdout))) {
        usleep(100*1000);
    }
}

/**
 * Attempt to move a step in the maze with the given direction
 * 
 * @param[in,out] maze An array to store maze information
 * @param[in] cx The current x position
 * @param[in] cy The current y position
 * @param[in] dx The x direction to move
 * @param[in] dy The y direction to move
 * @param[out] steps The total number of steps taken
 *
 * @return true if can move, else false if cannot move in maze 
 */
bool moveOnce(char **maze, long cx, long cy, long dx, long dy, long *steps) {
   if (maze[cx + dx][cy + dy] != EMPTY) {
      return false;
   }
   // Update Scully's position   
   maze[cx + dx][cy + dy] = USER;
   // Update Scully's previous position
   maze[cx][cy] = EMPTY;
   *steps += 1;

   return true;
}

// Function prototype declaration for escape
bool escape(char **maze, bool **visited_maze, long row, long col, long cx, long cy, long *steps);

/** 
 * Update scully's position in the maze
 * 
 * @param[in] maze A 2D array information for the maze structure
 * @param[in,out] visited_maze A 2D array to track if scully has visited the cell
 * @param[in] row The number of rows in the maze
 * @param[in] col The number of cols in the maze
 * @param[in] cx The x position of scully
 * @param[in] cy The y position of scully
 * @param[in] dx The designated x position for scully to move
 * @param[in] dy The designated y position for scully to move
 * @param[in,out] steps The number of steps that scully has taken
 * 
 * @return true if scully can move, else scully is to backtracked and return false for not moving
 */
bool hasVisited(char **maze, bool **visited_maze, long row, long col, long cx, long cy, long dx, long dy, long *steps) {
   bool canMove = moveOnce(maze, cx, cy, dx, dy, steps);
   if (canMove) {
      print_maze(maze, row, *steps);
      if (escape(maze, visited_maze, row, col, (cx+dx), (cy+dy), steps)) {
         return true;
      }
      moveOnce(maze, (cx+dx), (cy+dy), -dx, -dy, steps);
      print_maze(maze, row, *steps);
   }
   return false;
}

/**
 * To attempt to escape the maze from a given position of x and y
 *
 * @param[in] maze A 2D array information for the maze structure
 * @param[in,out] visited_maze A 2D array to track if scully has visited the cell
 * @param[in] row The number of rows in the maze
 * @param[in] col The number of cols in the maze
 * @param[in] cx The x position of scully
 * @param[in] cy The y position of scully
 * @param[in,out] steps The number of steps that scully has taken
 * 
 * @return true if scully escaped, false if have not escaped
 */
bool escape(char **maze, bool **visited_maze, long row, long col, long cx, long cy, long *steps) {
   if (visited_maze != NULL && visited_maze[cx] != NULL) {
      visited_maze[cx][cy] = true;
   }
   
   if (cx == 0 || cx == (row - 1) || cy == 0 || cy == (col - 1)) {
      return true;
   }
   
   // 4 directions, up, right, down, left
   for (long k = 0; k < 4; k += 1) {

      char direction[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
      char dx = direction[k][0];
      char dy = direction[k][1];
      
      if (!visited_maze[cx + dx][cy + dy]) {
         bool hasVisit = hasVisited(maze, visited_maze, row, col, cx, cy, dx, dy, steps);
         if (hasVisit) {
            return true;
         }
      }
   }
   return false;
}

/**
 * Free memory allocated to a char 2D array
 * 
 * @param[out] arr The 2D char array to be free
 * @param[in] n The number of rows in the 2D array
 */
void free_mem_char(char **arr, long n) {
   for (long i = 0; i < n; i += 1) {
      free(arr[i]);
   }
   free(arr);
}

/**
 * Free memory allocated to a bool 2D array
 * 
 * @param[out] arr The 2D bool array to be free
 * @param[in] n The number of rows in the 2D array
 */
void free_mem_bool(bool **arr, long n) {
   for (long i = 0; i < n; i += 1) {
      free(arr[i]);
   }
   free(arr);
}

int main() {
   long m = cs1010_read_long();
   long n = cs1010_read_long();
   char **maze = calloc((size_t)m, sizeof(char *));
   bool **visited_maze = calloc((size_t)m, sizeof(bool *));
  
   // Check null for memory allocated
   if (maze == NULL || visited_maze == NULL) {
      free_mem_char(maze, m);
      free_mem_bool(visited_maze, m);
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }
   // scully's starting position
   long sx;
   long sy;
   bool found = false;
   for (long i = 0; i < m; i += 1) {
      maze[i] = cs1010_read_word();
      // Calloc makes all to 0, which means default is "false"
      visited_maze[i] = calloc((size_t)n, sizeof(bool));
      // Check null for memory allocated
      if (maze[i] == NULL || visited_maze[i] == NULL) {
         free_mem_char(maze, m);
         free_mem_bool(visited_maze, m);
         cs1010_println_string("Not enough memory allocated");
         return -1;
      }
      // Find scully's starting position in maze
      for (long j = 0; j < n && !false; j += 1) {
         if (maze[i][j] == '@') {
            sx = i;
            sy = j;
            found = true;
         }
      }
   }
   long steps = 0;
   print_maze(maze, m, steps);
   escape(maze, visited_maze, m, n, sx, sy, &steps);

   free_mem_char(maze, m);
   free_mem_bool(visited_maze, m);
}
