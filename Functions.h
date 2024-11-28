#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

void add_task();
void asc_sorting();
void desc_sorting();
void sort_selection();
void update_task();
void delete_task();
void view_task(char *type);
void view_rec_dlt_task_with_line_num();
void rec_dlt_task();
void exit_page();

int is_leap_year(int year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

// Helper function to validate date
int validate_date(int dd, int mm, int yyyy) {
    if (yyyy >= 1900 && yyyy <= 9999) {
        if (mm >= 1 && mm <= 12) {
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12)) return 1;
            if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) return 1;
            if ((dd >= 1 && dd <= 28) && (mm == 2)) return 1;
            if (dd == 29 && mm == 2 && (yyyy % 400 == 0 || (yyyy % 4 == 0 && yyyy % 100 != 0))) return 1;
        }
    }
    return 0;
}

struct addtask {
    char taskname[100];
    char duedate[11];
    char cat[25];
    char status[25];
    char record[400];
    char num[100];
    int current_line;
    int dd;
    int mm;
    int yyyy;
};

void add_task() {
    struct addtask task;
    time_t t;
    int i = 1, j = 1, choice, line_number = 1;

    time(&t);
    printf("\nToday's Date: %s\n", ctime(&t));

    // Open task.txt in read and append mode
    FILE *f = fopen("task.txt", "a+");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }

    // Determine the next line number by reading the file
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        line_number++;
    }

    // Prompt for Task Name
    printf("Enter Task Name: ");
    getchar(); // Consume leftover newline from previous input
    if (fgets(task.taskname, sizeof(task.taskname), stdin) != NULL) {
        strtok(task.taskname, "\n"); // Remove trailing newline
    } else {
        printf("Error reading task name.\n");
        fclose(f);
        return;
    }

    // Prompt for Due Date
    while (i) {
        printf("\nEnter Due Date [DD/MM/YYYY]: ");
        int dd, mm, yyyy;
        if (scanf("%d/%d/%d", &dd, &mm, &yyyy) != 3) {
            printf("Invalid date format! Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (validate_date(dd, mm, yyyy)) {
            sprintf(task.duedate, "%02d/%02d/%04d", dd, mm, yyyy);
            i = 0; // Exit loop when date is valid
        } else {
            printf("Invalid date! Please try again.\n");
        }
    }

    // Prompt for Category
    while (j) {
        printf("\n===== Category =====\n");
        printf("(1) Assignment\n(2) Revision\n(3) Homework\n(4) Others\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                strcpy(task.cat, "Assignment");
                j = 0;
                break;
            case 2:
                strcpy(task.cat, "Revision");
                j = 0;
                break;
            case 3:
                strcpy(task.cat, "Homework");
                j = 0;
                break;
            case 4:
                printf("Please enter a category: ");
                getchar(); // Clear buffer
                if (fgets(task.cat, sizeof(task.cat), stdin) != NULL) {
                    strtok(task.cat, "\n"); // Remove trailing newline
                    j = 0;
                } else {
                    printf("Error reading category.\n");
                }
                break;
            default:
                printf("Invalid option! Try again.\n");
        }
    }

    // Set Default Status
    strcpy(task.status, "Incomplete");

    // Write the task to the file with line number
    if (fprintf(f, "%d;%s;%s;%s;%s\n", line_number, task.taskname, task.duedate, task.cat, task.status) < 0) {
        perror("Error writing to file");
    } else {
        printf("\nTask added successfully! Line Number: %d\n", line_number);
    }

    // Close the file
    if (fclose(f) != 0) {
        perror("Error closing file");
    }
}


void asc_sorting() {
    struct addtask task[100], tmp;
    int i = 0, j, count_lines = 0;
    char record[100];

    // Open files
    FILE *ft = fopen("task.txt", "r");
    FILE *fw = fopen("asc_task.txt", "w");
    if (!ft || !fw) {
        perror("Error opening file");
        if (ft) fclose(ft);
        if (fw) fclose(fw);
        return;
    }

    // Read tasks from task.txt and count lines
    while (fgets(record, sizeof(record), ft)) {
        sscanf(record, "%d;%[^;];%02d/%02d/%d;%[^;];%s\n", 
               &task[i].current_line, task[i].taskname, 
               &task[i].dd, &task[i].mm, &task[i].yyyy, 
               task[i].cat, task[i].status);
        i++;
    }
    count_lines = i;

    // Sort tasks by date in ascending order
    for (i = 0; i < count_lines - 1; i++) {
        for (j = i + 1; j < count_lines; j++) {
            if (task[i].yyyy > task[j].yyyy || 
               (task[i].yyyy == task[j].yyyy && task[i].mm > task[j].mm) || 
               (task[i].yyyy == task[j].yyyy && task[i].mm == task[j].mm && task[i].dd > task[j].dd)) {
                tmp = task[i];
                task[i] = task[j];
                task[j] = tmp;
            }
        }
    }

    // Write sorted tasks to asc_task.txt with updated line numbers
    for (i = 0; i < count_lines; i++) {
        fprintf(fw, "%d;%s;%02d/%02d/%04d;%s;%s\n", 
                i + 1, // New line number based on the sorted order
                task[i].taskname, task[i].dd, task[i].mm, task[i].yyyy, 
                task[i].cat, task[i].status);
    }

    // Close files
    fclose(ft);
    fclose(fw);

    // Display sorted tasks
    printf("\nTasks sorted in ascending order by date have been written to 'asc_task.txt' with updated line numbers.\n");
    char type[] = "asc";
    view_task(type); // Assuming view_task can read and display asc_task.txt
}


void desc_sorting() {
    struct addtask task[100], tmp;
    int i = 0, j, count_lines = 0;
    char record[100];

    // Open files
    FILE *ft = fopen("task.txt", "r");
    FILE *fw = fopen("desc_task.txt", "w");
    if (!ft || !fw) {
        perror("Error opening file");
        if (ft) fclose(ft);
        if (fw) fclose(fw);
        return;
    }

    // Read tasks from task.txt and count lines
    while (fgets(record, sizeof(record), ft)) {
        sscanf(record, "%d;%[^;];%02d/%02d/%d;%[^;];%s\n", 
               &task[i].current_line, task[i].taskname, 
               &task[i].dd, &task[i].mm, &task[i].yyyy, 
               task[i].cat, task[i].status);
        i++;
    }
    count_lines = i;

    // Sort tasks by date in descending order
    for (i = 0; i < count_lines - 1; i++) {
        for (j = i + 1; j < count_lines; j++) {
            if (task[i].yyyy < task[j].yyyy || 
               (task[i].yyyy == task[j].yyyy && task[i].mm < task[j].mm) || 
               (task[i].yyyy == task[j].yyyy && task[i].mm == task[j].mm && task[i].dd < task[j].dd)) {
                tmp = task[i];
                task[i] = task[j];
                task[j] = tmp;
            }
        }
    }

    // Write sorted tasks to desc_task.txt with updated line numbers
    for (i = 0; i < count_lines; i++) {
        fprintf(fw, "%d;%s;%02d/%02d/%04d;%s;%s\n", 
                i + 1, // New line number based on the sorted order
                task[i].taskname, task[i].dd, task[i].mm, task[i].yyyy, 
                task[i].cat, task[i].status);
    }

    // Close files
    fclose(ft);
    fclose(fw);

    // Display sorted tasks
    printf("\nTasks sorted in descending order by date have been written to 'desc_task.txt' with updated line numbers.\n");
    char type[] = "desc";
    view_task(type); // Assuming view_task can read and display desc_task.txt
}

void sort_selection() {
    int option;
    int valid = 0; // Flag to track valid input
    while (!valid) {
        printf("\nSort Date in: \n"
               "(1) Ascending\n"
               "(2) Descending\n"
               "Enter an option: ");
        
        if (scanf("%d", &option) != 1) {  // Check if input is an integer
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;  // Retry
        }

        switch (option) {
            case 1:
                asc_sorting();
                printf("\nTasks sorted in ascending order.\n");
                valid = 1; // Exit loop
                break;
            case 2:
                desc_sorting();
                printf("\nTasks sorted in descending order.\n");
                valid = 1; // Exit loop
                break;
            default:
                printf("Error! Please enter 1 or 2.\n");
                break;
        }
    }
}

void update_task() {
    struct addtask task;
    int recordnum, columnupdate, choice, stat;
    int record_found = 0;

    FILE *task_f = fopen("task.txt", "r");
    FILE *temp_task = fopen("temp_task.txt", "w");

    // Validate file opening
    if (!task_f || !temp_task) {
        printf("Error opening file. Please ensure the file exists.\n");
        if (task_f) fclose(task_f);
        if (temp_task) fclose(temp_task);
        return;
    }

    // Display tasks
    char type[] = "view";
    view_task(type);

    printf("Enter Record No. to update: ");
    scanf("%d", &recordnum);

    // Read and process tasks from task.txt
    while (fgets(task.record, sizeof(task.record), task_f)) {
        sscanf(task.record, "%d;%[^;];%[^;];%[^;];%s", 
               &task.current_line, task.taskname, 
               task.duedate, task.cat, task.status);

        if (recordnum == task.current_line) {
            record_found = 1;

            printf("\nCurrent Task Details:\n");
            printf("Taskname: %s\nDue Date: %s\nCategory: %s\nStatus: %s\n", 
                   task.taskname, task.duedate, task.cat, task.status);

            printf("\nColumns available for update:\n");
            printf("(1) Taskname\n");
            printf("(2) Due Date\n");
            printf("(3) Category\n");
            printf("(4) Status\n");
            printf("Enter the column number to update: ");
            scanf("%d", &columnupdate);

            switch (columnupdate) {
                case 1: // Update Taskname
                    printf("Enter New Taskname: ");
                    getchar(); // Clear buffer
                    fgets(task.taskname, sizeof(task.taskname), stdin);
                    strtok(task.taskname, "\n"); // Remove newline
                    break;

                case 2: // Update Due Date
                    printf("Enter New Due Date (DD/MM/YYYY): ");
                    scanf("%s", task.duedate);
                    break;

                case 3: { // Update Category
                    int j = 1;
                    while (j != 0) {
                        printf("\n===== Category =====\n");
                        printf("(1) Assignment\n");
                        printf("(2) Reminder\n");
                        printf("(3) Revision\n");
                        printf("(4) Others\n");
                        printf("Enter option above: ");
                        getchar();
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                strcpy(task.cat, "Assignment");
                                j = 0;
                                break;
                            case 2:
                                strcpy(task.cat, "Reminder");
                                j = 0;
                                break;
                            case 3:
                                strcpy(task.cat, "Revision");
                                j = 0;
                                break;    
                            case 4:
                                printf("Please enter a category: ");
                                getchar();
                                fgets(task.cat, sizeof(task.cat), stdin);
                                strtok(task.cat, "\n"); // Remove newline
                                j = 0;
                                break;                        
                            default:
                                printf("Error! Please enter the above number!!\n");
                                j = 1;
                                break;
                        }
                    }
                    break;
                }

                case 4: { // Update Status
                    int k = 1;
                    while (k != 0) {
                        printf("\n===== Status =====\n");
                        printf("(1) Pending\n");
                        printf("(2) Complete\n");
                        printf("Enter option above: ");
                        scanf("%d", &stat);

                        switch (stat) {
                            case 1:
                                strcpy(task.status, "Pending");
                                k = 0;
                                break;                            
                            case 2:
                                strcpy(task.status, "Complete");
                                k = 0;
                                break;                        
                            default:
                                printf("Error! Please enter the above number!!\n");
                                k = 1;
                                break;
                        }
                    }
                    break;
                }

                default:
                    printf("Error! Please enter the above number!!\n");
                    break;
            }

            printf("\nUpdated Task Details:\n");
            printf("Taskname: %s\nDue Date: %s\nCategory: %s\nStatus: %s\n", 
                   task.taskname, task.duedate, task.cat, task.status);
        }

        // Write the (possibly updated) record to the temp file
        fprintf(temp_task, "%d;%s;%s;%s;%s\n", task.current_line, task.taskname, task.duedate, task.cat, task.status);
    }

    fclose(task_f);
    fclose(temp_task);

    if (record_found) {
        // Replace the original file with the updated temp file
        remove("task.txt");
        rename("temp_task.txt", "task.txt");

        printf("Task updated successfully.\n");
    } else {
        printf("Record not found.\n");
        remove("temp_task.txt");
    }

    // Display the updated task list
    view_task(type);
}

// Function to delete a task based on record number
void delete_task() {
    struct addtask task;
    int recordnum;

    char type[] = "view";
    view_task(type);

    FILE *f = fopen("task.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *dlt_task = fopen("dlt_task.txt", "a");

    if (!f || !temp || !dlt_task) {
        printf("Error opening files.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        if (dlt_task) fclose(dlt_task);
        return;
    }

    printf("Enter Record No. to delete: ");
    scanf("%d", &recordnum);

    int current_line = 1;  // Track the line number in task.txt
    int found = 0;

    while (fgets(task.record, sizeof(task.record), f)) {
        sscanf(task.record, "%d;%[^;];%[^;];%[^;];%s", &task.current_line, task.taskname, task.duedate, task.cat, task.status);

        // If the task is the one to delete
        if (recordnum == task.current_line) {
            printf("\nDelete -> Record No.: %d\nTaskname: %s\nDue Date: %s\nCategory: %s\nStatus: %s\n",
                   task.current_line, task.taskname, task.duedate, task.cat, task.status);

            // Write the task to dlt_task.txt with the current line number
            fprintf(dlt_task, "%d;%s;%s;%s;%s\n", current_line, task.taskname, task.duedate, task.cat, task.status);
            found = 1;
        } else {
            // Write the task to temp.txt with updated line numbers
            fprintf(temp, "%d;%s;%s;%s;%s\n", current_line, task.taskname, task.duedate, task.cat, task.status);
        }

        // Increment the line number for the next task
        current_line++;
    }

    fclose(f);
    fclose(temp);
    fclose(dlt_task);

    if (found) {
        // Replace the old task.txt with the updated temp.txt
        remove("task.txt");
        rename("temp.txt", "task.txt");
        printf("Task deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("No task found with the given record number.\n");
    }
}


void view_task(char *type) {
    struct addtask tk = {0};  // Initialize structure to zero
    int j, k, times = 136;
    FILE *file;
    char buffer[MAX_LINE];
    char *type1 = "asc";
    char *type2 = "desc";
    char *type3 = "view";
    char *filename;

    // Determine which file to read based on the type
    if (strcmp(type, type1) == 0) {
        filename = "asc_task.txt";
    } else if (strcmp(type, type2) == 0) {
        filename = "desc_task.txt";
    } else if (strcmp(type, type3) == 0) {
        filename = "task.txt";
    } else {
        printf("Invalid type provided.\n");
        return;
    }

    // Open the corresponding file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // Print table headers
    for (j = 0; j < times; ++j) {
        printf("=");
    }
    printf("\n    Record No.    |\t\t     Taskname     \t\t|\tDue Date\t|\tCategory\t|\t Status \t\n");
    for (k = 0; k < times; ++k) {
        printf("=");
    }
    printf("\n");

    // Read and display each task
    while (fgets(buffer, MAX_LINE, file) != NULL) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%s", 
               &tk.current_line, tk.taskname, tk.duedate, tk.cat, tk.status);
        printf("\t%d \t  |\t   %26s   \t|\t%s\t|%17s\t|%17s\n", 
               tk.current_line, tk.taskname, tk.duedate, tk.cat, tk.status);
    }

    fclose(file);
}

void view_rec_dlt_task_with_line_num() {
    struct addtask task;
    int times = 136;
    int j, k;

    FILE *f = fopen("dlt_task.txt", "r");
    if (!f) {
        printf("Error opening dlt_task.txt file.\n");
        return;
    }

    printf("\nThese are the deleted records\n");
    for (j = 0; j < times; ++j) {
        printf("=");
    }
    printf("\n    Record No.    |\t\t     Taskname     \t\t|\tDue Date\t|\tCategory\t|\t Status \t\n");
    for (k = 0; k < times; ++k) {
        printf("=");
    }
    printf("\n");

    while (fgets(task.record, sizeof(task.record), f)) {
        sscanf(task.record, "%d;%[^;];%[^;];%[^;];%s", &task.current_line, task.taskname, task.duedate, task.cat, task.status);
        printf("\t%d \t  |\t   %26s   \t|\t%s\t|%17s\t|%17s\n",
               task.current_line, task.taskname, task.duedate, task.cat, task.status);
    }

    fclose(f);
}


// Function to recover deleted tasks
void rec_dlt_task() {
    struct addtask task;
    int recordnum;

    view_rec_dlt_task_with_line_num();  // Display deleted tasks with line numbers

    FILE *f = fopen("dlt_task.txt", "r");
    FILE *temp_dlt = fopen("temp_dlt.txt", "w");
    FILE *rec_task = fopen("task.txt", "a+");

    if (!f || !temp_dlt || !rec_task) {
        printf("Error opening files.\n");
        if (f) fclose(f);
        if (temp_dlt) fclose(temp_dlt);
        if (rec_task) fclose(rec_task);
        return;
    }

    printf("Enter Record No. to recover: ");
    scanf("%d", &recordnum);

    int found = 0;
    while (fgets(task.record, sizeof(task.record), f)) {
        sscanf(task.record, "%d;%[^;];%[^;];%[^;];%s", &task.current_line, task.taskname, task.duedate, task.cat, task.status);

        if (recordnum == task.current_line) {
            printf("\nTask recovered -> Record No.: %d\nTaskname: %s\nDue Date: %s\nCategory: %s\nStatus: %s\n",
                   task.current_line, task.taskname, task.duedate, task.cat, task.status);

            // Temporarily add the task to task.txt with a dummy line number
            fprintf(rec_task, "0;%s;%s;%s;%s\n", task.taskname, task.duedate, task.cat, task.status);
            found = 1;
        } else {
            // Write remaining tasks to temp_dlt.txt
            fprintf(temp_dlt, "%d;%s;%s;%s;%s\n", task.current_line, task.taskname, task.duedate, task.cat, task.status);
        }
    }

    fclose(f);
    fclose(temp_dlt);
    fclose(rec_task);

    if (!found) {
        remove("temp_dlt.txt");
        printf("No task found with the given record number.\n");
        return;
    }

    // Rename temp_dlt.txt to dlt_task.txt
    remove("dlt_task.txt");
    rename("temp_dlt.txt", "dlt_task.txt");

    // Renumber task.txt
    FILE *task_file = fopen("task.txt", "r");
    FILE *temp_task = fopen("temp_task.txt", "w");
    if (!task_file || !temp_task) {
        printf("Error renumbering tasks.\n");
        if (task_file) fclose(task_file);
        if (temp_task) fclose(temp_task);
        return;
    }

    int current_line = 1;
    while (fgets(task.record, sizeof(task.record), task_file)) {
        sscanf(task.record, "%d;%[^;];%[^;];%[^;];%s", &task.current_line, task.taskname, task.duedate, task.cat, task.status);

        // Assign new line number and write to temp_task.txt
        fprintf(temp_task, "%d;%s;%s;%s;%s\n", current_line, task.taskname, task.duedate, task.cat, task.status);
        current_line++;
    }

    fclose(task_file);
    fclose(temp_task);

    // Replace the original task.txt with the renumbered version
    remove("task.txt");
    rename("temp_task.txt", "task.txt");

    printf("Task recovered successfully, and line numbers updated.\n");
}

void exit_page() {
    printf("\nExiting...\nThank you for using system\n");        
}