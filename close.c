//Group A 
//Jackson
//Jackson@okstate.edu
//4/21/24


#include "includes.h"

int closeAccount(char *accountID)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    lockThreads();
    
    char *fName = concat("accounts/", accountID);

    if (fileExists(fName) < 0)
    {
        // File doesn't exist!
        printf("Close account failed! Account %s doesn't exist!\n", accountID);
        

        if (logTransaction(accountID, "CLOSE", 0, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
            
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -1;
    }

    if (remove(fName) == 0)
    {

        printf("Account %s closed successfully!\n", accountID);
        
        if (logTransaction(accountID, "CLOSE", 0, NULL, "success") < 0)
            printf("Shared memory logging error!\n");
            
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return 0;
    }
    else
    {
        printf("Action failed! Could not close account %s!\n", accountID);

        if (logTransaction(accountID, "CLOSE", 0, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
            
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -2;
    }

}
