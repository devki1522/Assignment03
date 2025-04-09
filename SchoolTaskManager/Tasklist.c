// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Implementation of the List struct and functions

#include "taskList.h"
#include "task.h"
#include "date.h"
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
		return;		
	}
	//sort the list to save the new node
	LISTNODE* Current = list;
	LISTNODE* Previous = NULL;
	while (Current != NULL && IsDate1SoonerThanDate2(Current->task.dueDate, Task.dueDate)) {
		Previous = Current;
		Current = Current->next;
	}
	if (Previous == NULL) {
		NewNode->next = list;
		return;
	}
	else {
		NewNode->next = Current;
		Previous->next = NewNode;
	}
	return;
}
void RemoveListNode(LISTNODE* Node, LISTNODE* NodeToDelete) {
	// check if the task exists and delete it
	if (Node == NULL || NodeToDelete == NULL) {
		fprintf(stderr, "List is Empty. ");
		return ;
	}
	if (Node == NodeToDelete) {		
		LISTNODE* NewNode = Node->next;
		free(Node);
		return ;
	}
	LISTNODE* Current = Node;
	while (Current != NULL && Current->next != NodeToDelete)
	{
		Current = Current->next;
	}
	if (Current != NULL) {
		Current->next = NodeToDelete->next;
		free(NodeToDelete);
	}
	else 
		fprintf(stderr, "Node not found in the list.\n");
}


void DeleteList(LISTNODE* Node) {
	// delete all nodes in the list one by one 
	LISTNODE* Current = Node;
	LISTNODE* NextNode;
	while (Current != NULL) {
		NextNode = Current->next;
		free(Current);
		Current = NextNode;
	}
	
}

void PrintAllList(LISTNODE* Node) {
	LISTNODE* Current = Node;
	
	while (Current != NULL) {
		TASK Task = Current->task;
		PrintTask(&Task);
		Current = Current->next;
	}
	printf("\n");
}

void PrintByCourseCode(LISTNODE* Node, char* CourseCode) {
	LISTNODE* Current = Node;
	
	while (Current != NULL) {
		TASK Task = Current->task;
		if (strcmp(Current->task.courseCode, CourseCode) == 0) {
			PrintTask(&Task);
		}
		Current = Current->next;
	}
	printf("\n");

}

void PrintUpcomingTask(LISTNODE* Node, int Num) {
	LISTNODE* Current = Node;
	
	int count = 0;
	while (Current != NULL && count < Num) {
		TASK Task = Current->task;
		PrintTask(&Task);
		Current = Current->next;
		count++;
	}
	printf("\n");
}

LISTNODE* SearchLinkedList(LISTNODE* Node) {
	LISTNODE* list = {0};
	printf("Enter the course code: ");
	char CourseCode[COURSE_CODE_LEN] = GetTaskCourseCodeFromUser;	
	PrintByCourseCode(list, CourseCode);
	printf("Enter the task name: ");
	char TaskName[MAX_NAME_LEN]= GetTaskNameFromUser;
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


