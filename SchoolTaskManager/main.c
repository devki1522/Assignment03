// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// A program that allows you to manage your upcoming school assignments and quizzes

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
#include "fileIO.h"
#include <stdio.h>
#include <ctype.h>
#include "IOutils.h"

/// Prints start up message (welcome, urgent tasks, outdated task notif.)
void PrintMOTD(PLISTNODE TaskList);

/// Prints user menu
void PrintMenu();

int main(void) {
	PLISTNODE taskList = LoadTasksfromDatabase();

	PrintMOTD(taskList);

	bool running = true;
	do {
		PrintMenu();

		char userSelection = toupper(GetChar());

		switch (userSelection) { //Put the cases in {} due to: https://stackoverflow.com/questions/92396/why-cant-variables-be-declared-in-a-switch-statement
		case 'A': // Add New Task
		{
			char taskName[MAX_NAME_LEN];
			GetTaskNameFromUser(taskName);

			char courseCode[COURSE_CODE_LEN];
			GetCourseCodeFromUser(courseCode);

			int weight = GetWeightFromUser();

			DATE date = GetDateFromUser();

			TASK task = CreateTask(taskName, courseCode, weight, date);

			if (AddListNode(&taskList, task)) {
				fprintf(stdout, "Task Added Sucessfully");
			}
			break;
		}
		case 'B': // Remove Task
		{
			PLISTNODE nodeToRemove = SearchLinkedList(taskList);
			if (nodeToRemove == NULL) 
				break; // Error message printed in function, so not needed here

			if (RemoveListNode(&taskList, nodeToRemove)) {
				fprintf(stdout, "Task Removed Sucessfully.");
			}
			
			break;
		}
		case 'C': // Update Task
		{
			PTASK taskToUpdate = &SearchLinkedList(taskList)->task;
			if (taskToUpdate == NULL) {
				fprintf(stderr, "Task not found.\n");
				break;
			}

			// Ask what to update
			fprintf(stdout, "What would you like to update?\n"
				"A - Task Name\n"
				"B - Course Code\n"
				"C - Weight\n"
				"D - Due Date\n"
				"Your selection: ");

			char updateSelection = toupper(GetChar());

			switch (toupper(updateSelection)) {
			case 'A': // Task Name
			{
				char taskName[MAX_NAME_LEN];
				GetTaskNameFromUser(taskName);
				if (SetTaskName(taskToUpdate, taskName)) {
					fprintf(stdout, "Task Name Updated");
				}
				break;
			}
			case 'B': // Course Code
			{
				char courseCode[COURSE_CODE_LEN];
				GetCourseCodeFromUser(courseCode);
				if (SetTaskCourseCode(taskToUpdate, courseCode)) {
					fprintf(stdout, "Course Code Upadted.");
				}
				break;
			}
			case 'C': // Weight
			{
				int weight = GetWeightFromUser();
				if (SetTaskWeight(taskToUpdate, weight)){
					fprintf(stdout, "Task Weight Updated");
				}
				break;
			}
			case 'D': // Due Date
			{
				DATE date = GetDateFromUser();

				// Create a new task with the updated due date
				TASK updatedTask = *taskToUpdate;
				if (SetTaskDueDate(&updatedTask, date)) {
					fprintf(stdout, "Task Due Date Updated ");
				}

				// Remove the old task and add the updated task
				PLISTNODE nodeToUpdate = FindListNode(taskList, taskToUpdate->courseCode, taskToUpdate->name);
				RemoveListNode(&taskList, nodeToUpdate);

				// Add the updated task to the list so that it re-sorts into the right place
				AddListNode(&taskList, updatedTask);
				break;
			}
			default:
				fprintf(stderr, "Invalid selection.\n");
				break;
			}

			break;
		}
		case 'D': // Display All Tasks
			PrintAllList(taskList);
			break;
		case 'E': // Display a set of tasks
		{
			if (taskList == NULL) {
				fprintf(stderr, "No tasks in the list.\n");
				break;
			}

			fprintf(stdout, "How would you like to filter the tasks?\n"
				"A - By course code\n"
				"B - By most urgent (date)\n"
				"Your selection: ");

			char filterSelection = toupper(GetChar());

			switch (toupper(filterSelection)) {
			case 'A': // By course code
				{
					char courseCode[COURSE_CODE_LEN];
					GetCourseCodeFromUser(courseCode);
					PrintByCourseCode(taskList, courseCode);
					break;
				}
			case 'B': // By due date
				{
					int numTasks;
					fprintf(stdout, "How many upcoming tasks would you like to see? ");
					while (fscanf(stdin, "%d", &numTasks) != 1 || numTasks < 0)
						fprintf(stderr, "Input not an integer or is negative. Please try again: ");
					PrintUpcomingTask(taskList, numTasks);
					break;
				}
			default:
					fprintf(stderr, "Invalid selection.\n");
			}

			break;
			}
		case 'F': // Display upcoming tasks
			if (taskList == NULL) {
				fprintf(stderr, "No tasks in the list.\n");
				break;
			}

			// Print the first task in the list
			fprintf(stdout, "Next due task:\n");
			PrintUpcomingTask(taskList, 1);
			break;
		case 'G': // Remove past-due tasks
			if (taskList == NULL) {
				fprintf(stderr, "No tasks in the list.\n");
				break;
			}

			PLISTNODE curNode = taskList;
			while (curNode != NULL) {
				if (IsDate1SoonerThanDate2( GetTaskDueDate(curNode->task), GetCurrentDate() )) {
					PLISTNODE temp = curNode;
					curNode = curNode->next;
					RemoveListNode(&taskList, temp);
				}
				else {
					curNode = curNode->next;
				}
			}

			printf("All past-due tasks have been removed.\n");
			break;
		case 'H': // Quit
			fprintf(stdout, "Have a good day! Exiting...\n");
			running = false;
			break;
		default:
			fprintf(stderr, "Invalid selection. Please try again.\n");
			break;
		}
		

	} while (running);

	SaveTaskstoDatabase(taskList);

	DeleteList(&taskList);
}



void PrintMOTD(PLISTNODE TaskList) {
	fprintf(stdout,
		"~~~ Welcome to the School Task Manager! ~~~\n"
		"Here you can manage all of your upcoming school tasks.\n"
		"Created by - Devki S, Spencer W, Tanveer S. J\n\n"
	);

	if (TaskList == NULL) // Stop MOTD if list is empty
		return;

	fprintf(stdout, "Here are your next most urgent tasks:\n");
	PrintUpcomingTask(TaskList, 3);

	if ( IsDate1SoonerThanDate2(GetTaskDueDate(TaskList->task), GetCurrentDate()) ) {
		fprintf(stdout, "\nYou have some past-due tasks! If you'd like to remove them, run option G.\n\n");
	}
}

void PrintMenu() {
	fprintf(stdout, 
		"\n\nPlease select an option:\n"
		"A - Add a new task\n"
		"B - Remove a task\n"
		"C - Update a task\n"
		"D - Display all tasks\n"
		"E - Display a set of tasks\n"
		"F - Display next due task\n"
		"G - Remove past-due tasks\n"
		"H - Quit School Task Manager\n"
		"\nYour Selection: "
	);
}