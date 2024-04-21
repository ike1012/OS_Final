//Group A 
//Isaac
//Isaac.devlin@okstate.edu
//4/21/24
#include "includes.h"

int inquireAccount(char *accountID)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    lockThreads();
    
    char *fName = concat("accounts/", accountID);

    if (fileExists(fName) < 0)
    {
        // Account doesn't exist
        printf("Failed to inquire, account %s doesn't exist!\n", accountID);

        if (logTransaction(accountID, "INQUIRY", 0, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -1;
    }

    char *currBal = readFile(fName);
    if (currBal == NULL)
    {
        printf("Failed to inquire, account %s encountered a read error.\n", accountID);

        if (logTransaction(accountID, "INQUIRY", 0, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -2;
    }

    int acctBal = strToInt(currBal);

    printf("Inquired successfully! Account %s current balance: %d\n", accountID, acctBal);

    if (logTransaction(accountID, "INQUIRY", 0, NULL, "success") < 0)
        printf("Shared memory logging error!\n");

    // =====================================================
    // RELEASE THREAD LOCKING CODE
    // =====================================================
    unlockThreads();
    return 0;
}
