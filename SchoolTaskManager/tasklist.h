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
void AddListNode(LISTNODE** list,TASK Task);

// Delete

/// Loops through the linkedlist
/// Free node and remove from list
void RemoveListNode(LISTNODE** Node, LISTNODE* NodeToDelete);

/// Runs RemoveListNode on all nodes
void DeleteList(LISTNODE** Node);

// Read

/// Prints task from each node
void PrintAllList(LISTNODE* Node);

/// Loops through the linkedlist
/// Prints task from each node that has a certain course code
void PrintByCourseCode(LISTNODE* Node, char* CourseCode);

/// Loops through the linkedlist
/// Prints next upcoming 'Num' tasks
void PrintUpcomingTask(LISTNODE* Node, int Num);

/// Loops through the linkedlist
/// 1. Ask for CC from user
/// 2. PrintByCourseCode all tasks that belong to the input CC
/// 3. Ask for TaskName from user
/// 4. Call FindListNode with info
/// 5. If FindListNode returns null, print "cant find"
LISTNODE* SearchLinkedList(LISTNODE* Node); 

/// Recursive search through LL until finds task with matching CC and TaskName
LISTNODE* FindListNode(LISTNODE* Current, char* CourseCode, char* TaskName); // make a find recursive function for searching 


