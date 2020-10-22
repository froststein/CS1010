/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Suffix
 *
 * Read in a number and prints out the number with the appropriate suffix.
 *
 * @file: suffix.c
 * @author: Roy Tang (Group BC1A)
 */
#include "cs1010.h"

// Prints out the suffix of a number
void print_with_suffix(long n)
{
	// Checking for special cases (11,12,13)
	if ( (n % 100 == 11) || (n % 100 == 12) || (n % 100 == 13))
	{
		cs1010_print_long(n);
		cs1010_print_string("th");
	}
	else
	{
		if (n % 10 == 1)
		{	
			cs1010_print_long(n);
			cs1010_print_string("st");
		}
		else if (n % 10 == 2)
		{	
			cs1010_print_long(n);
			cs1010_print_string("nd");
		}
		else if (n % 10 == 3)
		{
			cs1010_print_long(n);
			cs1010_print_string("rd");		
		}
		else
		{
			cs1010_print_long(n);
			cs1010_print_string("th");
		}
	}
}

int main() 
{
	long number = cs1010_read_long();
	print_with_suffix(number);	
}
