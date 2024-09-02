#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../Terminal/terminal.h"

// Function to check if a string contains only digits
static bool is_digits_only(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Function to check if a string has the correct format for expiry date
static bool isRightFormat(const char *str) {
    return isdigit(str[0]) && isdigit(str[1]) && str[2] == '/' &&
           isdigit(str[3]) && isdigit(str[4]) && str[5] == '\0';
}

// Function to get the card holder's name
EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
    char *StrName = (char *)malloc(25 * sizeof(char)); // Allocate memory for input
    if (StrName == NULL) {
        printf("Error: Memory allocation failed.\n");
        return WRONG_NAME;
    }

    printf("Enter The Card Holder's Name: ");
    if (fgets(StrName, 25, stdin) != NULL) {
        size_t len = strlen(StrName);
        // Remove newline character if present
        if (len > 0 && StrName[len - 1] == '\n') {
            StrName[len - 1] = '\0';
            len--;
        }
        
        // Validate length and content of the name
        if (len < 20 || len > 24) {
            printf("Error: Name length must be between 20 and 24 characters.\n");
            free(StrName); // Free allocated memory
            return WRONG_NAME;
        }
        
        // Check if the name contains only digits
        if (is_digits_only(StrName)) {
            printf("Error: Name must not be only digits.\n");
            free(StrName); // Free allocated memory
            return WRONG_NAME;
        }

        // Copy valid name to cardData
        strcpy(cardData->cardHolderName, StrName);
        free(StrName); // Free allocated memory
        return CARD_OK;
    } else {
        printf("Error: Failed to read input.\n");
        free(StrName); // Free allocated memory
        return WRONG_NAME;
    }
}

// Function to get the card's expiration date
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    char *strExpiry = (char *)malloc(6 * sizeof(char)); // Allocate memory for input
    if (strExpiry == NULL) {
        printf("Error: Memory allocation failed.\n");
        return WRONG_EXP_DATE;
    }

    printf("Please Enter The Card's Expiry Date 'MM/YY': ");
	fflush(stdin);
    if (fgets(strExpiry, 6, stdin) != NULL) {
        size_t len = strlen(strExpiry);
        // Remove newline character if present
        if (len > 0 && strExpiry[len - 1] == '\n') {
            strExpiry[len - 1] = '\0';
            len--;
        }

        if (len == 5 && isRightFormat(strExpiry)) {
            strcpy(cardData->cardExpirationDate, strExpiry);
            free(strExpiry); // Free allocated memory
            return CARD_OK;
        } else {
            printf("Error: Invalid expiry date format. Please use 'MM/YY' and ensure it is exactly 5 characters long.\n");
        }
    } else {
        printf("Error: Failed to read input.\n");
    }

    free(strExpiry); // Free allocated memory
    return WRONG_EXP_DATE;
}

// Function to get the card's Primary Account Number (PAN)
EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
    char *strPAN = (char *)malloc(20 * sizeof(char)); // Allocate memory for input
    if (strPAN == NULL) {
        printf("Error: Memory allocation failed.\n");
        return WRONG_PAN;
    }

    printf("Please Enter The Card's Primary Account Number (PAN): ");
	fflush(stdin);
    if (fgets(strPAN, 20, stdin) != NULL) {
        size_t len = strlen(strPAN);
        // Remove newline character if present
        if (len > 0 && strPAN[len - 1] == '\n') {
            strPAN[len - 1] = '\0';
            len--;
        }

        if (isValidCardPAN(strPAN) == TERMINAL_OK) {
            strcpy(cardData->primaryAccountNumber, strPAN);
            free(strPAN); // Free allocated memory
            return CARD_OK;
        } else {
            printf("Error: Invalid PAN. The PAN must be between 16 and 19 digits long, contain only digits, and pass Luhn validation.\n");
        }
    } else {
        printf("Error: Failed to read input.\n");
    }

    free(strPAN); // Free allocated memory
    return WRONG_PAN;
}
