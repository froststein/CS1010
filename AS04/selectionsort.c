/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: SelectionSort
 *
 * This program will sort an array of numbers accordingly using selection sort.
 * The size of the array would be determined by the first input and the numbers to be
 * sorted would be entered as follows.
 *
 * @file: selectionsort.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

/**
 * Print out the contents of array.
 * 
 * @param[in] len The size of the array
 * @param[in] arr The array to print
 */
void print_arr(long len, long arr[]) {
   for (long i = 0; i < len; i += 1) {
      cs1010_print_long(arr[i]);
      cs1010_print_string(" ");
   }
   cs1010_println_string("");
}

/**
 * Find the maximum number from the input array, given a boundary to look until 
 * and returns the index of the maximum element
 *
 * @param[in] last The boundary index of which our method should look until
 * @param[in] arr The array to find max
 *
 * @return The index of the maximum element in the input array given a set boundary
 */
long find_max(long last, long arr[]) {
   long index = last - 1;
   for (long i = 0; i < last; i += 1) {
      if (arr[i] > arr[index]) {
         index = i;
      }
   }
   return index;
}

/**
 * Sort the input array using selection sort
 * 
 * @param[in] len The size of the array
 * @param[in,out] arr The array to sort
 * @pre len variable needs to be > 1 for the function to print and sort
 */
void selection_sort(long len, long arr[]) {
   long last = len;
   long cur_index;
   for (long i = 1; i <= (len - 1); i += 1) {
      cur_index = (last - 1); 
      // find the max in the list and return the index of the max value
      // last variable would decrement with every loop iteration, this is because the right hand-side
      // of the array is already sorted, hence we can ignore those values, therefore we decrement the last variable
      long max_index = find_max(last, arr);
      if (max_index != cur_index) {
         long tmp = arr[max_index];
         arr[max_index] = arr[cur_index];
         arr[cur_index] = tmp;
      }
      // to print out the current arrangement of the array after 1 loop iteration
      print_arr(len, arr);
      last -= 1;
   }
}

int main() {
   long len = cs1010_read_long();
   long *arr = cs1010_read_long_array(len);
   if (arr == NULL) {
      cs1010_println_string("Not enough memory");
      return 1;
   }
   selection_sort(len, arr);
   free(arr);
}
