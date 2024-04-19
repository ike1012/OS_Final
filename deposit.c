#include "bank_operations.h"

UserAccount *depositFunds(UserAccount *accounts, char *accountID, int amount) {
    UserAccount *current = accounts;
    while (current != NULL) {
        if (strcmp(current->ID, accountID) == 0) {
            // Deposit funds into the account
            current->balance += amount;
            printf("Deposited $%d into account %s.\n", amount, accountID);
            return accounts; // Return updated account list
        }
        current = current->next;
    }
    printf("Account %s not found. Deposit failed.\n", accountID);
    return accounts; // Return unchanged account list
}
