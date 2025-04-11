// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Interface of the Date struct and functions

#pragma once

#include <stdbool.h>

typedef struct date {
	int day;
	int month;
	int year;
} DATE;

/// Create new date
DATE CreateDate(int day, int month, int year);

/// Call some library to get current system date, runs CreateDate + return
DATE GetCurrentDate();

/// Compares two dates, returns true if date1 is sooner than date2
bool IsDate1SoonerThanDate2(DATE date1, DATE date2);

// User Inputs -------------------

/// Get a valid date from user input
DATE GetDateFromUser();

// Validators --------------------

/// Check if day is valid (1-31) (Ignores per-month limit (ie, April only 30 days))
bool IsDayValid(int day);

/// Check if month is valid (1-12)
bool IsMonthValid(int month);

/// Check if year is valid (0-9999)
bool IsYearValid(int year);

/// Checks if the entire date is valid (day, month, year)
bool IsDateValid(DATE date);