#include "bank_operations.h"

void checkBalance(UserAccount *accounts, char *accountID) {
    // Find the account
    UserAccount *current = findAccount(accounts, accountID);

    // If account is not found
    if (current == NULL) {
        printf("Account \"%s\" not found.\n", accountID);
        return;
    }

    // Display account balance
    printf("Account balance for %s: $%d\n", accountID, current->balance);
}
