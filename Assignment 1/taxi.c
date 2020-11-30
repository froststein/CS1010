/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Taxi
 *
 * Read in four positive integer corresponding to the day of the week,
 * the hour and minute of boarding, and the distance travelled.  Print
 * to the standard output, the fare of the taxi.
 *
 * @file: taxi.c
 * @author: Roy Tang (Group BC1A)
 */

#include "cs1010.h"
#include <stdbool.h>

// Checking if input day is a weekday
bool is_weekday(long day) {
	return ( (day >= 1) && (day <= 5) ); 
}

// Checking if input time is in range of morning peak (06:00 to 09:29)
bool is_morning_peak(long start_hour, long start_minute) {
	return (start_hour >= 6 && start_hour < 9) || (start_hour == 9 && start_minute <= 29);
}

// Checking if input time is in range of evening peak (18:00 to 23:59)
bool is_evening_peak(long start_hour) {
	return (start_hour >= 18 && start_hour <= 23);
}

// Checking if input time is in range of midnight peak (00:00 to 05:59)
bool is_midnight_peak(long start_hour) {
	return (start_hour >= 0 && start_hour < 6);
}

// Finding the surcharge rate of the ride
double find_surcharge(long day, long start_hour, long start_minute) {
	if (is_weekday(day) && is_morning_peak(start_hour,start_minute)) {
		return 1.25;
	}
	if (is_evening_peak(start_hour)) {
		return 1.25;
	}
	if (is_midnight_peak(start_hour)) {
		return 1.5;
	}
	return 1.0;
}

// A function to round up to the nearest whole number, used for basic fare calculations
long lceil(long distance, long x) {
	long result = distance / x;
	if (distance % x != 0) {
		result += 1;
	}
	return result;
}

// Calculate the basic fare before surcharge is applied
double calculate_basic_fare(long distance) {
	double fare = 3.20;
	if (distance <= 1000) {
		return fare;
	}
	distance -= 1000;
	// checking the first 10km range of fare ($0.22 per 400m)
	if (distance <= 9000) {
		fare += 0.22 * lceil(distance, 400);
	}
	else {
		fare += 0.22 * lceil(9000, 400);
	}
	distance -= 9000;
	if (distance <= 0) {
		return fare;
	}
	// calculating fare after 10km range ($0.22 per 350m)
	fare += 0.22 * lceil(distance, 350);

	return fare;
}

int main() {
	long day = cs1010_read_long();
	long start_hour = cs1010_read_long();
	long start_minute = cs1010_read_long();
	long distance = cs1010_read_long();
		
	double basic_fare = calculate_basic_fare(distance);
	double surcharge = find_surcharge(day, start_hour, start_minute);
	
	double total_fare = basic_fare * surcharge;
	cs1010_println_double(total_fare);	
}
