#include "includes.h"

int transferFunds(char *acctFrom, char *acctTo, int balance)
{
    // =====================================================
    // NEED THREAD LOCKING CODE
    // =====================================================
    lockThreads();

    char *fNameSrc = concat("accounts/", acctFrom);

    if (fileExists(fNameSrc) < 0)
    {
        // Account doesn't exist
        printf("Failed to access account %s, it doesn't exist!\n", acctFrom);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -1;
    }

    char *fNameDst = concat("accounts/", acctTo);

    if (fileExists(fNameDst) < 0)
    {
        // Account doesn't exist
        printf("Failed to access account %s, it doesn't exist!\n", acctTo);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -2;
    }

    
    char *currBalSrc = readFile(fNameSrc);
    if (currBalSrc == NULL)
    {
        printf("Failed to access account %s, a read error has occurred.\n", acctFrom);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -3;
    }

    char *currBalDst = readFile(fNameDst);
    if (currBalDst == NULL)
    {
        printf("Failed to access account %s, a read error has occurred.\n", acctTo);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -4;
    }

    int srcBal = strToInt(currBalSrc);
    int dstBal = strToInt(currBalDst);

    if (srcBal - balance < 0)
    {
        printf("Failed to transfer, account %s has insufficient funds.\n", acctFrom);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -5;
    }

    srcBal -= balance;
    dstBal += balance;

    char *newBalSrc = intToStr(srcBal);
    char *newBalDst = intToStr(dstBal);

    int r = writeFile(fNameSrc, newBalSrc);
    if (r < 0)
    {
        printf("Failed to transfer, account %s encountered a write error.\n", acctFrom);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -6;
    }

    r = writeFile(fNameDst, newBalDst);
    if (r < 0)
    {
        printf("Failed to transfer, account %s encountered a write error.\n", acctTo);

        if (logTransaction(acctFrom, "TRANSFER", balance, acctTo, "failed") < 0)
            printf("Shared memory logging error!\n");
        
        // =====================================================
        // RELEASE THREAD LOCKING CODE
        // =====================================================
        unlockThreads();
        return -7;
    }

    printf("Transferred successfully!\n\tAccount %s new balance: %d\n\tAccount %s new balance: %d\n", acctFrom, srcBal, acctTo, dstBal);

    if (logTransaction(acctFrom, "TRANSFER", 0, acctTo, "success") < 0)
        printf("Shared memory logging error!\n");

    // =====================================================
    // RELEASE THREAD LOCKING CODE
    // =====================================================
    unlockThreads();
    return 0;
}