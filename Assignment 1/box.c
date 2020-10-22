/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Box
 *
 * Read in three positive integer corresponding to the width,
 * height, and length of a box from the standard input, and
 * print the total surface area and the length of the diagonal
 * to the standard output.
 *
 * @file: box.c
 * @author: Roy Tang (Group BC1A)
 */

#include "cs1010.h"
#include <math.h>

// Calculate area of triangle
long area_of_rectangle(long width, long height)
{
	return (width * height);
}

// Calculate the hypotenuse of a triangle
double hypotenuse_of(double base, double height)
{	
	return sqrt( (base * base) + (height * height) );
}

int main() 
{
	long length = cs1010_read_long();
	long width = cs1010_read_long();
	long height = cs1010_read_long();

	long total_surface_area = ( 2 * area_of_rectangle(length, height) )
	+ ( 2 * area_of_rectangle(length, width) )
	+ ( 2 * area_of_rectangle(height,width) ); 

	cs1010_print_long(total_surface_area);
	cs1010_print_string(" ");

	// getting the base length of the triangle to calculate the diagonal via pythagoras theorem
	double diagonal_base = hypotenuse_of(length, width);
	// using the base from before calculate the diagonal length
	double diagonal_length = hypotenuse_of(diagonal_base, height);
	
	cs1010_print_double(diagonal_length);	
}
