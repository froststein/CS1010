/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: ID
 *
 * Read in a number and print out the check code 
 * according to NUS student ID algorithm.
 *
 * @file: id.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

long get_remainder(long num) {
   long sum = 0;

   while (num > 0) {
      // get last digit and add into sum
      sum += num % 10;
      // update num
      num /= 10;
   }
   // to get remainder, sum % 13
   return (sum % 13);
}

int main() {
   char check_code[13] = {'Y', 'X', 'W', 'U', 'R', 'N', 'M', 'L', 'J', 'H', 'E', 'A', 'B'};
   long input_num = cs1010_read_long();
   long remainder = get_remainder(input_num);
   char code = check_code[remainder];
   // print check code character
   putchar(code);
}
