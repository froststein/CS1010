/**
 * CS1010 Semester 1 AY20/21
 * Assignment 6: Frequency
 * 
 * Given 2 equal length string of small letter 'a' 
 * to 'z', this program checks if both have the
 * same set of alphabets appearing the same number
 * of time.
 *
 * @file: frequency.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <string.h>
#include <stdbool.h>

/**
 * Checking if both string has the same frequency of characters, if they do print YES, else NO
 * 
 * @param[in] s1 The first input string
 * @param[in] s2 The second input string
 */
void find_frequency(char s1[], char s2[]) {
   long frequency_t[26] = {0};
   
   long len = (long)strlen(s1);
   for (long i = 0; i < len; i += 1) {
      // using ASCII values, hence - 'a'
      long index_1 = s1[i] - 'a';
      long index_2 = s2[i] - 'a';
      frequency_t[index_1] += 1;
      frequency_t[index_2] += 1;
   }
   
   bool is_same = true;
   for (long j = 0; j < 26 && (is_same); j += 1) {
      // if there is an equal frequency, it should be times 2 of the original frequency of s1
      // therefor checking if its not a multiple of 2 would indicate it does not have same frequency
      if ((frequency_t[j] != 0) && (frequency_t[j] % 2 != 0)) {
         is_same = false;
      }
   }
   if (is_same) {
      cs1010_println_string("YES");
   } else {
      cs1010_println_string("NO");
   }
}

int main() {
   char *s1 = cs1010_read_word();
   char *s2 = cs1010_read_word();

   if (s1 == NULL || s2 == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }

   find_frequency(s1, s2);

   //Free memory
   free(s1);
   free(s2);
}
