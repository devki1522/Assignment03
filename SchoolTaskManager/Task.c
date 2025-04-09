// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the Task struct and functions

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
#include "date.h"
#include <stdio.h>4
#include <string.h>

PTASK CreateTask(char* NewName, char* NewCourseCode, int NewWeight, DATE NewDueDate) {
	PTASK newTask = { 0 };
	SetTaskName(newTask, NewName);
	SetTaskCourseCode(newTask, NewCourseCode);
	SetTaskWeight(newTask, NewWeight);
	SetTaskDueDate(newTask, NewDueDate);
	
	return newTask;
}

void PrintTaskHeader(PTASK Task)
{	printf("+--------------------+-------------+------------+-----------------+\n");
	printf("|     Task Name      | Course Code |   Weight   |     Due Date    |\n");
	printf("+--------------------+-------------+------------+-----------------+\n");
	
	return;
}

void PrintTask(PTASK Task)
{
	printf("| %-20s | %-9s | %-3d % | %02d/%02d/%04d |\n", Task -> name, Task-> courseCode, Task-> weight, Task-> dueDate.day,
			Task-> dueDate.month, Task-> dueDate.year );
	printf("+--------------------+-------------+------------+-----------------+\n");

	return;
}


// GETTERS

//REMINDER: GETTERS NEED TO BE CHECKED AND MODIFIED [MAYBE :) ]
char* GetTaskName(PTASK TASK) {
	return TASK->name;
}

char* GetTaskCourseCode(PTASK TASK) {
	return TASK->courseCode;
}

int GetTaskWeight(PTASK TASK) {
	return TASK->weight;
}

DATE GetTaskDueDate(PTASK TASK) {
	return TASK->dueDate;
}

// SETTERS

bool SetTaskName(PTASK Task, char* NewName) {
	strncpy(Task->name, NewName, MAX_NAME_LEN);
	return true;
}

bool SetTaskCourseCode(PTASK Task, char* NewCourseCode) {
	strncpy(Task-> courseCode, NewCourseCode, COURSE_CODE_LEN);
	return true;
}

bool SetTaskWeight(PTASK Task, int NewWeight) {
	Task->weight = NewWeight;
	return true;
}

bool SetTaskDueDate(PTASK Task, DATE NewDueDate) {
	Task->dueDate = NewDueDate;
	return true;
}
