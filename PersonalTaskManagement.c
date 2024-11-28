#include <stdio.h>
#include "Functions.h"

void add_task();
void sort_selection();
void update_task();
void delete_task();
void rec_dlt_task();
void exit_page();

int main()
{
    int option, result;
    int i = 1;
    char input[100];
    char ans[] = "c";

    while (i != 0) {
        printf("\n========== Welcome to Personal Task Management ==========\n");
        printf("(1) Add New Tasks\n"
               "(2) View All Tasks\n"
               "(3) Update Task\n"
               "(4) Delete Task Record\n"
               "(5) Recover Deleted Task\n"
               "(6) Exit Program\n\n");
        printf("Enter option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input from the buffer
            continue;
        }
        
        switch (option) {
            case 1:
                add_task();
                break;
            case 2:
                sort_selection();
                break;
            case 3:
                update_task();
                break;
            case 4:
                delete_task();
                break;
            case 5:
                rec_dlt_task();
                break;
            case 6:
                printf("Do you want to exit? Enter 'y' to exit or any other key to continue: ");
                scanf("%s", input);
                if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {
                    exit_page();
                    i = 0;
                }
                break;
            default:
                printf("Invalid option! Please select a number between 1 and 6.\n");
                break;
        }
    }
    return 0;
};