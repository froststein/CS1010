#include "cs1010.h"
/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Triangle
 *
 * Read in a positive integer h from standard input and 
 * print an equlateral triangle of height h.
 *
 * @file: triangle.c
 * @author: Roy Tang (Group BC1A)
 */

// Row index starts at 1
// Each row of blank space is height-(row index) 
void print_space(long count) {
        for (long j = 0; j < count; j += 1) {
                cs1010_print_string(" ");
        }
}

// Hash printing would be 2n-1 per row, where n is the current row printing
void print_hash(long n) {
        for (long k = 0; k < n; k += 1) {
                cs1010_print_string("#");
        }
} 

// each row contains L-blankspace, hash printing, R-blankspace
void print_row(long n, long pos) {
        // number of blank space = height - row index
        long space_count = n - pos;
        // print left side blank spaces
        print_space(space_count);
        
        // number of hash = 2*(row index) - 1
        long hash_count = ( 2 * pos ) - 1;
        print_hash(hash_count);
        
        // print right side blank spaces
        print_space(space_count);
}

int main() {
        long height = cs1010_read_long();		
        // Using input height to loop each row
        for (long i = 1; i <= height; i += 1) {
                print_row(height, i);
                cs1010_println_string("");
        }		
}
