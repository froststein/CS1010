/**
 * CS1010 Semester 1 AY20/21
 * Assignment 8: Walk
 *
 * The program will find the total number of possible paths 
 * given a destination x block to the east and y block to the north.
 * The program will attempt to find all possible paths from bottom left
 * to top right(x,y) position.
 *
 * @file: walk.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

/**
 * Find every possible path to take to (x,y) 
 * 
 * @param[in,out] count A 2D array to store possible paths
 * @param[in] x The number of x block to the east
 * @param[in] y The number of y block to the north
 *    
 * @pre x and y is more than 0
 * @post position of count[0][y-1] would contain total number of paths
 */
void countPath(long **count, long x, long y) {
   for (long k = (x - 2); k >= 0 ; k -= 1) {
      for (long l = 1; l < y; l += 1) {
         count[k][l] = count[k + 1][l] + count[k][l - 1];
      }
   }
}

/**
 * Free memory allocated to a 2D array
 * 
 * @param[out] arr The 2D array to be free
 * @param[in] x The number of rows in the 2D array
 */
void free_mem(long **arr, long x) {
   for (long i = 0; i < x; i += 1) {
      free(arr[i]);
   }
   free(arr);
}

int main() {
   long x = cs1010_read_long();
   long y = cs1010_read_long();
   // If any of the coordinate is 0, there is only 1 possible path(straight path)
   if (x == 0 || y == 0) {
      cs1010_println_long(1);
      return 0;
   }
   
   // Account for starting position
   x += 1;
   y += 1;
   long **count = malloc((size_t)x * sizeof(long));
   if (count == NULL) {
      free_mem(count, x);
      cs1010_println_string("Not enough memory");
      return -1;
   }

   for (long i = 0; i < x; i += 1) {
      count[i] = malloc((size_t)y * sizeof(long));
      if (count[i] == NULL) {
         free_mem(count, x);
         cs1010_println_string("Not enough memory");
         return -1;
      }
      for (long j = 0; j < y; j += 1) {
         count[i][j] = 1;
      }
   }
   
   countPath(count, x, y);
   cs1010_println_long(count[0][y - 1]);
   free_mem(count, x);
}
