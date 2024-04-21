//Group A 
//James
//James.jolly@okstate.edu
//4/21/24
#include "includes.h"

// Declare the transaction detail logs
struct TransactionDetails *AllTransactions[100];
static int TOTAL_TRANSACTIONS = 100;

int initSharedMemory()
{
    for (int i = 0; i < TOTAL_TRANSACTIONS; i++)
    {
        AllTransactions[i] = mmap(NULL, sizeof(struct TransactionDetails), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (AllTransactions[i] == MAP_FAILED)
            return -1;

        clearStr(AllTransactions[i]->accountID, 10);
        clearStr(AllTransactions[i]->transactionType, 10);
        clearStr(AllTransactions[i]->targetID, 10);
        clearStr(AllTransactions[i]->status, 10);
        AllTransactions[i]->amount = 0;
        AllTransactions[i]->timeStamp = 0;
    }

    return 0;
}

int logTransaction(char *acctID, char *transType, int amount, char *targetID, char *status)
{
    time_t timeStamp = time(NULL);

    for (int i = 0; i < TOTAL_TRANSACTIONS; i++)
    {
        if (len(AllTransactions[i]->accountID) <= 0)
        {
            AllTransactions[i]->amount = amount;    
            AllTransactions[i]->timeStamp = timeStamp;
            if (acctID != NULL)
                strcpy(AllTransactions[i]->accountID, acctID);
            if (transType != NULL)
                strcpy(AllTransactions[i]->transactionType, transType);
            if (targetID != NULL)
                strcpy(AllTransactions[i]->targetID, targetID);
            if (status != NULL)
                strcpy(AllTransactions[i]->status, status);

            return 0;
        }
    }

    return -1;
}

void displayTransactionLogs()
{
    printf("\n\nDisplaying all transaction logs\n\n");

    for (int i = 0; i < TOTAL_TRANSACTIONS; i++)
    {
        if (len(AllTransactions[i]->accountID) > 0)
        {
            printf("Transaction Details:\n\tAccount: %s\n\tTransaction: %s\n\tAmount: %d\n\tTarget: %s\n\tTimestamp: %ld\n\tStatus: %s\n\n",
                AllTransactions[i]->accountID, AllTransactions[i]->transactionType, AllTransactions[i]->amount, AllTransactions[i]->targetID, AllTransactions[i]->timeStamp, AllTransactions[i]->status);
        }
    }
}