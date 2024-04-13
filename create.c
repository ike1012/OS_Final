#include "includes.h"

UserAccount *createNewAccount(UserAccount *accounts, char *accountID, int startingBalance)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    


    // Check if the list has been created yet
    if (accounts == NULL)
    {
        // This will be the first account to create

        accounts = malloc(sizeof(struct UserAccount));
        strcpy(accounts->ID, accountID);
        accounts->balance = startingBalance;

        return accounts;
    }

    // Check if the account has already been added to the list or not
    if (findAccount(accounts, accountID) != NULL)
    {
        printf("Account \"%s\" already exists!", accountID);
        return NULL;
    }
    
    struct UserAccount *ua = accounts;
    while (ua->next != NULL)
    {
        ua = ua->next;
    }

    // Add new account to the list
    struct UserAccount *newAccount = malloc(sizeof(struct UserAccount));
    strcpy(newAccount->ID, accountID);
    newAccount->balance = startingBalance;

    ua->next = newAccount;

    return newAccount;
}
