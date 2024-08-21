#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Display function to print an element
void Display(ListEntry e) {
    printf("Name: %s\nAge: %d\n", e.Name, e.age);
}

int main() {
    List myList;
    CreateList(&myList);
    ListEntry e;

    int choice, pos;

    do {
        printf("\n-----------------------------------------------\n");
        printf("1. Clear the list.\n");
        printf("2. Insert an element.\n");
        printf("3. Delete an element.\n");
        printf("4. What is the list size?\n");
        printf("5. Retrieve an element.\n");
        printf("6. Replace an element.\n");
        printf("7. Print all elements in the list.\n");
        printf("8. Reverse the list.\n");
        printf("9. Get the middle node.\n");
        printf("10. Get the sum of all ages.\n");
        printf("11. Get the maximum age.\n");
        printf("12. Exit.\n");
        printf("-----------------------------------------------\n");

        printf("Enter Your Order: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                DestroyList(&myList);
                printf("List cleared.\n");
                break;

            case 2:
                if (!ListFull(&myList)) {
                    printf("Enter the position to insert: ");
                    scanf("%d", &pos);
                    printf("Enter the Name: ");
                    scanf("%s", e.Name);
                    printf("Enter the Age: ");
                    scanf("%d", &e.age);
                    if (InsertList(pos, e, &myList)) {
                        printf("Element inserted.\n");
                    } else {
                        printf("This position doesn't exist.\n");
                    }
                } else {
                    printf("The list is full!\n");
                }
                break;

            case 3:
                if (!ListEmpty(&myList)) {
                    printf("Enter the position to delete: ");
                    scanf("%d", &pos);
                    if (DeleteList(pos, &e, &myList)) {
                        printf("Deleted element: Name: %s, Age: %d\n", e.Name, e.age);
                    } else {
                        printf("Failed to delete element.\n");
                    }
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 4:
                printf("List Size = %d\n", ListSize(&myList));
                break;

            case 5:
                if (!ListEmpty(&myList)) {
                    printf("Enter the position to retrieve: ");
                    scanf("%d", &pos);
                    RetrieveList(pos, &e, &myList);
                    printf("Retrieved element: Name: %s, Age: %d\n", e.Name, e.age);
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 6:
                if (!ListEmpty(&myList)) {
                    printf("Enter the position to replace: ");
                    scanf("%d", &pos);
                    printf("Enter the new Name: ");
                    scanf("%s", e.Name);
                    printf("Enter the new Age: ");
                    scanf("%d", &e.age);
                    ReplaceList(pos, e, &myList);
                    printf("Element replaced.\n");
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 7:
                if (!ListEmpty(&myList)) {
                    TraverseList(&myList, &Display);
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 8:
                if (!ListEmpty(&myList)) {
                    ReverseList(&myList);
                    printf("List reversed.\n");
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 9:
                if (!ListEmpty(&myList)) {
                    MiddleNode(&e, &myList);
                    printf("Middle node: Name: %s, Age: %d\n", e.Name, e.age);
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 10:
                if (!ListEmpty(&myList)) {
                    int sum = SumList(&myList);
                    printf("Sum of all ages: %d\n", sum);
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 11:
                if (!ListEmpty(&myList)) {
                    int max = MaxList(&myList);
                    printf("Maximum age: %d\n", max);
                } else {
                    printf("The list is empty!\n");
                }
                break;

            case 12:
                DestroyList(&myList);
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
