# Personal Task Management

## Overview
A **Personal Task Management System** designed to help users efficiently manage and monitor their tasks. This system allows users to stay organized, productive, and track their progress effectively.

## Features
### Core Functionalities
### 1. Add New Tasks
- Users can add tasks by specifying the task name, due date, category, and status.

### 2. View All Tasks
- Tasks can be sorted and viewed in ascending or descending order based on attributes like due date or category.

### 3. Update Task Records
- Modify existing task details, including task name, category, due date, and status.

### 4. Delete Task Records
- Remove unwanted or erroneous tasks permanently from the system.

### 5. Recover Deleted Tasks
- Retrieve previously deleted tasks from a backup file.

### 6. Exit Program
- Safely exit the application with an option to continue or quit.

## Requirements
To compile and run this program, ensure you have the following:
1. Visual Studio Enterprise 2022 or any IDE supporting ANSI C.
2. Desktop Development with C++ workload installed in Visual Studio.

## Usage Instructions
### Run the Program
1. Clone this repository to your local system
2. Open the project in Visual Studio Code.
3. Run the Code using `Ctrl + Shift + N` to start the Personal Task Management System.
4. Click PersonalTaskManagement.exe to use the Personal Task Management System.

## Implementation Details
### Programming Approach
- Modular Programming: Code is separated into multiple files (PersonalTaskManagement.c, Functions.h) for better organization.
- File Handling: Task data is stored in text files, ensuring persistence across sessions.
- Validation: Input validation is implemented to minimize errors.
- Sorting and Searching: Users can sort tasks for better viewing and find specific tasks easily.

### Code Highlights
The program includes these key functions:
- `add_task()`: Add a new task
- `sort_selection()`: Sort and view tasks.
- `update_task()`: Update task information.
- `delete_task()`: Delete unwanted tasks.
- `rec_dlt_task()`: Recover deleted tasks.
- `exit_page()`: Manage the exit process.

## License
This project is released under the MIT License.
