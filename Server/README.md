Here's a lighter README file with a brief project description and a function overview:

---

# README

## Project Overview
### `server.c`

- **`initialize()`**: Sets up global pointers for accounts and transactions.
- **`recieveTransactionData(ST_transaction_t *transData)`**: Handles transaction processing, including validation and balance updates.
- **`isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t* accountRefrence)`**: Checks if the provided card data matches an existing account.
- **`isAmountAvailable(ST_transaction_t *transData)`**: Verifies if there is enough balance for the transaction.
- **`isBlockedAccount(ST_accountsDB_t *accountRefrence)`**: Determines if the account is blocked.
- **`update_Account_Balance_and_amount_trans(ST_transaction_t *transData)`**: Updates the account balance and records the transaction.
- **`reportStolenCard()`**: Allows reporting and blocking of stolen cards.

### `server.h`

Defines data structures and enumerations used in `server.c`, including:

- **Transaction States** (`EN_transState_t`): `APPROVED`, `DECLINED_INSUFFICIENT_FUND`, `FRAUD_CARD`, etc.
- **Transaction Structure** (`ST_transaction_t`): Contains card data, terminal data, and transaction state.
- **Server Errors** (`EN_serverError_t`): Error codes like `ACCOUNT_NOT_FOUND`, `LOW_BALANCE`.
- **Account Structure** (`ST_accountsDB_t`): Holds account details including balance and state.

## Author

Amr Khaled  
[GitHub Profile](https://github.com/amrkhaled104)
