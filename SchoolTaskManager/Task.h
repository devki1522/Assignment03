// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Interface of the Task struct and functions

#pragma once

#include "date.h"

#define MAX_NAME_LEN 20 
#define COURSE_CODE_LEN 10 // Conestoga course codes are 9 chars, plus \0

typedef struct Task {
	char name[MAX_NAME_LEN];
	char courseCode[COURSE_CODE_LEN];
	int weight;
	DATE dueDate;
} TASK, *PTASK;

// Create

TASK CreateTask(char* Name, char* CourseCode, int Weight, DATE DueDate);

// Read

void PrintTask(TASK Task);

// Getters

char* GetTaskName(TASK Task);

char* GetTaskCourseCode(TASK Task);

int GetTaskWeight(TASK Task);

DATE GetTaskDueDate(TASK Task);

// Setters

void SetTaskName(PTASK Task, char* Name);

void SetTaskCourseCode(PTASK Task, char* CourseCode);

void SetTaskWeight(PTASK Task, int Weight);

void SetTaskDueDate(PTASK Task, DATE DueDate);

// Delete - not needed

