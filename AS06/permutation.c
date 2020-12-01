/**
 * CS1010 Semester 1 AY20/21
 * Assignment 6: Permutation
 * 
 * Given two strings of lowercase letters 'a' to 'z', with 
 * first string * no longer than the second.The program 
 * checks if the 1st string is a permutation of a substring
 * of the 2nd one.
 *
 * @file: permutation.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <string.h>
#include <stdbool.h>

/**
 * Get the freqency of each char in the input string array and fill it up in the frequency table
 * 
 * @param[in] str The input string to count frequency of each char
 * @param[in] size The length of the input string 
 * @param[out] freq_t The frequnecy table to be updated with the frequency count
 */
void make_frequency_table(char str[], long size, long freq_t[]) {
   for (long j = 0; j < size; j += 1) {
      long index = str[j] - 'a';
      freq_t[index] += 1;
   }
}

/**
 * To update the frequency table of the new substring with lengh k of str
 *
 * @param[in,out] freq_t The frequency table to be updated
 * @param[in] str The input string
 * @param[in] index The starting position of the substring
 * @param[in] k The length of the substring
 */
void update_frequency_table(long freq_t[], char str[], long index, long k) {
   freq_t[str[index - 1] - 'a'] -= 1;
   freq_t[str[index + k - 1] - 'a'] += 1;
}

/**
 * Check if both the strings are permutated, by checking the frequency of both strings
 *
 * @param[in] freq_t1 The frequency table for the first string
 * @param[in] freq_t2 The frequency table for the second string
 * 
 * @return If both frequency table match return true, else false
 */
bool is_permutated(long freq_t1[], long freq_t2[]) {
   for (long i = 0; i < 26; i += 1) {
      if (freq_t1[i] != freq_t2[i]) {
         return false;
      }
   }
   return true;
}

/**
 * Find if s1 is a permutation of substring of s2
 *
 * @param[in] s1 The shorter input string
 * @param[in] s2 The string to search for the permutation of s1
 *
 * @return if s1 is a permutation in s2 return true, else false
 */
bool find_permutation(char s1[], char s2[]) {
   long s1_len = (long)strlen(s1);
   long s2_len = (long)strlen(s2);
   
   long freq_t1[26] = {0};
   long freq_t2[26] = {0};
   
   make_frequency_table(s1, s1_len, freq_t1); 
   make_frequency_table(s2, s1_len, freq_t2);
  
   if (is_permutated(freq_t1, freq_t2)) {
      return true;
   }
   
   for (long i = 1; i <= (s2_len - s1_len); i += 1) {
      update_frequency_table(freq_t2, s2, i, s1_len);
      if (is_permutated(freq_t1, freq_t2)) {
         return true;
      }
   }
   return false;
}

/**
 * To print out "YES" or "NO" if string 1 and string 2 are permutated
 *
 * @param[in] s1 The first input string 
 * @param[in] s2 The second input string
 */
void perform_permutation(char s1[], char s2[]) {
   bool is_permutated = find_permutation(s1, s2);   
   if (is_permutated) {
      cs1010_println_string("YES");
   } else {
      cs1010_println_string("NO");
   }
}

int main() {
   char *s1 = cs1010_read_word();
   char *s2 = cs1010_read_word();

   // Checking if memory was assigned to the arrays
   if (s1 == NULL || s2 == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }
   
   perform_permutation(s1, s2);

   // Free memory
   free(s1);
   free(s2);
}
