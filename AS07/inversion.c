/**
 * CS1010 Semester 1 AY20/21
 * Assignment 7: Inversion
 *
 * The program would compute the number of inversions 
 * it takes to sort the given array.
 *
 * @file: inversion.c
 * @author: Roy Tang (Group BC1A)
 */

#include "cs1010.h"

/**
 * To count the number of inversions to sort the given array 
 *
 * @param[in] arr The input array of numbers
 * @param[in] n The size of the array
 *
 * @return The count of inversions to sort the array
 */
long countInversion(long arr[], long n) {
   long left = 0;
   long right = n - 1;
   long count = 0;
   while (left <= right) {
      if (arr[left] < arr[right]) {
         left += 1;
      } else {
         count += right - left;
         right -= 1;
      }
   }
   return count;
}

int main() {
   long n = cs1010_read_long();

   long *studId = malloc((size_t)n * sizeof(long)); 

   // Check if memory was allocated to the array
   if (studId == NULL) {
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }
   
   for (long i = 0; i < n; i += 1) {
      studId[i] = cs1010_read_long();
   }
   
   long count = countInversion(studId, n);
   cs1010_println_long(count);
   // Free memory
   free(studId);
}
