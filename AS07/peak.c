/**
 * CS1010 Semester 1 AY20/21
 * Assignment 7: Peak
 *
 * Given an array of n peaks. The program would find the index of the peak
 * if there is no peak present, program would print "no peak", if a peak is present
 * print the index of the peak.
 *
 * @file: peak.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

/**
 * Check if the peak is within the range of start and end in the array
 *
 * @param[in] arr The array of locations for elevations
 * @param[in] start The starting index to search
 * @param[in] end The end index to search
 *
 * @return Return the index of peak in elevation, return -1 if there is no peak
 */
long findPeak(long arr[], long start, long end) {
   if (end < start + 2) {
      return -1;
   }
   
   long mid = start + ((end - start) / 2);
   
   // if mid is higher than the nearby points(left,right), it is the peak itself
   if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]) {
      return mid;
   }
   
   // If mid is same for left and right, we need to check both sides. 
   if (arr[mid - 1] == arr[mid] && arr[mid + 1] == arr[mid]) {
      // left side
      long pos = findPeak(arr, start, mid);
      if (pos != -1) {
         return pos;
      }
      // right side
      return findPeak(arr, mid, end);
   }
   // Check right side of array
   if (arr[mid - 1] <= arr[mid] && arr[mid + 1] >= arr[mid]) {
      return findPeak(arr, mid, end);
   }

   // Check left side of array
   return findPeak(arr, start, mid);
}

int main() {
   long n = cs1010_read_long();

   long *locations = malloc((size_t)n * sizeof(long));
   
   // Check if memory was allocated to the array
   if (locations == NULL) {
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }

   for (long i = 0; i < n; i += 1) {
      locations[i] = cs1010_read_long();
   }

   long peak = findPeak(locations, 0, n);
   if (peak == -1) {
      cs1010_println_string("no peak");
   } else {
      cs1010_println_long(peak);
   }

   // Free memory
   free(locations);
}
