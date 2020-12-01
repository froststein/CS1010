/**
 * CS1010 Semester 1 AY20/21
 * Assignment 5: Social
 *
 * To print the social network formed by a friendship chain of k times
 *
 * @file: social.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"
#include <stdbool.h>
#define FRIENDS ('1')
#define STRANGERS ('0')

/**
 * Check if person m and n had a direct connection
 * 
 * @param[in] network The array of social information 
 * @param[in] m Person 1 that we are checking
 * @param[in] n Person 2 that we are checking
 *
 * @return A boolean value to check if m and n are in direct contact
 */
bool is_connected(char **network, long m, long n) {
   if (m >= n) {
      return network[m][n] == FRIENDS;
   }
   return network[n][m] == FRIENDS;
}

/**
 * Checking if 2 people are indirectly connected by a middle person
 *
 * @param[in] network The array of social information
 * @param[in] n_one_hop_network The (n-1)hop social information
 * @param[in] m Person 1 that we are checking
 * @param[in] n Person 2 that we are checking
 * @param[in] row The number of rows(user) for the arrays 
 * 
 * @return Friends if m and n has a (n+1)hop connection, otherwise return STRANGER 
 */
char indirect_connected(char **network, char **n_one_hop_network, long m , long n, long row) {
   for (long index = 0; index < row; index += 1) {
      if (is_connected(network, m, index) && is_connected(n_one_hop_network, index, n)) {
         return FRIENDS;
      }
   }
   return STRANGERS;
}

/*
 * Copying the values from n_hop_network to n_one_hop_network 
 * to get ready for next round of iteration
 *
 * @param[in,out] n_one_hop_network The destination array for values to be copied to
 * @param[in,out] n_hop_network The source array for values to be copied from
 * @param[in] row The number of rows(user) for the arrays
 */
void swap(char **n_one_hop_network, char **n_hop_network, long row) {
   for (long i = 0; i < row; i += 1) {
      for (long j = 0; j <= i; j += 1) {
         char tmp = n_one_hop_network[i][j];  
         n_one_hop_network[i][j] = n_hop_network[i][j];
         n_hop_network[i][j] = tmp;
      }
   }
}

/*
 * Finds the n hop friends for the whole network and update n_hop_network with the information
 *
 * @param[in] row The number of rows(users) for the array(networks)
 * @param[in] network The main social network
 * @param[in] n_one_hop_network The (n-1)hop of friends network
 * @param[out] n_hop_network The n hop of friends network
 */
void connected_n(char **network, char **n_one_hop_network, char **n_hop_network, long row) {
   for (long i = 0; i < row; i += 1) {
      for (long j = 0; j <= i; j += 1) {
         if (is_connected(n_one_hop_network, i, j)) {
            n_hop_network[i][j] = FRIENDS;
         } else {
            n_hop_network[i][j] = indirect_connected(network, n_one_hop_network, i, j, row);
         }
      }
   }
}

/*
 * Runs k number of times to find k-hop friends in a network
 * 
 * @param[in] network The main social network
 * @param[in] n_one_hop_network A copy of the main social network
 * @param[in] n_hop_network A empty jagged array to be parsed for storing
 * @param[in] row The number of rows(users) for the arrays
 * @param[in] k The number of times to find k-hop friends within a network
 */
void print_friendship(char **network, char **n_one_hop_network, char **n_hop_network, long row, long k) {
   for (long i = 1; i < k; i += 1 ) {
      connected_n(network, n_one_hop_network, n_hop_network, row);
      swap(n_one_hop_network, n_hop_network, row);
   }
   
   for (long i = 0; i < row; i += 1) {
      cs1010_println_string(n_one_hop_network[i]);
   }
}

int main() {
   long row = cs1010_read_long();
   long k = cs1010_read_long();

   char **network = calloc((size_t)row, sizeof(char *));
   char **n_one_hop_network = calloc((size_t)row, sizeof(char *));
   char **n_hop_network = calloc((size_t)row, sizeof(char *));
   
   // Checking if memory was assigned to these arrays
   if (network == NULL || n_one_hop_network == NULL || n_hop_network == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }
   
   for (long i = 0; i < row; i += 1) {
      network[i] = cs1010_read_word();
      // +2 for jagged and terminating null char
      n_one_hop_network[i] = calloc((size_t)(i + 2), sizeof(char));
      n_hop_network[i] = calloc((size_t)(i + 2), sizeof(char));
      
      // Checking if memory was assigned to these arrays
      if (network[i] == NULL || n_one_hop_network[i] == NULL || n_hop_network[i] == NULL) {
         cs1010_println_string("Not enough memory");
         return 1;
      }

      // Copying values from main network into n_one_hop_network
      for (long j = 0; j < (i + 2); j += 1) {
         n_one_hop_network[i][j] = network[i][j];
      }
   }
   
   print_friendship(network, n_one_hop_network, n_hop_network, row, k);

   // Free memory
   for (long i = 0; i < row; i += 1) {
      free(network[i]);
      free(n_one_hop_network[i]);
      free(n_hop_network[i]);
   }
   free(network);
   free(n_one_hop_network);
   free(n_hop_network);
}
