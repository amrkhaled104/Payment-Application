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
        printf("\nAnother Transaction? (y/n): ");
        scanf(" %c", &userChoice);

        if (userChoice == 'n' || userChoice == 'N')
        {
            continueTransaction = false;
        }
    }

    save_data();
    clear_lists();
    printf("Thank you!\n");
    return 0;
}
