#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"
// Function to get user choice from input
static UserChoice getUserChoice(const char* input) {
    if (strcmp(input, "1") == 0) {
        return TRANSACTION;
    } else if (strcmp(input, "2") == 0) {
        return SHOW_LAST_TRANSACTION;
    } else if (strcmp(input, "3") == 0) {
        return SHOW_TRANSACTION_HISTORY;
    } else if (strcmp(input, "4") == 0) {
        return REPORT_STOLEN_CARD;
    } else {
        return INVALID_CHOICE;
    }
}

void appStart(void) {
    initialize();
    char input[10];
    UserChoice userChoice;

    while (1) {
        printf("1. Perform a transaction\n");
        printf("2. Show information about last transaction\n");
        printf("3. Show transaction history\n");
        printf("4. Report a stolen card\n");
        printf("Enter your choice: ");
		fflush(stdin);
        fgets(input, sizeof(input), stdin);
        clearScreen();
        // Remove trailing newline character if it exists
        input[strcspn(input, "\n")] = '\0';
        userChoice = getUserChoice(input);
        // Handle the user choice
        switch (userChoice) {
            case TRANSACTION:
                printf("You chose to perform a transaction.\n");
                // Handle the transaction process
                {
                    ST_transaction_t transaction;
                    EN_transState_t transactionState = recieveTransactionData(&transaction);
                    switch (transactionState) {
                        case APPROVED:
                            printf("Transaction APPROVED\n");
                            break;
                        case DECLINED_EXPIRED_CARD:
                            printf("Transaction DECLINED: EXPIRED CARD\n");
                            break;
                        case DECLINED_EXCEEDING_AMOUNT:
                            printf("Transaction DECLINED: EXCEEDING THE LIMIT (3000.00 Pound)\n");
                            break;
                        case DECLINED_INSUFFICIENT_FUND:
                            printf("Transaction DECLINED: INSUFFICIENT FUND\n");
                            break;
                        case DECLINED_STOLEN_CARD:
                            printf("Transaction DECLINED: STOLEN CARD\n");
                            break;
                        case INTERNAL_SERVER_ERROR:
                            printf("Transaction ERROR: INTERNAL SERVER ERROR\n");
                            break;
                        case FRAUD_CARD:
                            printf("Transaction ERROR: FRAUD CARD ERROR\n");
                            break;
                        default:
                            printf("Transaction ERROR: UNKNOWN STATE\n");
                            break;
                    }
                    saveTransaction(&transaction);
                }
                break;

            case SHOW_LAST_TRANSACTION:
                printf("You chose to show the last transaction.\n");
                showLastTransaction();
                break;

            case SHOW_TRANSACTION_HISTORY:
                printf("You chose to show the transaction history.\n");
                showTransactionHistory();
                break;

            case REPORT_STOLEN_CARD:
                printf("You chose to report a stolen card.\n");
                reportStolenCard();
                break;

            case INVALID_CHOICE:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                continue;
        }

        // Exit loop after a valid choice
        break;
    }
}
