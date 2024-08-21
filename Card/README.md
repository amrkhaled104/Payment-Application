# Card Data Handling

This project is designed to handle and validate card data, including the card holder's name, expiration date, and primary account number (PAN). It includes functions to validate input and ensure that it meets specific criteria.

## Files

- `card.h`: Header file that defines the data structures and function prototypes.
- `card.c`: Source file that implements the functions for handling card data.

## Functions

### `EN_cardError_t getCardHolderName(ST_cardData_t *cardData)`

Prompts the user to enter the card holder's name. It checks that the length of the name is between 20 and 24 characters and that it is not composed solely of digits. If valid, it copies the name to the `cardData` structure.

### `EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)`

Prompts the user to enter the card's expiration date in the format `MM/YY`. It validates the format and length. If valid, it copies the date to the `cardData` structure.

### `EN_cardError_t getCardPAN(ST_cardData_t *cardData)`

Prompts the user to enter the card's primary account number (PAN). It checks that the length is between 16 and 19 characters and that the PAN is alphanumeric. If valid, it copies the PAN to the `cardData` structure.

## Error Codes

- `CARD_OK`: The input is valid.
- `WRONG_NAME`: The card holder's name is invalid.
- `WRONG_EXP_DATE`: The expiration date format is incorrect.
- `WRONG_PAN`: The PAN is invalid.
