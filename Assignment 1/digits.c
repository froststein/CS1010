/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Digits
 *
 * Read in a positive integer from the standard input and print
 * the sum of the square of each digit in the integer to the standard output.
 *
 * @file: digits.c
 * @author: Roy Tang (Group BC1A)
 */

#include "cs1010.h"

// Square the input
long square(long x)
{
	return x * x;
}

// Sum the square of each digit in a number
long sum_of_digits_square(long number)
{
	// if number has only 1 digit(<10) return square(number)
	if(number < 10)
	{
		return square(number);
	} 
	// mod 10 would get the last digit of the number
	long last_digit = number % 10;
	// dividing 10 would remove the last digit from the number
	long remainder = number / 10;
	return (square(last_digit)) + sum_of_digits_square(remainder);
}

int main()
{
	long number = cs1010_read_long();
	long sum = sum_of_digits_square(number);
	cs1010_println_long(sum);
}
