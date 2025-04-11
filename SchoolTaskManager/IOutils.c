// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the helper I/O functions

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "IOutils.h"

void ClearStdin() {
	int c;
	while ((c = fgetc(stdin)) != '\n' && c != EOF);
}

char GetChar() {
	char input;

	while (scanf(" %c", &input) != 1); //scan until char received

	ClearStdin();
	return input;
}