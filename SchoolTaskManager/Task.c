// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the Task struct and functions

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
#include "date.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "IOutils.h"

TASK CreateTask(char* Name, char* CourseCode, int Weight, DATE DueDate) {
    TASK newTask = { 0 };
    SetTaskName(&newTask, Name);
    SetTaskCourseCode(&newTask, CourseCode);
    SetTaskWeight(&newTask, Weight);
    SetTaskDueDate(&newTask, DueDate);

    return newTask;
}

void PrintTaskHeader() {	
	printf("+----------------------+-------------+------------+-----------------+\n");
	printf("|      Task Name       | Course Code |  Weight %%  |   Due Date      |\n");
	printf("+----------------------+-------------+------------+-----------------+\n");
}

void PrintTask(TASK Task){
	printf("| %-20s |  %-9s  |   %3d%%     |   %02d/%02d/%04d    |\n", Task.name, Task.courseCode, Task.weight, Task.dueDate.day,
			Task.dueDate.month, Task.dueDate.year );
	printf("+----------------------+-------------+------------+-----------------+\n");
}


// GETTERS

char* GetTaskName(TASK Task) {
	return Task.name;
}

char* GetTaskCourseCode(TASK Task) {
	return Task.courseCode;
}

int GetTaskWeight(TASK Task) {
	return Task.weight;
}

DATE GetTaskDueDate(TASK Task) {
	return Task.dueDate;
}

// SETTERS

bool SetTaskName(PTASK Task, char* TaskName) {
	if (IsTaskNameValid(TaskName) == false)
		return false;

	strncpy(Task->name, TaskName, MAX_NAME_LEN);
	return true;
}

bool SetTaskCourseCode(PTASK Task, char* CourseCode) {
	if (IsCourseCodeValid(CourseCode) == false)
		return false;

	strncpy(Task->courseCode, CourseCode, COURSE_CODE_LEN);
	return true;
}

bool SetTaskWeight(PTASK Task, int Weight) {
	if (IsWeightValid(Weight) == false)
		return false;

	Task->weight = Weight;
	return true;
}

bool SetTaskDueDate(PTASK Task, DATE DueDate) {
	if (IsDateValid(DueDate) == false)
		return false;

	Task->dueDate = DueDate;
	return true;
}

// Input from user

void GetTaskNameFromUser(char* TaskName) {
	char buffer[MAX_NAME_LEN];
	do {
		fprintf(stdout, "Input a task name: ");
		fgets(buffer, MAX_NAME_LEN, stdin);

		for (int i = 0; i < MAX_NAME_LEN; i++) //Remove newline characters
			if (buffer[i] == '\n')
				buffer[i] = ' ';

	} while (!IsTaskNameValid(buffer));

	TaskName = strncpy(TaskName, buffer, MAX_NAME_LEN - 1);
	TaskName[MAX_NAME_LEN - 1] = '\0'; // Ensure null terminator exists
}


void GetCourseCodeFromUser(char* CourseCode) {
   char buffer[COURSE_CODE_LEN];
   do {
       fprintf(stdout, "Input a course code: ");
       fgets(buffer, COURSE_CODE_LEN, stdin);

	   for (int i = 0; i < MAX_NAME_LEN; i++) //Remove newline characters
		   if (buffer[i] == '\n')
			   buffer[i] = ' ';

   } while (!IsCourseCodeValid(buffer));

	// Convert chars to uppercase, couldnt do it in strncpy due to strncpy limitations
	for (int i = 0; i < COURSE_CODE_LEN; i++)
		buffer[i] = toupper(buffer[i]);

   strncpy(CourseCode, buffer, COURSE_CODE_LEN - 1);
   CourseCode[COURSE_CODE_LEN - 1] = '\0'; // Ensure null terminator exists
}

int GetWeightFromUser() {
	int weight;
	bool goodInput = false;

	do {
		fprintf(stdout, "Input a percentage weight: ");
		int returnVal = scanf("%d", &weight);

		if (returnVal != 1) {
			fprintf(stderr, "Bad input recieved. Try again.\n");
		}
		else {
			if (IsWeightValid(weight))
				goodInput = true;
		}

	} while (!goodInput);

	return weight;
}

// Validations

bool IsTaskNameValid(char* TaskName) {
	return true; // All task names are valid for now
}

bool IsCourseCodeValid(char* CourseCode) {
	if (strlen(CourseCode) != 9) {
		fprintf(stderr, "Invalid course code - should be 9 characters. Try again.\n");
		return false;
	}
	for (int i = 0; i < 4; i++) {
		if (isalpha(CourseCode[i]) == 0) { // returns 0 if isnt a alpha char
			fprintf(stderr, "Invalid course code - first 4 chars includes non-alpha values. Try again.\n");
			return false;
		}
	}
	for (int i = 4; i < 9; i++) {
		if (isdigit(CourseCode[i]) == 0) { // returns 0 if isnt a numeric char
			fprintf(stderr, "Invalid course code - last 5 chars includes non-numeric values. Try again.\n");
			return false;
		}
	}

	return true;
}

bool IsWeightValid(int Weight) {
	if (Weight < 0 || Weight > 100) {
		fprintf(stderr, "Invalid task weight - Should be between 0 - 100 inclusive. Try again.\n");
		return false;
	}

	return true;
}
