// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Interface of the List struct and functions

#pragma once

#include "task.h"

typedef struct listnode {
	TASK task;
	struct listnode* next;
} LISTNODE, *PLISTNODE;

// Create

/// Adds a new node into the list **IN CORRECT ORDER (head = soonest, tail = latest)**
bool AddListNode(PLISTNODE* List, TASK Task);

// Delete

/// Loops through the linkedlist
/// Free node and remove from list
bool RemoveListNode(PLISTNODE* List, PLISTNODE NodeToDelete);

/// Runs RemoveListNode on all nodes
void DeleteList(PLISTNODE* List);

// Read

/// Prints task from each node
void PrintAllList(PLISTNODE List);

/// Loops through the linkedlist
/// Prints task from each node that has a certain course code
void PrintByCourseCode(PLISTNODE List, char* CourseCode);

/// Loops through the linkedlist
/// Prints next upcoming 'Num' tasks
void PrintUpcomingTask(PLISTNODE List, int Num);

/// Loops through the linkedlist
/// 1. Ask for CC from user
/// 2. PrintByCourseCode all tasks that belong to the input CC
/// 3. Ask for TaskName from user
/// 4. Call FindListNode with info
/// 5. If FindListNode returns null, print "cant find"
PLISTNODE SearchLinkedList(PLISTNODE List);

/// Recursive search through LL until finds task with matching CC and TaskName
PLISTNODE FindListNode(PLISTNODE Current, char* CourseCode, char* TaskName); 

/// Returns number of tasks in list with the same course code
int TasksWithCourseCodeCount(PLISTNODE List, char* CourseCode);