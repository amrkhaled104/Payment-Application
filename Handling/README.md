**File**: `handling.c`

**Description**:  
This file handles linked list operations for transactions and accounts. It includes functions to load and save data, clear the linked lists, and convert between enums and strings for transaction and account states.

**Functions**:
- `save_data()`: Saves the transactions and accounts to files.
- `load_data()`: Loads transactions and accounts from files.
- `clear_lists()`: Clears the linked lists for transactions and accounts.
- `transStateToString()`, `stringToTransState()`: Convert transaction states between enum and string.
- `accountStateToString()`, `stringToAccountState()`: Convert account states between enum and string.

**Usage**:
- Call `save_data()` before the program exits to ensure all data is saved.
- Use `load_data()` at the start to populate the linked lists.
