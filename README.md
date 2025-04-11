# School Task Manager - Division Of Labour

Planning - All ideas, code flow, and interface planning done together

### Main - Spencer
- printMOTD()
- printMenu()
- main()

### TaskList Component - Devki
- AddListNode()
- RemoveListNode()
- DeleteList()
- PrintAllList()
- PrintByCourseCode()
- PrintUpcomingTask()
- SearchLinkedList()
- FindListNode()

### Task Component - Tanveer
Create
- CreateTask()

Read
- PrintTaskHeader()
- PrintTask()

Getters
- GetTaskName()
- GetTaskCourseCode()
- GetTaskWeight()
- GetTaskDueDate()

Setters
- SetTaskName()
- SetTaskCourseCode()
- SetTaskWeight()
- SetTaskDueDate()

User Input
- GetTaskNameFromUser()
- GetCourseCodeFromUser()
- GetWeightFromUser()

Validators
- IsTaskNameValid()
- IsCourseCodeValid()
- IsWeightValid()

### Date Component - Spencer
- CreateDate()
- GetCurrentDate()
- IsDate1SoonerThanDate2()
- GetDateFromUser()
- IsDayValid()
- IsMonthValid()
- IsYearValid()
- IsDateValid()

### FileIO Component - Devki
- LoadTasksfromDatabase()
- SaveTaskstoDatabase()

### IOutils Component - Spencer
- ClearStdin()
- GetChar()