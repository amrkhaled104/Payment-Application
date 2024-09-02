#include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Function to get the current date and store it in the terminal data structure
void getCurrentDate(ST_terminalData_t *termData) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(termData->transactionDate, sizeof(termData->transactionDate), "%d/%m/%Y", tm_info);
}

// Function to get the transaction date and store it in the terminal data structure
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
    getCurrentDate(termData);
    return TERMINAL_OK;
}

// Function to check if the card is expired
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData) {
    int cardMonth, cardYear, NowDay, NowMonth, NowYear;
    
    sscanf((char*)cardData->cardExpirationDate, "%d/%d", &cardMonth, &cardYear);
    sscanf((char*)termData->transactionDate, "%d/%d/%d", &NowDay, &NowMonth, &NowYear);
    
    cardYear += 2000;

    if (cardYear > NowYear || (cardYear == NowYear && cardMonth >= NowMonth))
        return TERMINAL_OK;
    
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
    
    if (scanf("%f", &amount) == 1 && amount > 0) {
        termData->transAmount = amount;
        return TERMINAL_OK;
    }
    return INVALID_AMOUNT;
}

// Function to check if the transaction amount is below the maximum amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
    return (termData->transAmount <= termData->maxTransAmount) ? TERMINAL_OK : EXCEED_MAX_AMOUNT;
}

// Function to check if the PAN is valid using the Luhn algorithm
static int isLuhnValid(const char *pan) {
    int sum = 0, isOdd = 0, length = strlen(pan);

    for (int i = length - 1; i >= 0; i--) {
        if (!isdigit(pan[i])) return 0;
        
        int digit = pan[i] - '0';
        if (isOdd) digit = (digit * 2 > 9) ? digit * 2 - 9 : digit * 2;

        sum += digit;
        isOdd = !isOdd;
    }

    return (sum % 10 == 0);
}

// Function to validate the card's PAN
EN_terminalError_t isValidCardPAN(const char *str) {
    return isLuhnValid(str) ? TERMINAL_OK : INVALID_CARD;
}
