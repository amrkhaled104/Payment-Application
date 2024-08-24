# Card Module

## Overview

The Card module manages card-related data, including the cardholder's name, expiration date, and primary account number (PAN). It provides functions to retrieve and validate this information, ensuring it meets expected formats and constraints.

## Files

- **card.h** - Header file defining the data structures and function prototypes for card operations.
- **card.c** - Contains the implementation of functions for handling card data.

## Data Structures

### `ST_cardData_t`
- `uint8_t cardHolderName[25]` - Stores the name of the cardholder.
- `uint8_t primaryAccountNumber[20]` - Stores the Primary Account Number (PAN).
- `uint8_t cardExpirationDate[6]` - Stores the expiration date of the card in "MM/YY" format.

## Enumeration

### `EN_cardError_t`
- `CARD_OK` - No error, input is valid.
- `WRONG_NAME` - Invalid cardholder name.
- `WRONG_EXP_DATE` - Invalid expiration date.
- `WRONG_PAN` - Invalid PAN.

## Functions

### `EN_cardError_t getCardHolderName(ST_cardData_t *cardData)`
- Prompts the user to enter the cardholder's name and stores it in `cardHolderName`.
- Validates that the name is between 20 and 24 characters and does not contain digits.
- Returns `CARD_OK` if valid, or `WRONG_NAME` if invalid.

### `EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)`
- Prompts the user to enter the card's expiration date in "MM/YY" format and stores it in `cardExpirationDate`.
- Validates that the format is correct and the length is exactly 5 characters.
- Returns `CARD_OK` if valid, or `WRONG_EXP_DATE` if invalid.

### `EN_cardError_t getCardPAN(ST_cardData_t *cardData)`
- Prompts the user to enter the card's Primary Account Number (PAN) and stores it in `primaryAccountNumber`.
- Validates that the PAN is between 16 and 19 digits long and contains only digits.
- Returns `CARD_OK` if valid, or `WRONG_PAN` if invalid.

## Error Codes

- `CARD_OK` - Operation completed successfully, input is valid.
- `WRONG_NAME` - Invalid cardholder name (contains digits or incorrect length).
- `WRONG_EXP_DATE` - Invalid expiration date (incorrect format or length).
- `WRONG_PAN` - Invalid PAN (contains non-digit characters or incorrect length).

