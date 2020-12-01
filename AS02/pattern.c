/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Pattern
 *
 * Read in two positive integers: an interval n (n >= 1) 
 * and the height of the triangle h.  Then draw a triangle
 * according to a given pattern.  
 *
 * @file: pattern.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

// Checking if a number is prime 
bool is_prime(long n) {
        for (long i = 2; i <= sqrt(n); i += 1) {
                if (n % i == 0) {
                        return false;
                }
        }
        return true;
}

// Find the leading number of the cell
long leading_num(long row, long n) {
        long num = 1;
        for (long i = 1; i <= row; i += 1) {
                num += (i * n);
        }
        return num;
}

// Printing the blanks spaces for the triangle
void print_space(long count) {
        for (long i = 0; i < count; i += 1) {
                cs1010_print_string(" ");
        }
}

// Finding of any numbers in the cell has a prime
void print_hash(long row, long col, long n) {
        // getting the leading number of the cell
        long num = leading_num(row, n) + col;
        bool found= false;
        // looping through n-intervals as n defines how many numbers are in each cell
        for (long i = 0; (i < n) && (!found); i += 1) {
                // Checking for prime to print hash
                if (num == 1 || is_prime(num)) {
                        cs1010_print_string("#");
                        found = true;
                }
                else {
                        // updating it with the next number in the cell
                        num += (row + 1);
                }
        }
        // if no primes are present in the set of numbers, print blank
        if (!found) {
                cs1010_print_string(" ");
        }	
}

// Printing the middle cells of the triangle
void print_pattern(long row, long num_cells, long n) {
        // looping through each cell to find if the group of numbers in the cell has a prime 
        for (long i = 0; i < num_cells; i += 1) {
                print_hash(row, i, n);
        }
}
		
void print_triangle(long n, long h) {	
        // Each iteration is printing a row of the triangle
        for (long row = 0; row < h; row += 1) {
                // getting the number of blank spaces to be printed (height - rowindex)
                long space_count = h - row - 1;
                // printing blank space on left side of triangle
                print_space(space_count);
                
                // number of cells on the row is calculated to be 2*row + 1
                print_pattern(row, (2 * row) + 1, n);
                
                // printing blank space on right side of triangle
                print_space(space_count);
                cs1010_println_string("");
        }
}

int main() {
        long n = cs1010_read_long();
        long height = cs1010_read_long();
        
        print_triangle(n,height);
}
