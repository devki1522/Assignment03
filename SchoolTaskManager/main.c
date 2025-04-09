// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// A program that allows you to manage your upcoming school assignments and quizzes

#define _CRT_SECURE_NO_WARNINGS
#include "task.h"
#include "fileIO.h"
#include <stdio.h>
#include <ctype.h>

/// Prints start up message (welcome, urgent tasks, outdated task notif.)
void printMOTD(PLISTNODE TaskList, DATE CurDate);

/// Prints user menu
void printMenu();

int main(void) {
	DATE curDate = { 0 };// GetCurrentDate();
	PLISTNODE taskList = LoadTasksfromDatabase();

	printMOTD(taskList, curDate);

	bool running = true;
	char userSelection;
	do {
		printMenu();

		while (fscanf(stdin, " %c ", &userSelection)); //Scan until char token is recieved

		switch (toupper(userSelection)) { //Put the cases in {} due to: https://stackoverflow.com/questions/92396/why-cant-variables-be-declared-in-a-switch-statement
		case 'A': // Add New Task
		{
			TASK newTask;

			// Set task name [no validation]
			char name[MAX_NAME_LEN];
			fprintf(stdout, "Enter the name of the task: ");
			while (fscanf(stdin, "%s", name) != 1);
			SetTaskName(&newTask, name);

			// Set task course code [validation]
			char courseCode[COURSE_CODE_LEN];
			fprintf(stdout, "Enter the course code: ");
			fscanf(stdin, "%s", courseCode);
			while (SetTaskCourseCode(&newTask, courseCode) == false) {
				fprintf(stderr, "Invalid course code. Please try again: ");
				fscanf(stdin, "%s", courseCode);
			}

			// Set task weight
			int weight;
			fprintf(stdout, "Enter the weight of the task: ");
			while (fscanf(stdin, "%d", &weight) != 1 || weight < 0)
				fprintf(stderr, "Input not an integer or is negative. Please try again: ");
			SetTaskWeight(&newTask, weight);

			// Set task due date
			int day, month, year;
			fprintf(stdout, "Enter the due date (DD/MM/YYYY): ");
			while (fscanf(stdin, "%d/%d/%d", &day, &month, &year) != 3
					&& IsDayValid(day) 
					&& IsMonthValid(month) 
					&& IsYearValid(year))
				fprintf(stdout, "The input date is invalid. Please try again: ");

			SetTaskDueDate(&newTask, CreateDate(day, month, year));

			AddListNode(taskList, newTask);
			break;
		}
		case 'B': // Remove Task
		{
			RemoveListNode(SearchLinkedList());

			break;
		}
		case 'C': // Update Task
		{
			fprintf(stdout, "Which task would you like to update?\n");
			TASK* taskToUpdate = SearchLinkedList();
			if (taskToUpdate == NULL) {
				fprintf(stderr, "Task not found.\n");
				break;
			}

			UpdateTask(taskToUpdate);

			break;
		}
		case 'D': // Display All Tasks
		{
			if (taskList == NULL) {
				fprintf(stderr, "No tasks in the list.\n");
				break;
			}

			PrintAllList(taskList);
			break;
		}
		case 'E': // Display a set of tasks
		{
			if (taskList == NULL) {
				fprintf(stderr, "No tasks in the list.\n");
				break;
			}

			fprintf(stdout, "How would you like to filter the tasks?\n"
				"A - By course code\n"
				"B - By upcoming\n"
				"Your selection: ");

			char filterSelection;
			while (fscanf(stdin, " %c ", &filterSelection) != 1);
			switch (toupper(filterSelection)) {
			case 'A': // By course code
				{
					char courseCode[COURSE_CODE_LEN];
					fprintf(stdout, "Enter the course code: ");
					while (fscanf(stdin, "%s", courseCode) != 1);
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
			{
				if (taskList == NULL) {
					fprintf(stderr, "No tasks in the list.\n");
					break;
				}
				// Print the first task in the list
				fprintf(stdout, "Next due task:\n");
				PrintUpcomingTask(taskList, 1);
				break;
			}
		case 'G': // Remove past-due tasks
			{
				if (taskList == NULL) {
					fprintf(stderr, "No tasks in the list.\n");
					break;
				}

				PLISTNODE curNode = taskList;
				while (curNode != NULL) {
					if (IsDate1SoonerThanDate2(GetTaskDueDate(&curNode->task), curDate)) {
						PLISTNODE temp = curNode;
						curNode = curNode->next;
						RemoveListNode(temp);
					}
					else {
						curNode = curNode->next;
					}
				}

				break;
			}
		case 'H': // Quit
			{
				fprintf(stdout, "Have a good day! Exiting...\n");
				running = false;
				break;
			}
		}

	} while (running);

	SaveTaskstoDatabase(taskList);

	DeleteList(taskList);
}



void printMOTD(PLISTNODE TaskList, DATE CurDate) {
	fprintf(stdout,
		"~~~ Welcome to the School Task Manager! ~~~\n"
		"Here you can manage all of your upcoming school tasks.\n"
		"Created by - Devki S, Spencer W, Tanveer S. J\n\n"
	);

	if (TaskList == NULL) // Stop MOTD if list is empty
		return;

	fprintf(stdout, "Here are your next most urgent tasks:\n");
	PrintUpcomingTask(TaskList, 3);

	if ( IsDate1SoonerThanDate2(GetTaskDueDate(&TaskList->task), CurDate) ) {
		fprintf(stdout, "\nYou have some past-due tasks! If you'd like to remove them, run option G.\n\n");
	}
}

void printMenu() {
	fprintf(stdout, 
		"Please select an option:\n"
		"A - Add a new task\n"
		"B - Remove a task\n"
		"C - Update a task\n"
		"D - Display all tasks\n"
		"E - Display a set of tasks\n"
		"F - Display next due task\n"
		"G - Remove past-due tasks\n"
		"H - Quit School Task Manager\n"
		"\nYour Selection:"
	);
}