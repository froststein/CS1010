/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

// Divide and conquer algorithm
long max(const long list[], long start, long end) {
   // if the list only has 1 element, return the element itself
   if ((start + 1) == end) {
      return list[start];
   }

   // we can find mid with (start + end) / 2
   // however, we need to account that there is a possibility of overflow from (start + end)
   // therefore, this way of finding mid was used instead, to account for chances of overflow
   // although, this is a rare occurance and it is more prevalent in "int" type, we should still account for it
   long mid = start + ((end - start) / 2);
   long left_max = max(list, start, mid);
   long right_max = max(list, mid, end);

   if (left_max > right_max) {
      return left_max;
   }
   return right_max;
}

int main() {
   long n = cs1010_read_long();
   long* num_arr = cs1010_read_long_array(n);
   
   if (num_arr != NULL) {
      long max_in_list = max(num_arr, 0, n);
      cs1010_println_long(max_in_list);
      free(num_arr);
   }
}
