#include "includes.h"
void checkBalance(UserAccount *accounts, char *accountID)
{
    UserAccount *account = findAccount(accounts, accountID);

    // Check if the account exists
    if (account == NULL)
    {
        printf("Balance inquiry failed: Account not found.\n");
        return;
    }

    // Display the balance
    printf("Balance inquiry: Account %s has a balance of $%d\n", accountID, account->balance);
}
