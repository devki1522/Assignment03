// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the file Input/Output functions

#define _CRT_SECURE_NO_WARNINGS
#include "fileIO.h"
#include "taskList.h"
#include <stdio.h>
#include "Task.h"
#include <stdlib.h>

PLISTNODE LoadTasksfromDatabase() {  
FILE* file = fopen("database.txt", "r");  
if (file == NULL) {  
	printf("Error opening file.\n");  
	return NULL;  
}  
PLISTNODE list = NULL;  
PLISTNODE newNode = NULL;  

while (1) {  
	newNode = (PLISTNODE)malloc(sizeof(LISTNODE));  
	if (newNode == NULL) {  
		printf("Memory allocation failed.\n");  
		break;  
	}  

	// Attempt to read a task from the file  
	if (fscanf(file, "%20[^\n]\n%10[^\n]\n%d\n%d/%d/%d\n",
		newNode->task.name,  
		newNode->task.courseCode,  
		&newNode->task.weight,  
		&newNode->task.dueDate.day,  
		&newNode->task.dueDate.month,  
		&newNode->task.dueDate.year) != 6) {  
		free(newNode);  
		break;  
	}  

	printf("Loaded task: %s\n", newNode->task.name);  

	AddListNode(&list, newNode->task);
}  

fclose(file);  
return list;  
}

void SaveTaskstoDatabase(PLISTNODE List) {
	FILE* file = fopen("database.txt", "w");
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}
	PLISTNODE current = List;
	while (current != NULL) {
		fprintf(file, "%s\n%s\n%d\n%d/%d/%d\n", 
			current->task.name,
			current->task.courseCode,
			current->task.weight,
			current->task.dueDate.day,
			current->task.dueDate.month,
			current->task.dueDate.year);
		current = current->next;
	}
	
	fclose(file);
}