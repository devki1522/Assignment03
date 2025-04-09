// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the List struct and functions

#include "taskList.h"
#include "task.h"
#include "date.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool AddListNode(PLISTNODE* List, TASK Task) {	

	// Allocate memory for a new list node
	PLISTNODE newNode = (PLISTNODE)malloc(sizeof(LISTNODE));
	if (newNode == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return false;
	}
	// Copy stuff 
	newNode->task = Task;
	newNode->next = NULL;

	// If list doesn't exist , create it
	if (*List == NULL) {
		*List = newNode;
		return true;
	}
			
	// Sort the list to save the new node
	PLISTNODE current = *List;
	PLISTNODE previous = NULL;
	while (current != NULL && IsDate1SoonerThanDate2(current->task.dueDate, Task.dueDate)) {
		previous = current;
		current = current->next;
	}
	if (previous == NULL) {
		newNode->next = *List;
		*List = newNode;
		return true;
	}
	else {
		newNode->next = current;
		previous->next = newNode;
	}
	return true;
}

bool RemoveListNode(PLISTNODE* List, PLISTNODE NodeToDelete) {
	// check if the task exists and delete it
	if (*List == NULL) {
		fprintf(stderr, "List is Empty.\n");
		return false;
	}

	if (NodeToDelete == NULL) {
		fprintf(stderr, "NodeToDelete is NULL.\n");
		return false;
	}

	if (*List == NodeToDelete) { // If first node is node to delete
		*List = NodeToDelete->next;
		free(NodeToDelete);
		return true;
	}

	PLISTNODE current = *List;
	while (current->next != NULL && current->next != NodeToDelete)
		current = current->next;

	if (current->next == NULL) {
		fprintf(stderr, "Node not found in the list.\n");
		return true; // If not in list, all good
	}

	current->next = NodeToDelete->next; // Remove node from list
	free(NodeToDelete);

	return true;
}


void DeleteList(PLISTNODE* List) {
	// delete all nodes in the list one by one 
	PLISTNODE current = *List;
	PLISTNODE nextNode;
	while (current != NULL) {
		nextNode = current->next;
		free(current);
		current = nextNode;
	}

	*List = NULL; // Set ptr back to NULL (not to reset, just to avoid dangling ptr)
}

void PrintAllList(PLISTNODE List) {
	PLISTNODE current = List;

	if (current == NULL) {
		printf("No tasks in the list.\n");
		return;
	}

	PrintTaskHeader();

	while (current != NULL) {
		PrintTask(current->task);
		current = current->next;
	}
}

void PrintByCourseCode(PLISTNODE List, char* CourseCode) {
	PLISTNODE current = List;

	if (TasksWithCourseCodeCount(List, CourseCode) == 0) {
		printf("No tasks with that course code in the list.\n");
		return;
	}

	PrintTaskHeader();

	while (current != NULL) {
		TASK task = current->task;
		if (strcmp(task.courseCode, CourseCode) == 0)
			PrintTask(task);

		current = current->next;
	}
}

void PrintUpcomingTask(PLISTNODE List, int Num) {
	PLISTNODE current = List;

	if (current == NULL) {
		printf("No tasks in the list.\n");
		return;
	}

	PrintTaskHeader();
	
	int count = 0;
	while (count < Num) {
		if (current == NULL) {
			printf("No more tasks in the list.\n");
			return;
		}
		PrintTask(current->task);
		current = current->next;
		count++;
	}
}

PLISTNODE SearchLinkedList(PLISTNODE List) {
	PLISTNODE list = {0};

	// COURSE CODE SORTING
	printf("Enter the course code: ");
	char courseCode[COURSE_CODE_LEN];
	GetCourseCodeFromUser(courseCode);

	PrintByCourseCode(list, courseCode);

	// TASK NAME SORTING
	printf("Enter the task name: ");
	char taskName[MAX_NAME_LEN];
	GetTaskNameFromUser(taskName);

	PLISTNODE foundNode = FindListNode(list, courseCode, taskName);

	if (foundNode == NULL) {
		printf("Task not found\n");
		return NULL;
	}

	PrintTaskHeader();
	PrintTask(foundNode->task);
	return foundNode;
	
	
}

PLISTNODE FindListNode(PLISTNODE Current, char* CourseCode, char* TaskName) {
	// Base case 1 (not in list)
	if (Current == NULL) { 
		return NULL;
	}

	// Base case 2 (in list)
	if (strcmp(Current->task.courseCode, CourseCode) == 0 && strcmp(Current->task.name, TaskName) == 0) {
		return Current;
	}

	// Iterative case
	return FindListNode(Current->next, CourseCode, TaskName);
}

int TasksWithCourseCodeCount(PLISTNODE List, char* CourseCode) {
	PLISTNODE current = List;
	int count;

	while (current != NULL) {
		if (strcmp(current->task.courseCode, CourseCode) == 0)
			count++;
			
		current = current->next;
	}

	return count;
}