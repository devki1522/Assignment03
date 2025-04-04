// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// A program that allows you to manage your upcoming school assignments and quizzes

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
#include "fileIO.h"
#include <stdio.h>
#include <ctype.h>

/// Prints start up message (welcome, urgent tasks, outdated task notif.)
void printMOTD();

/// Prints user menu
void printMenu();

int main(void) {

}


void printMOTD() {

}

void printMenu() {
	fprintf(stdout, 
		"Please select an option:\n"
		"A - Add a new task\n"
		"B - Remove a task\n"
		"C - Update a task\n"
		"D - Display all tasks\n"
		"E - Display a set of tasks\n"
		"F - Display next due task\n"
		"G - Remove past-due tasks\n"
		"H - Quit School Task Manager\n"
		"\nYour Selection:"
	);
}