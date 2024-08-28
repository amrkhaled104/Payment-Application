#include <stdio.h>
#include <stdlib.h>
#include "handling.h"

int main() {
    // Load data into the linked list
    load_data();

    // Print the contents of the linked list
    printf("Displaying Transactions:\n");
    print_old_list();
    print_new_list();
    save_data();
    // Clean up the list
    clear_lists();

    return 0;
}
