#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "../Server/server.h"

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

void appStart(void)
{
    initialize();
    uint32_t userChoice = 1;
    
    printf("1. Perform a transaction\n");
    printf("2. Report a stolen card\n");
    printf("Enter your choice: ");
    scanf("%d", &userChoice);

    if (userChoice == 1)
    {
        /* Initialize the struct instance with default values */
        ST_transaction_t transaction = {{"", "", ""}, {0.0f, 0.0f, ""}, 0, 0};
        EN_transState_t transactionState = recieveTransactionData(&transaction);

        switch (transactionState)
        {
        case APPROVED:
            printf("Transaction APPROVED\n");
            displayTransactionDetails(&transaction);
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
        default:
            printf("Transaction ERROR: UNKNOWN STATE\n");
            break;
        }
    }
    else if (userChoice == 2)
    {
        reportStolenCard();
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
}
