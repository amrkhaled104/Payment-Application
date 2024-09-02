#include <stdio.h>
#include <stdbool.h>
#include "app/app.h"
#include "Handling/handling.h"

int main()
{
    load_data();
    bool continueTransaction = true;
    char userChoice;

    while (continueTransaction)
    {
        appStart();

        do {
            printf("\nAnother Transaction? (y/n): ");
            fflush(stdin);
            scanf(" %c", &userChoice);
            if (userChoice == 'y' || userChoice == 'Y') {
                continueTransaction = true;
                break;
            } else if (userChoice == 'n' || userChoice == 'N') {
                continueTransaction = false;
                break;
            } else {
                printf("Invalid input. Please enter 'y' or 'n'.\n");
            }
        } while (true);
    }

    save_data();
    clear_lists();
    printf("Thank you!\n");
    return 0;
}
