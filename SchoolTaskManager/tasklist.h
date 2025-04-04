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
LISTNODE* AddListNode(TASK Task);

// Delete

/// Free node and remove from list
void RemoveListNode(LISTNODE* Node);

/// Runs RemoveListNode on all nodes
void DeleteList(LISTNODE* Head);

// Read

/// Prints task from each node
void PrintAllList(LISTNODE* Head);

/// Prints task from each node that has a certain course code
void PrintByCourseCode(LISTNODE* Head, char* CourseCode);

/// Prints next upcoming 'Num' tasks
void PrintUpcomingTask(LISTNODE* Head, int Num);

/// 1. Ask for CC from user
/// 2. PrintByCourseCode all tasks that belong to the input CC
/// 3. Ask for TaskName from user
/// 4. Call FindListNode with info
/// 5. If FindListNode returns null, print "cant find"
LISTNODE* SearchLinkedList(); 

/// Recursive search through LL until finds task with matching CC and TaskName
LISTNODE* FindListNode(LISTNODE* Current, char* CourseCode, char* TaskName); // make a find recursive function for searching 


