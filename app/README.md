**File**: `app.c`

**Description**:  
This file contains the main application logic, including user interaction and transaction processing. 
It prompts the user to choose between performing a transaction or reporting a stolen card and then executes
the corresponding function.

**Functions**:
- `appStart()`: Starts the application, handles user input, and processes transactions.
- `display(ST_transaction_t *transData)`: Displays detailed information about a transaction.

**Usage**:
- Call `appStart()` in the `main` function to initiate the application.
