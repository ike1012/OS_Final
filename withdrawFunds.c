#include "includes.h"
UserAccount *withdrawFunds(UserAccount *accounts, char *accountID, int amount)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================

    UserAccount *current = accounts;

    // Find the account
    while (current != NULL && strcmp(current->ID, accountID) != 0)
    {
        current = current->next;
    }

    // If account is not found or balance is insufficient
    if (current == NULL || current->balance < amount)
    {
        printf("Withdrawal failed: Insufficient funds or account not found.\n");
        return accounts; // No changes to accounts list
    }

    // Withdraw funds
    current->balance -= amount;
    printf("Withdrawal successful: $%d withdrawn from account %s\n", amount, accountID);
    return accounts;
}
