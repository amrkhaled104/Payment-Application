#ifndef APP__H_
#define APP__H_

#include "../Server/server.h"


typedef enum {
    INVALID_CHOICE = -1,
    TRANSACTION = 1,
	SHOW_LAST_TRANSACTION=2,
	SHOW_TRANSACTION_HISTORY=3,
    REPORT_STOLEN_CARD = 4
} UserChoice;
void appStart(void);
#endif