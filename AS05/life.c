/**
 * CS1010 Semester 1 AY20/21
 * Assignment 5: Life
 *
 * To simulate Conway's Game of Life for k number of times,
 * given a starting state.
 *
 * @file: life.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <unistd.h>
#include <stdbool.h>
#define ALIVE ('#')
#define DEAD ('.')

/*
 * Check if cell is alive or dead
 *
 * @param[in] cell The status of the cell
 *
 * @return Returns true if cell is ALIVE, else return false
 */
bool is_alive(char cell) {
   if (cell == ALIVE) {
      return true;
   }
   return false;
}

/*
 * To find the number of alive neighbours
 *
 * @param[in] universe The array of cell information
 * @param[in] row The row position of the cell that we are inspecting for neighbours
 * @param[in] col The col position of the cell that we are inspecting for neighbours
 *
 * @return The total number of alive neighbours of a cell
 */
long count_alive_neighbour(char **universe, long row, long col) {
   long alive_count = 0;
   for (long i = -1; i <= 1; i += 1) {
      for (long j = -1; j <= 1; j += 1) {
         if (i != 0 || j != 0) {
            if (is_alive(universe[row + i][col + j])) {
               alive_count += 1;
            }
         }
      }
   }
   return alive_count;
}

/*
 * To find the status of a cell whether its ALIVE, DEAD or no change
 *
 * @param[in] universe The array of cell information
 * @param[in] row The row position of the cell that we are inspecting 
 * @param[in] col The col position of the cell that we are inspecting
 * 
 * @return The new status of a cell (ALIVE or DEAD or no change)
 */
char update_cell(char **universe, long row, long col) {
   long count = count_alive_neighbour(universe, row, col);
   if (is_alive(universe[row][col])) {
      if (count < 2 || count > 3) {
         return DEAD;
      }
   } else {
      if (count == 3) {
         return ALIVE;
      }
   }
   // no change
   return universe[row][col];
}

/*
 * To swap the contents of 2 arrays
 *
 * @param[in,out] universe
 * @param[in,out] result_universe
 * @param[in] row The number of rows in the array
 * @param[in] col The number of cols in the array
 */
void swap(char **universe, char **result_universe, long row, long col) {
   for (long i = 0; i < row; i += 1) {
      // account for terminating char, therefore <=
      for (long j = 0; j <= col; j += 1) {
         char tmp = universe[i][j];
         universe[i][j] = result_universe[i][j];
         result_universe[i][j] = tmp;
      }
   }
}

/*
 * To print the 2D array out
 *
 * @param[in] universe They array of cell information
 * @param[in] row The number of rows in the array
 */
void print_universe(char **universe, long row) {
   for (long i = 0; i < row; i += 1) {
      cs1010_println_string(universe[i]);
   }
}

/*
 * To run 1 time of game of life
 * 
 * @param[in] universe An array of cell information
 * @param[out] result_universe A place to store the new states of cells
 * @param[in] row The number of rows in the array 
 * @param[in] col The number of cols in the array
 */
void run_game(char **universe, char **result_universe, long row, long col) {
   for (long i = 1; i < (row - 1); i += 1) {
      for (long j = 1; j < (col - 1); j += 1) {
         result_universe[i][j] = update_cell(universe, i ,j);
      }
   }
}

/*
 * To run k number of times for the game of life
 * 
 * @param[in] universe An array of cell information
 * @param[in] result_universe A copy of universe array
 * @param[in] row The number of rows in the array
 * @param[in] col The number of cols in the array
 * @param[in] k The number of time the game of life is simulated
 */
void k_simulation(char **universe, char **result_universe, long row, long col, long k) {
   for (long i = 0; i < k; i += 1) {
      cs1010_clear_screen();
      // run game will update result_universe with new cell information
      run_game(universe, result_universe, row, col);
      swap(universe, result_universe, row, col);
      print_universe(universe, row);
      
      usleep(250*1000);
   }
}

int main() {
   long row = cs1010_read_long();
   long col = cs1010_read_long();
   long k = cs1010_read_long();

   char **universe = cs1010_read_word_array(row);
   char **result_universe = calloc((size_t)row, sizeof(char *));
   
   // Checking if memory was assigned to these arrays
   if (universe == NULL || result_universe == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }
   
   for (long i = 0; i < row; i += 1) {
      // col + 1 for terminating char
      result_universe[i] = calloc((size_t)(col + 1), sizeof(char));
      // Checking if memory was assigned to the array
      if (result_universe[i] == NULL) {
         cs1010_println_string("Not enough memory");
         return 1;
      }
      for (long j = 0; j < col; j += 1) {
         result_universe[i][j] = universe[i][j];
      }
   }
   // Run Simulation 
   k_simulation(universe, result_universe, row, col, k);
   
   // Free memory
   for (long i = 0; i < row; i += 1) {
      free(universe[i]);
      free(result_universe[i]);
   }
   free(universe);
   free(result_universe);
}
