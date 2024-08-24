# Terminal Module

## Overview

The Terminal module handles transaction-related operations in the card management system. It includes functions for date management, transaction amount handling, and card validation checks. This module is designed to interact with card data and manage transaction constraints effectively.

## Files

- **terminal.c** - Contains the implementation of terminal-related functions.
- **terminal.h** - Header file defining the data structures and function prototypes for terminal operations.

## Data Structures

### `ST_terminalData_t`
- `float transAmount` - Represents the transaction amount entered by the user.
- `float maxTransAmount` - Represents the maximum allowed transaction amount.
- `uint8_t transactionDate[11]` - Stores the current transaction date in "DD/MM/YYYY" format.

## Functions

### `void getCurrentDate(ST_terminalData_t *termData)`
- Retrieves the current date from the system and stores it in the `transactionDate` field of `ST_terminalData_t`.

### `EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)`
- Calls `getCurrentDate` to fetch and store the current transaction date. Returns `TERMINAL_OK` if successful.

### `EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)`
- Checks if the card's expiration date is before or after the current transaction date. Returns `TERMINAL_OK` if the card is not expired, or `EXPIRED_CARD` if it is.

### `EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)`
- Sets the maximum allowed transaction amount. Returns `TERMINAL_OK` if `maxAmount` is positive, or `INVALID_MAX_AMOUNT` if it is not.

### `EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)`
- Prompts the user to enter a transaction amount and stores it in `transAmount`. Returns `TERMINAL_OK` if the amount is valid, or `INVALID_AMOUNT` if it is not.

### `EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)`
- Checks if the entered transaction amount is less than or equal to the maximum allowed amount. Returns `TERMINAL_OK` if it is, or `EXCEED_MAX_AMOUNT` if it is not.

## Error Codes

- `TERMINAL_OK` - Operation completed successfully.
- `WRONG_DATE` - Date format is incorrect.
- `EXPIRED_CARD` - Card is expired.
- `INVALID_CARD` - Invalid card number (PAN).
- `INVALID_AMOUNT` - Invalid transaction amount (non-positive value).
- `EXCEED_MAX_AMOUNT` - Transaction amount exceeds the maximum allowed.
- `INVALID_MAX_AMOUNT` - Maximum transaction amount is non-positive.