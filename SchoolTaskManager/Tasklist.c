// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the List struct and functions

#include "taskList.h"
#include "task.h"
#include <stdio.h>
#include <ctype.h>

void AddListNode(LISTNODE* list, TASK Task) {
	// allocate memory for a new list node
	LISTNODE* NewNode = (LISTNODE*)malloc(sizeof(LISTNODE));
	if (NewNode == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return;
	}
	// copy stuff 
	NewNode->task = Task;
	NewNode->next = NULL;
	if (list == NULL) {
		list = NewNode;
		return;
	}
	//sort the list to save the new node
	LISTNODE* Current = list;
	LISTNODE* Previous = NULL;
	while (Current != NULL && CompareDates(Current->task.dueDate, Task.dueDate) < 0) {
		Previous = Current;
		Current = Current->next;
	}
	if (Previous == NULL) {
		NewNode->next = list;
		list = NewNode;
	}
	else {
		NewNode->next = Current;
		Previous->next = NewNode;
	}
}
void RemoveListNode(LISTNODE* Node) {
	// check if the task exists and delete it
    if (scanf("%s",Node->task.courseCode) != 1) {
        fprintf(stderr, "Error reading Course Code\n");
        return NULL;
    }
    if (scanf("%s", Node->task.name) != 1) {
        fprintf(stderr, "Error reading Task Name\n");
        return NULL;
    }
	if (Node == NULL) {
		fprintf(stderr, "Node is NULL\n");
		return;
	}
	free(Node);
	Node = NULL;
}

void DeleteList(LISTNODE* Head) {
	// delete all nodes in the list one by one 
	LISTNODE* Current = Head;
	LISTNODE* NextNode;
	while (Current != NULL) {
		NextNode = Current->next;
		RemoveListNode(Current);
		Current = NextNode;
	}

}

void PrintAllList(LISTNODE* Head) {
	LISTNODE* Current = Head;
	while (Current != NULL) {
		PrintTask(Current->task);
		Current = Current->next;
	}
	printf("\n");
}

void PrintByCourseCode(LISTNODE* Head, char* CourseCode) {
	LISTNODE* Current = Head;
	while (Current != NULL) {
		if (strcmp(Current->task.courseCode, CourseCode) == 0) {
			PrintTask(Current->task);
		}
		Current = Current->next;
	}
	printf("\n");

}

void PrintUpcomingTask(LISTNODE* Head, int Num) {
	LISTNODE* Current = Head;
	int count = 0;
	while (Current != NULL && count < Num) {
		PrintTask(Current->task);
		Current = Current->next;
		count++;
	}
	printf("\n");
}

LISTNODE* SearchLinkedList() {
	LISTNODE* list = {0};
	char CourseCode[COURSE_CODE_LEN];
	GetTaskCourseCode(&list->task, CourseCode);
	PrintByCourseCode(list, CourseCode);
	char TaskName[MAX_NAME_LEN]= GetTaskName;
	LISTNODE* FoundNode = FindListNode(list, CourseCode, TaskName);
	if (FoundNode == NULL) {
		printf("Task not found\n");
		return NULL;
	}
	else {
		PrintTask(&FoundNode->task);
		return FoundNode;
	}
	
}

LISTNODE* FindListNode(LISTNODE* Current, char* CourseCode, char* TaskName) {
	if (Current == NULL) {
		return NULL;
	}
	if (strcmp(Current->task.courseCode, CourseCode) == 0 && strcmp(Current->task.name, TaskName) == 0) {
		return Current;
	}
	return FindListNode(Current->next, CourseCode, TaskName);
}


