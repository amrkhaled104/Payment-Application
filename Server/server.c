#include "server.h"
#include<stdio.h>
#include<string.h>
#include"../Handling/handling.h"
extern ST_accountsDB_t *HeadaccountDB;
extern ST_transaction_t *Headtransaction;
ST_accountsDB_t *current;
#define Maxamount 3000
ST_accountsDB_t *HElpaccountDB;
ST_transaction_t *HELPtransaction;

void initialize() {
    HElpaccountDB = HeadaccountDB;
    HELPtransaction = Headtransaction;
}

// Function to receive transaction data and process it
EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
	print_old_list();
    // Get and validate card data
    while (getCardHolderName(&(transData->cardHolderData)) == WRONG_NAME);
    while (getCardExpiryDate(&(transData->cardHolderData)) == WRONG_EXP_DATE);
    while (getCardPAN(&(transData->cardHolderData)) == WRONG_PAN);

    // Set maximum amount and get transaction date
    while (setMaxAmount(&(transData->terminalData), Maxamount) == INVALID_MAX_AMOUNT);
    getTransactionDate(&(transData->terminalData));

    // Check account validity
    if (isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND) {
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }

    // Check if the account is blocked
    if (isBlockedAccount(current) == BLOCKED_ACCOUNT) {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }

    // Check if the card is expired
    if (isCardExpired(&transData->cardHolderData, &transData->terminalData) == EXPIRED_CARD) {
        transData->transState = DECLINED_EXPIRED_CARD;
        return DECLINED_EXPIRED_CARD;
    }
	printf("hi");

    // Get and validate transaction amount
    while (getTransactionAmount(&(transData->terminalData)) == INVALID_AMOUNT);
    if (isBelowMaxAmount(&(transData->terminalData)) == EXCEED_MAX_AMOUNT) {
        transData->transState = DECLINED_EXCEEDING_AMOUNT;
        return DECLINED_EXCEEDING_AMOUNT;
    }
    if (isAmountAvailable(transData) == LOW_BALANCE) {
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        return DECLINED_INSUFFICIENT_FUND;
    }

    transData->transState = APPROVED;
    return APPROVED;
}

// Function to check if the account is valid
EN_serverError_t isValidAccount(ST_cardData_t *cardData) {
     current = HeadaccountDB;
    while (current != NULL) {
        if (strcmp((char *)cardData->primaryAccountNumber, (char *)current->primaryAccountNumber) == 0) {
            //*accountRefrence = *current;
            return SERVER_OK;
        }
        current = current->NEXT;
    }
    return ACCOUNT_NOT_FOUND;
}

// Function to check if the transaction amount is available
EN_serverError_t isAmountAvailable(ST_transaction_t *transData) {
    ST_accountsDB_t *current = HeadaccountDB;
    while (current != NULL) {
        if (strcmp((char *)transData->cardHolderData.primaryAccountNumber, (char *)current->primaryAccountNumber) == 0) {
            if (transData->terminalData.transAmount <= current->balance) {
                return SERVER_OK;
            } else {
                return LOW_BALANCE;
            }
        }
        current = current->NEXT;
    }
    return ACCOUNT_NOT_FOUND;
}

// Function to check if the account is blocked
EN_serverError_t isBlockedAccount(ST_accountsDB_t *current) {
    return (current->state == BLOCKED) ? BLOCKED_ACCOUNT : SERVER_OK;
}
static void displayTransactionDetails()
{
    printf("------------------------------------------------------------\n");
    printf("Card Holder's Name: %s\n", HELPtransaction->cardHolderData.cardHolderName);
    printf("Card PAN: %s\n", HELPtransaction->cardHolderData.primaryAccountNumber);
    printf("Card Expiry Date: %s\n", HELPtransaction->cardHolderData.cardExpirationDate);
    printf("------------------------------------------------------------\n");
    printf("Transaction Date: %s\n", HELPtransaction->terminalData.transactionDate);
    printf("Transaction Maximum Amount: %.2f\n", HELPtransaction->terminalData.maxTransAmount);
    printf("Transaction Amount: %.2f\n", HELPtransaction->terminalData.transAmount);
    printf("------------------------------------------------------------\n");
    printf("Transaction Sequence Number: %d\n", HELPtransaction->transactionSequenceNumber);
    printf("------------------------------------------------------------\n");
}
// Function to update account balance and transaction details
EN_serverError_t saveTransaction(ST_transaction_t *transData) {
    ST_accountsDB_t *current = HElpaccountDB;
    while (current != NULL) {
        if (strcmp(transData->cardHolderData.primaryAccountNumber, current->primaryAccountNumber) == 0) {
            current->balance -= transData->terminalData.transAmount;
            break;
        }
        current = current->NEXT;
    }
	 while (HELPtransaction != NULL) {
        if (strcmp(transData->cardHolderData.primaryAccountNumber, HELPtransaction->cardHolderData.primaryAccountNumber) == 0) {
                HELPtransaction->terminalData.transAmount = transData->terminalData.transAmount;
                HELPtransaction->transState = transData->transState;
                strcpy(HELPtransaction->cardHolderData.cardExpirationDate , transData->cardHolderData.cardExpirationDate);
                getTransactionDate(&HELPtransaction->terminalData);
                HELPtransaction->transactionSequenceNumber=HELPtransaction->transactionSequenceNumber++;
                break;
        }
        HELPtransaction = HELPtransaction->NEXT;
    }

	displayTransactionDetails();
	listSavedTransactions();
	return SERVER_OK;
}
void listSavedTransactions(){
	 print_old_list();
}
// Function to report a stolen card
void reportStolenCard() {
    char pan[20];
    printf("Enter the PAN of the stolen card: ");
    scanf("%s", pan);

    ST_accountsDB_t *current = HeadaccountDB;
    while (current != NULL) {
        if (strcmp(current->primaryAccountNumber, pan) == 0) {
            current->state = BLOCKED;
            printf("The card with PAN %s has been reported as stolen and blocked.\n", pan);
            return;
        }
        current = current->NEXT;
    }

    printf("No account found with PAN %s.\n", pan);
}