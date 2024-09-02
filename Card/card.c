#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Function to check if a string contains only digits
static bool is_digits_only(const uint8_t *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Function to get the card holder's name
EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
    uint8_t StrName[MAX_NAME_SIZE];
    fflush(stdin);
    printf("Enter The Card Holder's Name: ");
    if (fgets(StrName, MAX_NAME_SIZE, stdin) != NULL) {
        uint8_t len = strlen(StrName);
        // Remove newline character if present
        if (StrName[len - 1] == '\n') StrName[len - 1] = '\0';
        len = strlen(StrName);
        
        if (len >= 20 && len <= 24 && !is_digits_only(StrName)) {
            strcpy(cardData->cardHolderName, StrName);
            return CARD_OK;
        }
    } else {
        printf("Failed to read input\n");
    }
    return WRONG_NAME;
}

// Function to check if a string has the correct format for expiry date
static bool isRightFormat(const uint8_t *str) {
    // Expected format: "MM/YY"
    return isdigit(str[0]) && isdigit(str[1]) && str[2] == '/' &&
           isdigit(str[3]) && isdigit(str[4]) && str[5] == '\0';
}

// Function to get the card's expiration date
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    uint8_t strExpiry[EXP_DATE_SIZE];
    printf("Please Enter The Card's Expiry Date 'MM/YY': ");
    fflush(stdin);
    if (scanf("%5s", strExpiry) == 1) {
        if (isRightFormat(strExpiry)) {
            strcpy(cardData->cardExpirationDate, strExpiry);
            return CARD_OK;
        }
    }
    return WRONG_EXP_DATE;
}

// Function to get the card's Primary Account Number (PAN)
EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
    uint8_t strPAN[MAX_PAN_SIZE];
    printf("Please Enter The Card's Primary Account Number (PAN): ");
    fflush(stdin);
    if (fgets(strPAN, MAX_PAN_SIZE, stdin) != NULL) {
        uint8_t len = strlen(strPAN);
        // Remove newline character if present
        if (strPAN[len - 1] == '\n') strPAN[len - 1] = '\0';
        len = strlen(strPAN);
        
        if (len >= 16 && len <= 19 && is_digits_only(strPAN)) {
            strcpy(cardData->primaryAccountNumber, strPAN);
            return CARD_OK;
        }
    }
    return WRONG_PAN;
}
