// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the file Input/Output functions

#define _CRT_SECURE_NO_WARNINGS
#include "fileIO.h"
#include "taskList.h"
#include <stdio.h>
#include "Task.h"

PLISTNODE LoadTasksfromDatabase() {  
FILE* file = fopen("database.txt", "r");  
if (file == NULL) {  
	printf("Error opening file.\n");  
	return NULL;  
}  
PLISTNODE list = NULL;
TASK task = { 0 };

while (1) {
    // AddListNode allocates and owns the linked-list node.
    if (fscanf(file, "%19[^\n]\n%9[^\n]\n%d\n%d/%d/%d\n",
        task.name,
        task.courseCode,
        &task.weight,
        &task.dueDate.day,
        &task.dueDate.month,
        &task.dueDate.year) != 6) {
        break;
    }

    if (!AddListNode(&list, task)) {
        printf("Memory allocation failed.\n");
        break;
    }
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