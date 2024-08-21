#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NAME_SIZE 25
#define EXP_DATE_SIZE 6
#define MAX_PAN_SIZE 20

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
    uint8_t *StrName = (uint8_t *)malloc(MAX_NAME_SIZE * sizeof(uint8_t));
    if (StrName == NULL) {
        printf("Memory allocation failed\n");
        return WRONG_NAME;
    }

    printf("Enter The Card Holder's Name: ");
    if (fgets(StrName, MAX_NAME_SIZE, stdin) != NULL) {
		
        uint8_t len = strlen(StrName);
        if (len >= 20 && len <= 24) {
            if (is_digits_only(StrName)) {
                free(StrName);
                return WRONG_NAME;
            }

            strcpy(cardData->cardHolderName, StrName);
            free(StrName);
            return CARD_OK;
        }
    } else {
        printf("Failed to read input\n");
    }

    free(StrName);
    return WRONG_NAME;
}

// Function to check if a string has the correct format for expiry date
static bool isRightFormat(uint8_t *str) {
    // Expected format: "MM/YY"
    if (isdigit(str[0]) && isdigit(str[1]) && str[2] == '/' &&
        isdigit(str[3]) && isdigit(str[4]) && str[5] == '\0') {
        return true;
    }
    return false;
}

// Function to get the card's expiration date
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    uint8_t *strExpiry = (uint8_t *)malloc(EXP_DATE_SIZE * sizeof(uint8_t));
    if (strExpiry == NULL) {
        printf("Memory allocation failed\n");
        return WRONG_EXP_DATE;
    }

    printf("Please Enter The Card's Expiry Date 'MM/YY': ");
    scanf("%5s", strExpiry);
    uint8_t len = strlen(strExpiry);

    if (len == 5 && isRightFormat(strExpiry)) {
        // Copy expiration date to cardExpirationDate
        strcpy(cardData->cardExpirationDate, strExpiry);
        free(strExpiry);
        return CARD_OK;
    } else {
        free(strExpiry);
        return WRONG_EXP_DATE;
    }
}

// Function to get the card's Primary Account Number (PAN)
EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
    uint8_t *strPAN = (uint8_t *)malloc(MAX_PAN_SIZE * sizeof(uint8_t));
    if (strPAN == NULL) {
        printf("Memory allocation failed\n");
        return WRONG_PAN;
    }

    printf("Please Enter The Card's Primary Account Number (PAN): ");
    fflush(stdin);fgets(strPAN, MAX_PAN_SIZE,stdin);
    uint8_t len = strlen(strPAN);
    if (len >= 16 && len <= 19 && is_digits_only(strPAN)) {
       
        strcpy(cardData->primaryAccountNumber, strPAN);
        free(strPAN);
        return CARD_OK;
    } else {
        free(strPAN);
        return WRONG_PAN;
    }
}

// Test functions

void getCardHolderNameTest(void) {
    ST_cardData_t obj;
    EN_cardError_t check = getCardHolderName(&obj);
    while (check == WRONG_NAME) {
        printf("Wrong input, please focus on name length (20-24 characters) and ensure it's not all numbers.\n");
        check = getCardHolderName(&obj);
    }
    printf("Card holder name is: %s\n", obj.cardHolderName);
}

void getCardExpiryDateTest(void) {
    ST_cardData_t obj;
    EN_cardError_t check = getCardExpiryDate(&obj);
    while (check == WRONG_EXP_DATE) {
        printf("Wrong input, please focus on the expiry date format (MM/YY) and ensure it is correct.\n");
        check = getCardExpiryDate(&obj);
    }
    printf("Card expiration date is: %s\n", obj.cardExpirationDate);
}

void getCardPANTest(void) {
    ST_cardData_t obj;
    EN_cardError_t check = getCardPAN(&obj);
    while (check == WRONG_PAN) {
        printf("Wrong input, please ensure the PAN is between 16 and 19 characters long and contains only alphanumeric characters.\n");
        check = getCardPAN(&obj);
    }
    printf("Card PAN is: %s\n", obj.primaryAccountNumber);
}

int main() {
    // Test the functions
   getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    return 0;
}
