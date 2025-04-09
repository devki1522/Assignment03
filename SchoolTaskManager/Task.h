// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Interface of the Task struct and functions

#pragma once

#include "date.h"

#include <stdbool.h>

#define MAX_NAME_LEN 20 
#define COURSE_CODE_LEN 10 // Conestoga course codes are 9 chars, plus \0

typedef struct Task {
	char name[MAX_NAME_LEN];
	char courseCode[COURSE_CODE_LEN];
	int weight;
	DATE dueDate;
} TASK, *PTASK;

// Create

PTASK CreateTask(char* Name, char* CourseCode, int Weight, DATE DueDate);

// Read

void PrintTaskHeader(PTASK Task);
void PrintTask(PTASK Task);

// Getters

char* GetTaskName(PTASK Task);

char* GetTaskCourseCode(PTASK Task);

int GetTaskWeight(PTASK Task);

DATE GetTaskDueDate(PTASK Task);

// Setters

bool SetTaskName(PTASK Task, char* Name);

bool SetTaskCourseCode(PTASK Task, char* CourseCode);

bool SetTaskWeight(PTASK Task, int Weight);

bool SetTaskDueDate(PTASK Task, DATE DueDate);

// Delete - not needed

