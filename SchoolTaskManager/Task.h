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

TASK CreateTask(char* NewName, char* NewCourseCode, int NewWeight, DATE NewDueDate);


// Read

void PrintTaskHeader();
void PrintTask(PTASK Task);


// Getters

char* GetTaskName(PTASK Task);

char* GetTaskCourseCode(PTASK Task);

int GetTaskWeight(PTASK Task);

DATE GetTaskDueDate(PTASK Task);


// Setters

bool SetTaskName(PTASK Task, char* TaskName);

bool SetTaskCourseCode(PTASK Task, char* CourseCode);

bool SetTaskWeight(PTASK Task, int Weight);

bool SetTaskDueDate(PTASK Task, DATE DueDate);


// User Input

void GetTaskNameFromUser(char* TaskName);

void GetCourseCodeFromUser(char* CourseCode);

int GetWeightFromUser();

DATE GetDateFromUser();

// Validations

bool IsTaskNameValid(char* TaskName);

bool IsCourseCodeValid(char* CourseCode);

bool IsWeightValid(int Weight);