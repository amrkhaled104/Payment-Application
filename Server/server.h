#ifndef SERVER_H
#define SERVER_H

#include "../Card/card.h"
#include "../Terminal/terminal.h"


typedef enum EN_transState_t {
    APPROVED, 
    DECLINED_INSUFFICIENT_FUND, 
	DECLINED_EXCEEDING_AMOUNT,
	DECLINED_EXPIRED_CARD,
    DECLINED_STOLEN_CARD,
    FRAUD_CARD, 
    INTERNAL_SERVER_ERROR
} EN_transState_t;

typedef struct ST_transaction_t {
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
    struct ST_transaction_t *NEXT;
} ST_transaction_t;

typedef enum EN_serverError_t {
    SERVER_OK, 
    SAVING_FAILED, 
    TRANSACTION_NOT_FOUND, 
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE, 
    BLOCKED_ACCOUNT
} EN_serverError_t;

typedef enum EN_accountState_t {
    RUNNING,
    BLOCKED
} EN_accountState_t;

typedef struct ST_accountsDB_t {
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
    struct ST_accountsDB_t *NEXT;
} ST_accountsDB_t;

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_transaction_t *transData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);
void initialize();
void reportStolenCard();

#endif /* SERVER_H */

