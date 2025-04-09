// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the Task struct and functions

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
#include "date.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
	printf("|      Task Name       | Course Code |   Weight   |     Due Date    |\n");
	printf("+----------------------+-------------+------------+-----------------+\n");
}

void PrintTask(TASK Task){
	printf("| %-20s |  %-9s  |    %3d%%    |   %02d/%02d/%04d    |\n", Task.name, Task.courseCode, Task.weight, Task.dueDate.day,
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
	DATE currentDate = GetCurrentDate();

	if (IsDate1SoonerThanDate2(DueDate, currentDate)) {
		fprintf(stderr, "Due date cannot be set to a time before today.\n");
		return false;
	}

	Task->dueDate = DueDate;
	return true;
}

// Input from user

void GetTaskNameFromUser(char* TaskName) {
	bool goodInput = false;

	fprintf(stdout, "Input a task name: ");

	do {
		int returnVal = scanf("%20s", TaskName);

		if (returnVal != 1) {
			fprintf(stderr, "Bad input recieved. Try again.\n");
		}
		else {
			if (IsTaskNameValid(TaskName))
				goodInput = true;
		}
			
	} while (!goodInput);
}


void GetCourseCodeFromUser(char* CourseCode) {
	bool goodInput = false;

	fprintf(stdout, "Input a course code: ");

	do {
		int returnVal = scanf("%10s", CourseCode);

		if (returnVal != 1) {
			fprintf(stderr, "Bad input recieved. Try again.\n");
		}
		else {
			if (IsCourseCodeValid(CourseCode))
				goodInput = true;
		}

	} while (!goodInput);
}

int GetWeightFromUser() {
	int weight;
	bool goodInput = false;

	fprintf(stdout, "Input a percentage weight: ");

	do {
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
		fprintf(stderr, "Invalid course code - should be 9 characters.\n");
		return false;
	}
	for (int i = 0; i < 4; i++) {
		if (isalpha(CourseCode[i]) == 0) { // returns 0 if isnt a alpha char
			fprintf(stderr, "Invalid course code - first 4 chars includes non-alpha values.\n");
			return false;
		}
	}
	for (int i = 4; i < 9; i++) {
		if (isdigit(CourseCode[i]) == 0) { // returns 0 if isnt a numeric char
			fprintf(stderr, "Invalid course code - last 5 chars includes non-numeric values.\n");
			return false;
		}
	}

	return true;
}

bool IsWeightValid(int Weight) {
	if (Weight < 0 || Weight > 100) {
		fprintf(stderr, "Invalid task weight - Should be between 0 - 100 inclusive.\n");
		return false;
	}

	return true;
}
