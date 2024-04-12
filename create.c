#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "includes.h"

UserAccount *createNewAccount(UserAccount *accounts, char *accountID, int startingBalance)
{
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

UserAccount *findAccount(UserAccount *accounts, char *accountID)
{
    if (accounts == NULL)
        return NULL;

    if (strcmp(accounts->ID, accountID) == 0)
        return accounts;

    struct UserAccount *ua = accounts->next;
    while (ua != NULL)
    {
        if (strcmp(ua->ID, accountID) == 0)
            return accounts;

        ua = ua->next;
    }
    return NULL;
}