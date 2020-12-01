/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Prime
 *
 * Reads in an integer n from standard input and print 
 * the largest prime smaller or equal to n.
 *
 * @file: prime.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

// Checking prime via sqrt(n)
bool is_prime(long n) {
        for (long i = 2; i <= sqrt(n) ; i += 1) {
                if ( (n % i) == 0 ) {
                        return false;
                }
        }
        return true;
}

// Find the largest from the back
long get_largest_prime(long num) {        
        // if the number is less than 2, return the original num
        if (num <= 2) {
                return num;
        }
        // if the number is an even number, number would confirm be > 2
        if ( num % 2 == 0 ) {
                // make num into an odd number
                num -= 1;
        }
        // decrement by 2, to skip the even numbers 
        for (long i = num; i >= 2 ; i -= 2) {
                if (is_prime(i)) {
                        return i;
                }
        }
        return num;
}

int main() {
        long num = cs1010_read_long();
        long largest_prime = get_largest_prime(num);
        cs1010_println_long(largest_prime);
}

