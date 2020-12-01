/**
 * CS1010 Semester 1 AY20/21
 * Assignment 7: Sort
 *
 * Given an array that is in an increasing order followed by a decreasing order.
 * The program would sort the array of student IDs in O(n) time.
 *
 * @file: sort.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

/**
 * To sort an array that is in an increasing order followed by decreasing order. 
 *
 * @param[in] arr The input array of numbers to be sorted
 * @param[out] output The output array where the sorted numbers are stored
 * @param[in] n The size of the array
 */
void sortScript(long arr[], long output[],long n) {
   long left = 0;
   long right = n - 1;
   long pos = 0;
   while (left <= right) {
      if (arr[left] < arr[right]) {
         output[pos] = arr[left];
         left += 1;
      } else {
         output[pos] = arr[right];
         right -= 1;
      }
      pos += 1;
   }
}

/**
 * Function to the print array content
 * 
 * @param[in] arr The array to be printed
 * @param[in] n The size of the array
 */
void printArr(long arr[], long n) {
   for (long i = 0; i < n; i += 1) {
      cs1010_print_long(arr[i]);
      cs1010_print_string(" ");
   }
   cs1010_println_string("\n");
}

int main() {
   long n = cs1010_read_long();

   long *studId = malloc((size_t)n * sizeof(long)); 
   long *output = malloc((size_t)n * sizeof(long));

   // Check if memory was allocated to the array
   if (studId == NULL || output == NULL) {
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }
   
   for (long i = 0; i < n; i += 1) {
      studId[i] = cs1010_read_long();
   }
   
   sortScript(studId, output, n);
   printArr(output, n);
   
   // Free memory
   free(studId);
   free(output);
}
