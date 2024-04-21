#include "includes.h"

int createNewAccount(char *accountID, int startingBalance)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    
    char *fName = concat("accounts/", accountID);

    if (fileExists(fName) < 0)
    {
        // Account doesn't exist, create it now

        int r = writeFile(fName, intToStr(startingBalance));
        if (r < 0)
        {
            // Failed

            if (logTransaction(accountID, "CREATE", startingBalance, NULL, "failed") < 0)
                printf("Shared memory logging error!\n");
            
            printf("Failed to create account %s\n", accountID);

            // =====================================================
            // RELEASE THREAD LOCKING CODE
            // =====================================================
            return -2;
        }
        else
        {
            // Success

            if (logTransaction(accountID, "CREATE", startingBalance, NULL, "success") < 0)
                printf("Shared memory logging error!\n");

            printf("Account %s was successfully opened!\n", accountID);

            // =====================================================
            // RELEASE THREAD LOCKING CODE
            // =====================================================
            return 0;
        }
    }
    else
    {
        // Account already exists
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================

        if (logTransaction(accountID, "CREATE", startingBalance, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
            
        return -1;
    }
}
