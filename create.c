#include "includes.h"

int createNewAccount(char *accountID, int startingBalance)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    lockThreads();
    
    char *fName = concat("accounts/", accountID);

    if (fileExists(fName) < 0)
    {
        // Account doesn't exist, create it now

        int r = writeFile(fName, intToStr(startingBalance));
        if (r < 0)
        {
            // Failed

            printf("Failed to create account %s\n", accountID);

            if (logTransaction(accountID, "CREATE", startingBalance, NULL, "failed") < 0)
                printf("Shared memory logging error!\n");
            
            // =====================================================
            // RELEASE THREAD LOCKING CODE
            // =====================================================
            unlockThreads();
            return -2;
        }
        else
        {
            // Success

            printf("Account %s was successfully opened!\n", accountID);

            if (logTransaction(accountID, "CREATE", startingBalance, NULL, "success") < 0)
                printf("Shared memory logging error!\n");

            // =====================================================
            // RELEASE THREAD LOCKING CODE
            // =====================================================
            unlockThreads();
            return 0;
        }
    }
    else
    {
        // Account already exists

        printf("Failed to create account %s\n", accountID);

        if (logTransaction(accountID, "CREATE", startingBalance, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
            
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -1;
    }
}
