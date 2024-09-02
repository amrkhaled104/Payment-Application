#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handling.h"

// Global variables for linked lists
ST_transaction_t *Headtransaction = NULL;
ST_accountsDB_t *HeadaccountDB = NULL;

// Function to convert transaction state enum to string
const char* transStateToString(EN_transState_t state) {
    switch (state) {
        case APPROVED: return "APPROVED";
        case DECLINED_INSUFFICIENT_FUND: return "DECLINED_INSUFFICIENT_FUND";
        case DECLINED_STOLEN_CARD: return "DECLINED_STOLEN_CARD";
        case FRAUD_CARD: return "FRAUD_CARD";
        case INTERNAL_SERVER_ERROR: return "INTERNAL_SERVER_ERROR";
        default: return "UNKNOWN";
    }
}

// Function to convert account state enum to string
const char* accountStateToString(EN_accountState_t state) {
    switch (state) {
        case RUNNING: return "RUNNING";
        case BLOCKED: return "BLOCKED";
        default: return "UNKNOWN";
    }
}

// Function to convert string to transaction state enum
EN_transState_t stringToTransState(const char *str){
    if (strcmp(str, "APPROVED") == 0) return APPROVED;
    if (strcmp(str, "DECLINED_INSUFFICIENT_FUND") == 0) return DECLINED_INSUFFICIENT_FUND;
    if (strcmp(str, "DECLINED_STOLEN_CARD") == 0) return DECLINED_STOLEN_CARD;
    if (strcmp(str, "FRAUD_CARD") == 0) return FRAUD_CARD;
    if (strcmp(str, "INTERNAL_SERVER_ERROR") == 0) return INTERNAL_SERVER_ERROR;
    return -1; // Or handle error as needed
}

// Function to convert string to account state enum
EN_accountState_t stringToAccountState(const char *str) {
    if (strcmp(str, "RUNNING") == 0) return RUNNING;
    if (strcmp(str, "BLOCKED") == 0) return BLOCKED;
    return -1; // Handle error case
}

// Function to save data to files
void save_data() {
    // Save transactions to old format file
    FILE *file1 = fopen("transactions.csv", "w");
    if (file1 == NULL) {
        printf("Error opening transactions file.\n");
        return;
    }

    ST_transaction_t *Helptransaction = Headtransaction;
    while (Helptransaction != NULL) {
        fprintf(file1, "%s,%s,%s,%.2f,%.2f,%s,%s,%d\n",
                Helptransaction->cardHolderData.cardHolderName,
                Helptransaction->cardHolderData.primaryAccountNumber,
                Helptransaction->cardHolderData.cardExpirationDate,
                Helptransaction->terminalData.transAmount,
                Helptransaction->terminalData.maxTransAmount,
                Helptransaction->terminalData.transactionDate,
                transStateToString(Helptransaction->transState),
                Helptransaction->transactionSequenceNumber);
        Helptransaction = Helptransaction->NEXT;
    }
    fclose(file1);

    // Save accounts to new format file
    FILE *file2 = fopen("accountDB.csv", "w");
    if (file2 == NULL) {
        printf("Error opening accountDB file.\n");
        return;
    }

    ST_accountsDB_t *HelpaccountDB = HeadaccountDB;
    while (HelpaccountDB != NULL) {
        fprintf(file2, "%.2f,%s,%s\n",
                HelpaccountDB->balance,
                HelpaccountDB->primaryAccountNumber,
                accountStateToString(HelpaccountDB->state));
        HelpaccountDB = HelpaccountDB->NEXT;
    }
    fclose(file2);
}

// Function to clear the linked lists
void clear_lists() {
    // Clear transactions list
    while (Headtransaction != NULL) {
        ST_transaction_t *ptr = Headtransaction;
        Headtransaction = Headtransaction->NEXT;
        free(ptr);
    }

    // Clear accounts list
    while (HeadaccountDB != NULL) {
        ST_accountsDB_t *ptr = HeadaccountDB;
        HeadaccountDB = HeadaccountDB->NEXT;
        free(ptr);
    }
}

// Function to load data from files
void load_data() {
    clear_lists();

    // Load transactions from file
    FILE *file1 = fopen("transactions.csv", "r");
    if (file1 == NULL) {
        perror("Error opening transactions file");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), file1)) {
        ST_transaction_t *newTransaction = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
        if (newTransaction == NULL) {
            perror("Memory allocation failed");
            fclose(file1);
            return;
        }

        char stateStr[50];  // Buffer to hold the state string

        // Parse the data from the line
        if (sscanf(line, "%[^,],%[^,],%[^,],%f,%f,%[^,],%49[^,],%d\n",
                   newTransaction->cardHolderData.cardHolderName,
                   newTransaction->cardHolderData.primaryAccountNumber,
                   newTransaction->cardHolderData.cardExpirationDate,
                   &newTransaction->terminalData.transAmount,
                   &newTransaction->terminalData.maxTransAmount,
                   newTransaction->terminalData.transactionDate,
                   stateStr, // Read the state as a string
                   &newTransaction->transactionSequenceNumber) != 8) {
            printf("Error parsing line: %s", line);
            free(newTransaction);
            continue;
        }

        // Convert the transaction state from string to enum
        newTransaction->transState = stringToTransState(stateStr);

        newTransaction->NEXT = NULL;
        if (Headtransaction == NULL) {
            Headtransaction = newTransaction;
        } else {
            ST_transaction_t *Helptransaction = Headtransaction;
            while (Helptransaction->NEXT != NULL) {
                Helptransaction = Helptransaction->NEXT;
            }
            Helptransaction->NEXT = newTransaction;
        }
    }
    fclose(file1);

    // Load accounts from file
    FILE *file2 = fopen("accountDB.csv", "r");
    if (file2 == NULL) {
        perror("Error opening accountDB file");
        return;
    }

    while (fgets(line, sizeof(line), file2)) {
        ST_accountsDB_t *newAccount = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        if (newAccount == NULL) {
            perror("Memory allocation failed");
            fclose(file2);
            return;
        }

        char stateStr[50];  // Buffer to hold the state string

        // Parse the data from the line
        if (sscanf(line, "%f,%[^,],%49[^\n]",
                   &newAccount->balance,
                   newAccount->primaryAccountNumber,
                   stateStr) != 3) {
            printf("Error parsing line: %s", line);
            free(newAccount);
            continue;
        }

        // Convert the account state from string to enum
        newAccount->state = stringToAccountState(stateStr);

        newAccount->NEXT = NULL;
        if (HeadaccountDB == NULL) {
            HeadaccountDB = newAccount;
        } else {
            ST_accountsDB_t *HelpaccountDB = HeadaccountDB;
            while (HelpaccountDB->NEXT != NULL) {
                HelpaccountDB = HelpaccountDB->NEXT;
            }
            HelpaccountDB->NEXT = newAccount;
        }
    }
    fclose(file2);
}

// Function to print the transactions list
void print_old_list() {
    ST_transaction_t *current = Headtransaction;

    if (current == NULL) {
        printf("The transaction list is empty.\n");
        return;
    }
     strcpy(current->cardHolderData.cardHolderName, "amrr khaled saad elsisy");
    while (current != NULL) {
        printf("Transaction:\n");
        printf("Name: %s\n", current->cardHolderData.cardHolderName);
        printf("PAN: %s\n", current->cardHolderData.primaryAccountNumber);
        printf("Expiry: %s\n", current->cardHolderData.cardExpirationDate);
        printf("Amount: %.2f\n", current->terminalData.transAmount);
        printf("Max Amount: %.2f\n", current->terminalData.maxTransAmount);
        printf("Date: %s\n", current->terminalData.transactionDate);
        printf("State: %s\n", transStateToString(current->transState));
        printf("Sequence: %d\n", current->transactionSequenceNumber);
        printf("\n");

        current = current->NEXT;
    }
}

// Function to print the accounts list
void print_new_list() {
    ST_accountsDB_t *current = HeadaccountDB;

    if (current == NULL) {
        printf("The accounts list is empty.\n");
        return;
    }
  current->state   = stringToAccountState("BLOCKED");
 while (current != NULL) {
        printf("Account:\n");
        printf("Balance: %.2f\n", current->balance);
        printf("PAN: %s\n", current->primaryAccountNumber);
        printf("State: %s\n", accountStateToString(current->state));
        printf("\n");

        current = current->NEXT;
    }
}
