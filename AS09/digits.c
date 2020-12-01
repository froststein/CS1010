/**
 * CS1010 Semester 1 AY20/21
 * Assignment 9: Digits
 *
 * The program reads n which corresponds to the number of training samples, 
 * followed by repeatedly reading n handwritten digits 
 * containing a label and 28 lines of texts consisting of '.' and '#' representing a 
 * handwritten digit. This is then followed by another positive integer m, corresponding
 * to the number of testing samples, followed by repeatedly reading m handwritten digits
 * containing a label and 28 lines of text. The program then prints for each testing sample, 
 * the digit it is labeled, then the digit it is detected and finally the accuracy.
 *
 * @file: digits.c
 * @author: Roy (Group BC1A)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <limits.h>

#define NCOLS 28
#define NROWS 28
#define K 5

typedef struct {
   long number;
   char *inputLine[NROWS];
} digit;

typedef struct {
   long number;
   long distance;
   char *inputLine[NROWS];
} neighbour;

/**
 * This function helps to determine the shortest distance for a particular digit, it helps to break tie for deciding of digit
 * 
 * @param[in] neighbours The 5 training samples witht he least difference
 * @param[in] q The digit to find the shortest distance
 * 
 * @return the shortest distance of the digit(q)
 */
long findShortest(neighbour *neighbours, long q) {
   long shortest = LONG_MAX;
   for (long i = 0; i < K; i += 1) {
      if (neighbours[i].number == q) {
         if (neighbours[i].distance < shortest) {
            shortest = neighbours[i].distance;
         }
      }
   }
   return shortest;
}

/**
 * This function finds the number that has the higest frequency amongst the 5 training samples
 *
 * @param[in] neighbours The array of 5 training samples with the least difference 
                         for distance amongst the test samples
 *
 * @return returns the number that has the highest frequency
 */
long decideDigit(neighbour *neighbours) {
   long freqTab[10] = {0};
   for (long i = 0; i < K; i += 1) {
      freqTab[neighbours[i].number] += 1;
   }
   long maxTemp = freqTab[0];
   long maxDig = 0;
   for (long i = 1; i < 10; i += 1) {
      if (freqTab[i] >= maxTemp) {
         // Tie breaking of same frequency
         if (freqTab[i] == maxTemp) {
            long currDis = findShortest(neighbours, maxDig);
            long tempDis = findShortest(neighbours, i);
            // take the shorter distance
            if (tempDis < currDis) {
               maxTemp = freqTab[i];
               maxDig = i;
            } else if (tempDis == currDis) {
               // if same distance, take the smaller digit
               if (i < maxDig) {
                  maxTemp = freqTab[i];
                  maxDig = i;
               }
            }
         } else {
           maxTemp = freqTab[i];
           maxDig = i;
         }
      }
   }
   return maxDig;
}

/**
 * This function keeps track of the 5 training samples with the least difference as compared to a test sample
 * 
 * @param[in] training The training sample that is getting inserted into the array of 5 training samples
 * @param[in] dist The distance of the current training samples has with the test sample
 * @param[in,out] neighbours The array of 5 training sample with the least differencs as compared to the test sample
 */
void insert(digit training, long dist, neighbour *neighbours) {
   if (dist > neighbours[K-1].distance) {
      return;
   }
   if (dist == neighbours[K-1].distance && training.number > neighbours[K-1].number) {
      return;
   }
   long i = K - 1;
   do {
      neighbours[i] = neighbours[i-1];
      i -= 1;
   } while (i >= 0 && (neighbours[i].distance > dist || 
      (neighbours[i].number > training.number && neighbours[i].distance == dist)));
   neighbours[i+1].number = training.number;
   neighbours[i+1].distance = dist;
}

/**
 * This funciton finds the distance between a training sample and a testing sample
 * 
 * @param[in] training One training sample
 * @param[in] testing One testing sample
 * @param[in] lim The 5 smallest distance of the training sample pertaining to a test sample 
 * 
 * @return The distance of the between the training sample and testing sample
 */
long getDistance(digit training, digit testing, long lim) {
   long distance = 0;
   for (long i = 0; i < NROWS; i += 1) {
      for (long j = 0; j < NCOLS; j += 1) { 
         if (testing.inputLine[i][j] != training.inputLine[i][j]) {   
            distance += 1;
            if (distance > lim) {
               return distance;
            }
         }
      }
   }
   return distance;
}

/**
 * This function tries to determine a digit in the testing sample by comparing the data in 
 * training array, and choose the most common digit amongst the first K smallest distance.
 * 
 * @param[in] training The array of training samples
 * @param[in] train_n The number of digits in the training samples
 * @param[in] testing One testing sample
 *
 * @return The recoginized digit after processing
 */
long recognizeNum(digit *training, long train_n, digit testing) {
   neighbour neighbours[K];
   for (long i = 0; i < K; i += 1) {
      neighbours[i].distance = LONG_MAX;
   }
   for (long j = 0; j < train_n; j += 1) {
      long dist = getDistance(training[j], testing, neighbours[K-1].distance);
      insert(training[j], dist, neighbours);
   }
   long output = decideDigit(neighbours);
   return output;
}

/**
 * This function process the testing data by training against training data and keeps track 
 * of the success hits and prints out the accuracy
 *
 * @param[in] training The array of training samples
 * @param[in] train_n The number of digits in the training samples
 * @param[in] testing The array of testing samples
 * @param[in] test_n The number of digits in the testing samples
 */
void process(digit *training, long train_n, digit *testing, long test_n) {
   long count = 0;
   for (long i = 0; i < test_n; i += 1) {
      long actual_num = testing[i].number;
      long recognize = recognizeNum(training, train_n, testing[i]);
      cs1010_print_long(actual_num);
      cs1010_print_string(" ");
      cs1010_println_long(recognize);
      if (actual_num == recognize) {
         count += 1;
      }
   }
   double accuracy = count * 100.0 / test_n;
   cs1010_println_double(accuracy);
}


/**
 * This function reads the training/testing samples
 * 
 * @param[out] input An array of digit structs
 * @param[in] n The number of digit structs in the array
 *
 * @return true if memory allocation is successful, else false.
 */
bool readDigit(digit *input, long n) {
   for (long i = 0; i < n; i += 1) {
      input[i].number = cs1010_read_long();
      for (long j = 0; j < NROWS; j += 1) {
         input[i].inputLine[j] = cs1010_read_word();
         if (input[i].inputLine[j] == NULL) {
            return false;
         }
      }
   }
   return true;
}

/**
 * This function will free the memory allocated to the struct arrays
 *
 * @param[out] input The strut array of digits to be free
 * @param[in] n The number of digits in the array
 */
void free_mem_struct(digit *input, long n){
   for (long i = 0; i < n; i += 1) {
      for (long j = 0; j < NROWS; j += 1) {
         free(input[i].inputLine[j]);
      }
   }
   free(input);
}

int main() {
   // Read in training samples
   long train_n = cs1010_read_long(); 
   digit *training_sample = malloc((size_t)train_n * sizeof(digit));
   if (training_sample == NULL) {
      free(training_sample);
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }
   bool trainCreated = readDigit(training_sample, train_n);
   if (trainCreated == false) {
      free_mem_struct(training_sample, train_n);
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }
  
   // Read in testing samples
   long test_n = cs1010_read_long();
   digit *testing_sample = malloc((size_t)test_n * sizeof(digit));
   if (testing_sample == NULL) {
      free(testing_sample);
      free_mem_struct(training_sample, train_n);
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }
   bool testCreated = readDigit(testing_sample, test_n);
   if (testCreated == false) {
      free_mem_struct(training_sample, train_n);
      free_mem_struct(testing_sample, test_n);
      cs1010_println_string("Not enough memory allocated");
      return -1;
   }

   process(training_sample, train_n, testing_sample, test_n);

   free_mem_struct(training_sample, train_n);
   free_mem_struct(testing_sample, test_n);
}
