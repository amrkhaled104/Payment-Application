#ifndef CARD_H
#define CARD_H

#include <stdint.h> 

// Structure to hold card data
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];       // Name of the card holder
    uint8_t primaryAccountNumber[20]; // Primary Account Number (PAN)
    uint8_t cardExpirationDate[6];    // Expiration Date of the card
} ST_cardData_t;

// Enumeration to define possible card errors
typedef enum EN_cardError_t
{
    CARD_OK,          // No error, input is valid
    WRONG_NAME,       // Invalid card holder name
    WRONG_EXP_DATE,   // Invalid expiration date
    WRONG_PAN         // Invalid PAN
} EN_cardError_t;

// Function prototypes
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif
