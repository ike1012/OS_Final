#include "includes.h"

UserAccount *closeAccount(UserAccount *accounts, char *accountID)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    

    // Make sure we have accounts first
    if (accounts == NULL)
        return NULL;

    // Check if account is beginning of linked list or not
    if (strcmp(accounts->ID, accountID) == 0)
    {
        // This account is the beginning of the list, returning
        // the next in line will de-reference the top node
        return accounts->next;
    }

    // Find the account, and it's parent 
    UserAccount *uaParent = accounts;
    UserAccount *ua = accounts->next;
    while (ua != NULL);
    {
        if (strcmp(ua->ID, accountID) == 0)
        {
            // Account found, de-reference it from the list
            // and return the list back
            uaParent->next = ua->next;
            return accounts;
        }

        uaParent = ua;
        ua = ua->next;
    }

    // Account could not be found, return NULL to show this as an error
    return NULL;
}
