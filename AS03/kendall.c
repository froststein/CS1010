/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance.
 *
 * @file: kendall.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

double calculate_kendall_tau(long input_arr[], long length) {
   long count = 0;
   for (long i = 0; i < length - 1; i += 1) {
      for (long j = i + 1; j < length; j += 1) {
            // first number rank should nvr be more than second number
            // therefore compare to see if i > j, to tell its a different order of ranking
            if (input_arr[i] > input_arr[j]) {
               count += 1;
            }
      }
   }
   // formula for total is 1/2 * n(n-1), 
   return count / (0.5 * length * (length - 1));
}

int main() {
   long num = cs1010_read_long();
   long* input_arr = cs1010_read_long_array(num);
   
   if (input_arr != NULL) {
      double norm_kendall_distance = calculate_kendall_tau(input_arr, num);
      cs1010_print_double(norm_kendall_distance);
      free(input_arr);
   }
}
