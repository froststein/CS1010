/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Collatz 
 *
 * Read in a positive integer n from the standard input,
 * then, for each number k between number 1 .. n, transform
 * it into 1 based on the steps below:
 * - if k is even, k = k/2
 * - else, k = 3k + 1
 * Find the number k that requires the most number of steps
 * between 1 and n, and print both k and the number of steps
 * to standard output. If there are multiple numbers with
 * the same number of steps, we prefer to output the larger
 * among these numbers.
 *
 * @file: collatz.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

long collatz_step(long num) {
        long i;
        if (num == 1) {
                return 0;
        }

        for (i = 0; num != 1 ; i += 1) {
                // Checking for even number
                if ( (num % 2) == 0 ) {
                        num /= 2;
                }
                else {
                        num = (num*3) + 1; 
                }
        }
        return i;
}


int main() {
        long num = cs1010_read_long(); 
        // Highest step count
        long max = 0;
        // Number with highest step count
        long k = 0;
        
        for (long i = 1; i <= num; i += 1) {
                long current_step = collatz_step(i);
                // check if the value is higher or same, this is the fulfill 
                // the condition of returning the bigger num with same step count
                if (current_step >= max) {
                        max = current_step;
                        k = i; 
                }
        }
        
        cs1010_println_long(k);
        cs1010_println_long(max);
}
