#ifndef HANDLING_H
#define HANDLING_H

#include "../Server/server.h"
#include "../Terminal/terminal.h"

const char* transStateToString(EN_transState_t state);
EN_transState_t stringToTransState(const char *str);
const char* accountStateToString(EN_accountState_t state);
EN_accountState_t stringToAccountState(const char *str);
void save_data();
void clear_lists();
void load_data();
void print_old_list();
void print_new_list();

#endif /* HANDLING_H */
