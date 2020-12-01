/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

void countingsort(long arr[], long n) {
   // integer range is always between 0 to 10000
   long counter[10000 + 1] = {0,};

   // looping through input array and using it's element as index for counter array
   for (long i = 0; i < n; i += 1) {
      counter[arr[i]] += 1;
   }

   for (long j = 0; j <= 10000; j += 1) {
      if (counter[j] != 0) {
         cs1010_print_long(j);
         cs1010_print_string(" ");
         cs1010_println_long(counter[j]);
      }
   }

   for (long i = 0; i <= 10000; i += 1) {
      for (long j = 0; j < counter[i]; j += 1) {
         cs1010_println_long(i);
      }
   }
}

int main() {
   long n = cs1010_read_long();
   long* input_arr  = cs1010_read_long_array(n);
   
   if (input_arr != NULL) {
      countingsort(input_arr, n);
      free(input_arr);
   }
}
