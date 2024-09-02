#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"

static void displayTransactionDetails(ST_transaction_t *transData)
{
    printf("------------------------------------------------------------\n");
    printf("Card Holder's Name: %s\n", transData->cardHolderData.cardHolderName);
    printf("Card PAN: %s\n", transData->cardHolderData.primaryAccountNumber);
    printf("Card Expiry Date: %s\n", transData->cardHolderData.cardExpirationDate);
    printf("------------------------------------------------------------\n");
    printf("Transaction Date: %s\n", transData->terminalData.transactionDate);
    printf("Transaction Maximum Amount: %.2f\n", transData->terminalData.maxTransAmount);
    printf("Transaction Amount: %.2f\n", transData->terminalData.transAmount);
    printf("------------------------------------------------------------\n");
    printf("Transaction Sequence Number: %d\n", transData->transactionSequenceNumber);
    printf("------------------------------------------------------------\n");
}

// Function to get user choice from input
static UserChoice getUserChoice(const char* input) {
    if (strcmp(input, "1") == 0) {
        return TRANSACTION;
    } else if (strcmp(input, "2") == 0) {
        return REPORT_STOLEN_CARD;
    } else {
        return INVALID_CHOICE;
    }
}

void appStart(void)
{
    initialize();
    char input[10];
    UserChoice userChoice;

    while (1) {
        printf("1. Perform a transaction\n");
        printf("2. Report a stolen card\n");
        printf("Enter your choice: ");
		fflush(stdin);
        fgets(input, sizeof(input), stdin);
        
        // Remove trailing newline character if it exists
        input[strcspn(input, "\n")] = '\0';

        userChoice = getUserChoice(input);

        // Handle the user choice
        switch (userChoice) {
            case TRANSACTION:
                printf("You chose to perform a transaction.\n");
                // Handle the transaction process
                {
                    ST_transaction_t transaction = {{"", "", ""}, {0.0f, 0.0f, ""}, 0, 0};
                    EN_transState_t transactionState = recieveTransactionData(&transaction);

                    switch (transactionState)
                    {
                        case APPROVED:
                            printf("Transaction APPROVED\n");
                            displayTransactionDetails(&transaction);
							saveTransaction(&transaction);
                            break;
                        case DECLINED_EXPIRED_CARD:
                            printf("Transaction DECLINED: EXPIRED CARD\n");
                            break;
                        case DECLINED_EXCEEDING_AMOUNT:
                            printf("Transaction DECLINED: EXCEEDING THE LIMIT\n");
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
                            printf("Transaction ERROR: FRAUD_CARD ERROR\n");
                            break;
                        default:
                            printf("Transaction ERROR: UNKNOWN STATE\n");
                            break;
                    }
                }
                break;
            case REPORT_STOLEN_CARD:
                printf("You chose to report a stolen card.\n");
                reportStolenCard();
                break;
            case INVALID_CHOICE:
                printf("Invalid choice. Please enter 1 or 2.\n");
                continue;
        }
        // Exit loop after a valid choice
        break;
    }
}
