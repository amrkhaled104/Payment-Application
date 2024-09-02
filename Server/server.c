#include "server.h"
#include<stdio.h>
#include<string.h>

extern ST_accountsDB_t *HeadaccountDB;
extern ST_transaction_t *Headtransaction;
#define Maxamount 3000
ST_accountsDB_t *HElpaccountDB;
ST_transaction_t *HELPtransaction;

void initialize() {
    HElpaccountDB = HeadaccountDB;
    HELPtransaction = Headtransaction;
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
	
    while(getCardHolderName(&(transData->cardHolderData)) == WRONG_NAME);
    while(getCardExpiryDate(&(transData->cardHolderData)) == WRONG_EXP_DATE);
    while(getCardPAN(&(transData->cardHolderData)) == WRONG_PAN);
	while(setMaxAmount(&(transData->terminalData), Maxamount) == INVALID_MAX_AMOUNT);
	
    getTransactionDate(&(transData->terminalData));
	
	ST_accountsDB_t accountRefrence;
    if (isValidAccount(&(transData->cardHolderData), &accountRefrence) == ACCOUNT_NOT_FOUND) {
        transData->transState = FRAUD_CARD;
        HELPtransaction->transState = transData->transState;
        return FRAUD_CARD;
    }
    if (isBlockedAccount(&accountRefrence) == BLOCKED_ACCOUNT) {
        transData->transState = DECLINED_STOLEN_CARD;
        HELPtransaction->transState = transData->transState;
        return DECLINED_STOLEN_CARD;
    }
    if (isCardExpired(&transData->cardHolderData,&transData->terminalData) == EXPIRED_CARD) {
        transData->transState = DECLINED_EXPIRED_CARD;
        HELPtransaction->transState = transData->transState;
        return DECLINED_EXPIRED_CARD;
    }
   
    while(getTransactionAmount(&(transData->terminalData)) == INVALID_AMOUNT);

    if (isBelowMaxAmount(&(transData->terminalData)) == EXCEED_MAX_AMOUNT) {
        transData->transState = DECLINED_EXCEEDING_AMOUNT;
        HELPtransaction->transState = transData->transState;
        return DECLINED_EXCEEDING_AMOUNT;
    }
	if (isAmountAvailable(transData) == LOW_BALANCE) {
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        HELPtransaction->transState = transData->transState;
        return DECLINED_INSUFFICIENT_FUND;
    }

    update_Account_Balance_and_amount_trans(transData);

    transData->transState = APPROVED;
    HELPtransaction->transState = transData->transState;
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t* accountRefrence) {
    ST_accountsDB_t *current = HElpaccountDB;
    while (current != NULL) {
        if (strcmp((char*)cardData->primaryAccountNumber, (char*)current->primaryAccountNumber) == 0) {
            *accountRefrence = *current;
            return SERVER_OK;
        }
        current = current->NEXT;
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_transaction_t *transData) {
    ST_accountsDB_t *current = HElpaccountDB;
    while (current != NULL) {
        if (strcmp((char*)transData->cardHolderData.primaryAccountNumber, (char*)current->primaryAccountNumber) == 0) {
            if (transData->terminalData.transAmount <= current->balance) {
                return SERVER_OK;
            } else {
                return LOW_BALANCE;
            }
        }
        current = current->NEXT;
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence) {
	
    if (accountRefrence->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    } else {
        return SERVER_OK;
    }
}
 void update_Account_Balance_and_amount_trans(ST_transaction_t *transData) {
    ST_accountsDB_t *current = HElpaccountDB;
    while (current != NULL) {
        if (strcmp(transData->cardHolderData.primaryAccountNumber,current->primaryAccountNumber) == 0) {
            current->balance -= transData->terminalData.transAmount;
            break;
        }
        current = current->NEXT;
    }
    HELPtransaction->terminalData.transAmount = transData->terminalData.transAmount;
    getTransactionDate(&transData->terminalData);
	HELPtransaction->transactionSequenceNumber++;
}
void reportStolenCard() {
    char pan[20];
    printf("Enter the PAN of the stolen card: ");
    scanf("%s", pan);
    HElpaccountDB=HeadaccountDB;
    // Find the account and update status
    while (HElpaccountDB != NULL) {
        if (strcmp(HElpaccountDB->primaryAccountNumber, pan) == 0) {
            HElpaccountDB->state=BLOCKED;
            printf("The card with PAN %s has been reported as stolen and blocked.\n", pan);
            return;
        }
        HElpaccountDB = HElpaccountDB->NEXT;
    }

    printf("No account found with PAN %s.\n", pan);
}
