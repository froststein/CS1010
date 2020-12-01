/**
 * CS1010 Semester 1 AY20/21
 * Assignment 5: Contact
 *
 * This program will determine if 2 people have came in direct contact or has 
 * contacted through a middle person or no contact at all. 
 *
 * @file: contact.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <stdbool.h>

/**
 * Check if person m and n had direct contact
 * 
 * @param[in] contact The array of contact information
 * @param[in] m Person 1 that we are checking
 * @param[in] n Person 2 that we are checking
 *
 * @return A boolean value to check if m and n are in direct contact
 */
bool is_connected(char **contact, long m, long n) {
   if (m >= n) {
      return contact[m][n] == '1';
   }
   return contact[n][m] == '1';
}

/**
 * To find if any person was in indirect contact with both person m and person n
 *
 * @param[in] contact The array of contact information
 * @param[in] m Person 1 that we are checking
 * @param[in] n Person 2 that we are checking
 * @param[in] row The number of people in the array of contact information
 *
 * @return The person's index if there was a indirect contact, else return -1 for no contact
 */
long get_indirect_connect(char **contact, long m, long n, long row) {
   long index;
   for (index = 0; index < row; index += 1) {
      if (is_connected(contact, m, index) && is_connected(contact, index, n)){
         return index;
      }   
   }
   // -1 means there is no connections
   return -1;
}

/**
 * This method handles the printing of contact status between person m and n
 * 
 * @param[in] contact The array of contact information
 * @param[in] m Person 1 that we are checking
 * @param[in] n Person 2 that we are checking
 * @param[in] row The number of people in the array of contact information
 */
void print_contact(char **contact, long m, long n, long row) {
   // check if there is a direct contact
   if(is_connected(contact, m, n)) {
      cs1010_println_string("direct contact");
   } else {
      // check if m & n are indirectly contacted or no contact
      long indirect = get_indirect_connect(contact, m, n, row);
      if (indirect >= 0) {
         cs1010_print_string("contact through ");
         cs1010_println_long(indirect);
      } else {
         cs1010_println_string("no contact");
      }
   }
}

int main() {
   long row = cs1010_read_long();
   char **contact = calloc((size_t)row, sizeof(char *));
   // Check if memory was assigned to this array 
   if (contact == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }

   for (long i = 0; i < row; i += 1) {
      contact[i] = cs1010_read_word();
      // Check if memory was assigned to this array
      if (contact[i] == NULL) {
         cs1010_println_string("Not enough memory");
         return 1;
      }
   }
   long m = cs1010_read_long();
   long n = cs1010_read_long();
   
   print_contact(contact, m , n, row);

   // Free memory
   for (long i = 0; i < row; i += 1) {
      free(contact[i]);
   }
   free(contact);
}
