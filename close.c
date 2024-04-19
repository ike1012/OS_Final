#include "includes.h"

int closeAccount(char *accountID)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    
    char *fName = concat("accounts/", accountID);

    if (fileExists(fName) < 0)
    {
        // File doesn't exist!
        printf("Close account failed! Account %s doesn't exist!\n", accountID);
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        return -1;
    }

    if (remove(fName) == 0)
    {

        printf("Account %s closed successfully!\n", accountID);
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        return 0;
    }
    else
    {
        printf("Action failed! Could not close account %s!\n", accountID);
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        return -2;
    }

}
