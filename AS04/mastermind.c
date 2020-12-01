/**
 * CS1010 Semester 1 AY20/21
 * Assignment 4: Mastermind
 *
 * To simulate a game of mastermind, it would first take in an input for the code
 * and the subsequent inputs would be to guess the code. The input for code and guess can only
 * contain 'c','g','r','b','p','o' that denotes the colors and the size of both code and guess can only be 4. 
 * Upon entering each guess the program would print 2 values, the number of correct color pegs in the correct placement
 * and the number of correct color pegs in the wrong placement. This program will terminate after
 * the guesser has managed to guess the correct code.
 * 
 * @file: mastermind.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
// Fixed size for the code and guess
#define CODE_SIZE (4)

/**
 * Determine if the given code and guess matches. While at the same time
 * determine how many pegs are in the correct color and correct placements
 * ,and how many are in the correct color but wrong placements.
 * 
 * @param[in] code The correct answer for the game 
 * @param[in] guess The input by the player to guess the code
 * 
 * @pre both the size for both code and guess are to be 4
 *
 * @return A boolean value to check if the guess is the same as the code 
 */
bool is_matched(char code[], char guess[]) {  
   long same_c_same_p = 0;
   long same_c_dif_p = 0;

   // Copying code array into a tmp array, which would be used to do checking
   // Size + 1 to account for terminating char '\0' 
   char tmp[5];
   strcpy(tmp,code);
   
   // Determining if the pegs are the correct color and correct placement
   for (long j = 0; j < CODE_SIZE; j += 1) {
      if (guess[j] == tmp[j]) {
         same_c_same_p += 1;
         // updating the array value 0, so that we mark it as checked
         // this is to prevent the double checking from happening
         tmp[j] = 0;
      }
   }

   // Determining if the pegs are the correct color but wrong placement
   for (long k = 0; k < CODE_SIZE; k += 1) {
      bool is_found = false;
      for (long j = 0; j < CODE_SIZE && !is_found; j += 1) {
         // Ignore those characters that has been checked in the tmp[]
         if (guess[k] == tmp[j] && guess[k] != code[k]) {
            same_c_dif_p += 1;
            is_found = true;
            // Updating the array with value 0, so that we mark it as checked, to prevent double counting
            tmp[j] = 0;
         }
      }  
   }
   
   cs1010_print_long(same_c_same_p);
   cs1010_print_string(" ");
   cs1010_println_long(same_c_dif_p);
   // if there are 4 of the correct colors and correct placement, it would mean that the guess was correct
   // hence solving the game and returning true;
   if (same_c_same_p == 4) {
      return true;
   }
   return false;
}

int main() {
   char *code = cs1010_read_word();
   // Check if memory was assigned to guess, if no memory was assigned, exit program
   if (code == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }
   char *guess; 
   bool match = false;
   // To get the input for guess, the loop will terminate when the guesser makes the correct guess
   do {
      guess = cs1010_read_word();
      // Check if memory was assigned to guess, if no memory was assigned, exit program.
      if (guess == NULL) {
         cs1010_println_string("Not enough memory");
         return 1;
      }
      match = is_matched(code, guess);
      free(guess);
   } while(!match);
   
   free(code);
}
