/**
 * CS1010 Semester 1 AY20/21
 * Assignment 6: Add
 *
 * Add two non-negative numbers which are arbitrarily large. The input numbers
 * will be stored as a char arrays. The program would add the 2 arrays and output an 
 * array with the added numbers.
 *
 * @file: add.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/**
 * To add 2 digits and determine if there is a carry
 * 
 * @param[in] d1 The digit(char) from the first number
 * @param[in] d2 The digit(char) from the second number
 * @param[in,out] has_carry_digit Check if carry is true, if it is add 1 to the sum. 
 *                                If (d1 + d2 > 9), carry is set to true, else false.
 * 
 * return The once placement digit(char) of (d1 + d2)
 */
char add_digit(char d1, char d2, bool *has_carry_digit) {
   long sum = (d1 - '0') + (d2 - '0');
   long res;
   if (*has_carry_digit) {
      sum += 1;
   }
   if (sum > 9) {
      // % 10 to get last digit
      res = sum % 10;
      *has_carry_digit = true;
   } else {
      res = sum;
      *has_carry_digit = false;
   }
   return (char)res + '0';
}

/** 
 * The function would add the 2 char array and store the output into an array
 * 
 * @param[in] num1 The char array of the first number
 * @param[in] num1_len The length of the num1 array
 * @param[in] num2 The char array of the second number
 * @param[in] num2_len The length of the num2 array
 * @param[in,out] total The array to store the results of the sum of num1 and num2
 * @param[in] total_len The length of total array 
 */
void add_numbers(char num1[], long num1_len, char num2[], long num2_len, char total[], long total_len) {
   long i = num1_len - 1;
   long j = num2_len - 1;
   long k = total_len;
   bool has_carry_digit = false;

   while (i >= 0 && j >=0) {
      assert(i >= 0 && i < num1_len);
      assert(j >= 0 && j < num2_len);
      total[k] = add_digit(num1[i], num2[j], &has_carry_digit);
      i -= 1;
      j -= 1;
      k -= 1;
   }
   
   char *remainder;
   if (j >= 0) {
      remainder = num2;
   } else {
      remainder = num1;
      j = i;
   }
   
   while (j >= 0) {
      assert(k >= 0 && j >= 0 && (j < num2_len || j < num1_len));
      total[k] = add_digit(remainder[j], '0', &has_carry_digit);
      k -= 1;
      j -= 1;
   }
   
   if (has_carry_digit) {
      assert(k == 0);
      total[k] = '1';
      cs1010_println_string(total);
   } else {
      cs1010_println_string(&total[1]);
   }
}

int main() {
   char *num1 = cs1010_read_word();
   char *num2 = cs1010_read_word();
   if (num1 == NULL || num2 == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }

   long num1_len = (long)strlen(num1);
   long num2_len = (long)strlen(num2);
   long total_len = num2_len;
   
   if (num1_len > num2_len) {
      total_len = num1_len;
   }

   // +2 for terminating char and carry
   char *total = calloc((size_t)(total_len + 2), sizeof(long));
   if (total == NULL) {
      cs1010_println_string("Not enough memory");
   }
   // assigning the terminating char
   total[total_len+1] = '\0';

   add_numbers(num1, num1_len, num2, num2_len, total, total_len);
   // Free memory
   free(num1);
   free(num2);
   free(total);
}
