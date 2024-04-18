#include "includes.h"
UserAccount *depositFunds(UserAccount *accounts, char *accountID, int amount)
{
    // Find the account
    UserAccount *current = accounts;
    while (current != NULL && strcmp(current->ID, accountID) != 0)
    {
        current = current->next;
    }

    // If account is not found
    if (current == NULL)
    {
        printf("Deposit failed: Account not found.\n");
        return accounts; // No changes to accounts list
    }

    // Deposit funds
    current->balance += amount;
    printf("Deposit successful: $%d deposited into account %s\n", amount, accountID);
    return accounts;
}
