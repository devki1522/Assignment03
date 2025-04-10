// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the Date struct and functions

#include "date.h"
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

DATE CreateDate(int day, int month, int year) {
	DATE date = { 0 };

	date.day = day;
	date.month = month;
	date.year = year;

	return date;
}

DATE GetCurrentDate() {
	time_t t = time(NULL); // time(NULL) returns seconds since epoch 
	struct tm tm = *localtime(&t); // Converts seconds into local time based on system timezone + stores in struct

	DATE date = CreateDate( // Converts time.h struct into our own struct, for convenience 
		tm.tm_mday, 
		tm.tm_mon + 1, // months are 0-11 in tm_mon, so +1 to make it match normal month numbering
		tm.tm_year + 1900); // tm_year is years since 1900, so + 1900 to get the real year
	return date;
}

bool IsDate1SoonerThanDate2(DATE date1, DATE date2) {
	if (date1.year < date2.year)
		return true;
	if (date1.year > date2.year)
		return false;

	if (date1.month < date2.month)
		return true;
	if (date1.month > date2.month)
		return false;

	if (date1.day < date2.day)
		return true;
	if (date1.day > date2.day)
		return false;

	return false; // if dates are equal, default considered not sooner
}

// User Inputs

DATE GetDateFromUser() {
	bool goodInput = false;

	int day, month, year;
	fprintf(stdout, "Input the due date [DD/MM/YYYY]: ");

	do {
		int returnVal = scanf("%d/%d/%d", &day, &month, &year);

		if (returnVal != 3) {
			fprintf(stderr, "Bad input recieved. Expected 3 integers. Try again.\n");
		}
		else {
			if (!IsDayValid(day)) {
				fprintf(stderr, "Day is invalid, should be between 1-31.\n");
			}
			else if (!IsMonthValid(month)) {
				fprintf(stderr, "Month is invalid, should be between 1-12.\n");
			}
			else if (!IsYearValid(year)) {
				fprintf(stderr, "Year is invalid, should be between 0-9999.\n");
			}
			else {
				goodInput = true;
			}
		}

	} while (!goodInput);

	return CreateDate(day, month, year);
}

// Validations
bool IsDayValid(int day) {
	if (day < 1 || day > 31) {
		return false;
	}
	return true;
}

bool IsMonthValid(int month) {
	if (month < 1 || month > 12) {
		return false;
	}
	return true;
}

bool IsYearValid(int year) {
	if (year < 0 || year > 9999) {
		return false;
	}
	return true;
}