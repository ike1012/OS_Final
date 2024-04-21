#include "includes.h"

int withdrawFromAccount(char *accountID, int balance)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    lockThreads();

    char *fName = concat("accounts/", accountID);

    if (fileExists(fName) < 0)
    {
        // Account doesn't exist
        printf("Failed to withdraw, account %s doesn't exist!\n", accountID);

        if (logTransaction(accountID, "WITHDRAW", balance, NULL, "failed") < 0)
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
        printf("Failed to withdraw, account %s encountered a read error.\n", accountID);

        if (logTransaction(accountID, "WITHDRAW", balance, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -2;
    }

    int acctBal = strToInt(currBal);

    if (acctBal - balance < 0)
    {
        printf("Failed to withdraw, account %s has insufficient funds.\n", accountID);

        if (logTransaction(accountID, "WITHDRAW", balance, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -3;
    }

    acctBal -= balance;

    char *newBal = intToStr(acctBal);

    int r = writeFile(fName, newBal);
    if (r < 0)
    {
        printf("Failed to withdraw, account %s encountered a write error.\n", accountID);

        if (logTransaction(accountID, "WITHDRAW", balance, NULL, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -4;
    }

    printf("Withdrew successfully! Account %s new balance: %d\n", accountID, acctBal);

    if (logTransaction(accountID, "WITHDRAW", balance, NULL, "success") < 0)
        printf("Shared memory logging error!\n");

    // =====================================================
    // RELEASE THREAD LOCKING CODE
    // =====================================================
    unlockThreads();
    return 0;
}
