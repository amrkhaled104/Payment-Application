#include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Function to get the current date and store it in the terminal data structure
void getCurrentDate(ST_terminalData_t *termData) {
    time_t t;
    struct tm *tm_info;

    // Get the current time from the system
    time(&t);
    tm_info = localtime(&t);

    // Format the date as "DD/MM/YYYY" and store it in the struct member
    strftime(termData->transactionDate, 11, "%d/%m/%Y", tm_info);
}

// Function to get the transaction date and store it in the terminal data structure
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
    getCurrentDate(termData);
    return TERMINAL_OK;
}

// Function to check if the card is expired
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData) {
    int cardMonth, cardYear, NowDay, NowMonth, NowYear;
    
    sscanf(cardData->cardExpirationDate, "%d/%d", &cardMonth, &cardYear);
    sscanf(termData->transactionDate, "%d/%d/%d", &NowDay, &NowMonth, &NowYear);
    
    cardYear += 2000;

    if (cardYear > NowYear)
        return TERMINAL_OK;
    else if (cardYear == NowYear) {
        if (cardMonth >= NowMonth)
            return TERMINAL_OK;
    }
    return EXPIRED_CARD;
}

// Function to set the maximum transaction amount
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount) {
    if (maxAmount > 0) {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }
    return INVALID_MAX_AMOUNT;
}

// Function to get the transaction amount from the user
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
    float amount;
    
    printf("Please Enter The Transaction Amount: ");
    
    if (scanf("%f", &amount) != 1) {
        return INVALID_AMOUNT;
    }
	
    if (amount > 0) {
        termData->transAmount = amount;
        return TERMINAL_OK;
    }
    return INVALID_AMOUNT;
}

// Function to check if the transaction amount is below the maximum amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
    if (termData->transAmount <= termData->maxTransAmount)
        return TERMINAL_OK;
    return EXCEED_MAX_AMOUNT;
}

// Function to check if the PAN is valid using the Luhn algorithm
int isLuhnValid(const char *pan) {
    int sum = 0;
    int length = strlen(pan);
    int isOdd = 0; // To track if we are in an odd or even position

    // Iterate through each digit from the end to the beginning
    for (int i = length - 1; i >= 0; i--) {
        if (!isdigit(pan[i])) {
            return 0; // If any non-digit character is found, the PAN is invalid
        }

        int digit = pan[i] - '0'; // Convert character to digit

        if (isOdd) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9; // If the result is greater than 9, subtract 9
            }
        }

        sum += digit;
        isOdd = !isOdd; // Toggle between odd and even positions
    }

    // Check if the sum is divisible by 10
    return (sum % 10 == 0);
}

// Function to validate the card's PAN
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData) {
    if (isLuhnValid(cardData->primaryAccountNumber))
        return TERMINAL_OK;
    return INVALID_CARD;
}

int main() {
    ST_terminalData_t obj;
    EN_terminalError_t status;

    // Get the current transaction date and store it in the struct
    status = getTransactionDate(&obj);
    if (status != TERMINAL_OK) {
        printf("Failed to get transaction date.\n");
        return 1;
    }

    // Print the stored transaction date
    printf("Current Date: %s\n", obj.transactionDate);

    return 0;
}
