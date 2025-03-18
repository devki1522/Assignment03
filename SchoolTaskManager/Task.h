// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Interface of the Task struct and functions

#pragma once

#include "date.h"

#define MAX_NAME_LEN 20
#define MAX_DESC_LEN 200
#define COURSE_CODE_LEN 10 // Course code is 9 chars, plus \0

typedef struct Task {
	char name[MAX_NAME_LEN];
	char courseCode[COURSE_CODE_LEN];
	int weight;
	DATE dueDate;
} TASK, *PTASK;

// Create

TASK CreateTask(char* Name, char* CourseCode, int Weight, DATE DueDate);

// Read / Getters

void PrintTask(TASK Task);

char* GetTaskName(TASK Task);

char* GetTaskCourseCode(TASK Task);

int GetTaskWeight(TASK Task);

DATE GetTaskDueDate(TASK Task);

// Update / Setters

void SetTaskName(TASK Task, char* Name);

void SetTaskCourseCode(TASK Task, char* CourseCode);

void SetTaskWeight(TASK Task, int Weight);

void SetTaskDueDate(TASK Task, DATE DueDate);

// Delete