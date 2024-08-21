 **********************************************************************************
 * @file           : main.c >> Linked-Based Implementation
 * @author         : Amr Khaled
 * @brief          : main.c that consists test for the implementation level 
 * @date           : 22/6/2024
 **********************************************************************************
**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "stack.h"

void Display(struct Data pe) {
    printf("Name: %s\nAge: %d\n", pe.Name, pe.age);
}

int main() {
    struct Data e;
    Stack s;
    CreateStack(&s);

    do {
        printf("\n-----------------------------------------------\n");
        printf("1. Clear the stack.\n");
        printf("2. Read an element then Push it.\n");
        printf("3. Pop an element then display it.\n");
        printf("4. What is the stack size?\n");
        printf("5. Display the Stack Top.\n");
        printf("6. Print all elements in the stack.\n");
        printf("7. Exit.\n");
        printf("-----------------------------------------------\n");

        int choose;
        printf("\nEnter Your Order: ");
        scanf("%d", &choose);

        switch (choose) {
            case 1:
                ClearStack(&s);
                break;

            case 2:
                if (!StackFull(&s)) {
                    printf("Enter the Name: ");
                    scanf("%s", e.Name);
                    char term;
                    while (1) {
                        printf("Enter the Age: ");
                        if (scanf("%d%c", &e.age, &term) != 2 || term != '\n') {
                            printf("Invalid input, please enter a number.\n");
                            while (getchar() != '\n'); // Clear the input buffer
                        } else {
                            break; // Valid input
                        }
                    }
                    Push(e, &s);
                } else {
                    printf("The Stack is Full !!\n");
                }
                break;

            case 3:
                if (!StackEmpty(&s)) {
                    Pop(&e, &s);
                    printf("The popped element Data\n\nName: %s\nAge: %d\n", e.Name, e.age);
                } else {
                    printf("The Stack is Empty !!\n");
                }
                break;

            case 4:
                printf("Stack Size = %d\n", StackSize(&s));
                break;

            case 5:
                if (!StackEmpty(&s)) {
                    StackTop(&e, &s);
                    printf("The TOP element Data\n\nName: %s\nAge: %d\n", e.Name, e.age);
                } else {
                    printf("The Stack is Empty !!\n");
                }
                break;

            case 6:
                TraverseStack(&s, &Display);
                break;

            case 7:
                exit(0);
                break;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }

        printf("\nEnter y to continue.... \n");
    } while (getch() == 'y');

    return 0;
}