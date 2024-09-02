#ifndef APP__H_
#define APP__H_

#include "../Server/server.h"


typedef enum {
    INVALID_CHOICE = -1,
    TRANSACTION = 1,
    REPORT_STOLEN_CARD = 2
} UserChoice;

void appStart(void);
#endif