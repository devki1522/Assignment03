#pragma once


typedef struct listnode {
	TASK task;
	struct listnode* next;
} LISTNODE, * PLISTNODE;

LISTNODE* AddListNode(TASK task);

void RemoveListNode(LISTNODE* node);

void DeleteList(LISTNODE* listnode);

void PrintAllList(LISTNODE* head);

void PrintByCourseCode(LISTNODE* head);

void PrintUpcomingTask(LISTNODE* head);

TASK SEarchLinkedList(); // make a find recursive function for searching 


