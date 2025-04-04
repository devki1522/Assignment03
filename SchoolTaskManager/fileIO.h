// Group 2 - PROG71990 W25 - Group Project - School Task Manager
// Interface of the file Input/Output functions

#pragma once

#include "taskList.h"

/// Loads in tasks from file into linked list
/// 1. Open database.txt file in read mode
/// 2. Read in a line
/// 3. Parse information
/// 4. Create Task
/// 5. Add task to list
/// 6. Repeat 2-5 until end of file
/// 7. Close file
/// 8. Return list
PLISTNODE LoadTasksfromDatabase();

/// Save tasks from Linked list into a file
/// 1. Open database.txt file in write mode
/// 2. Get next node from list
/// 3. Print task from node to file
/// 4. Repeat 2-3 until end of list
/// 5. Close file
void SaveTaskstoDatabase(PLISTNODE List);