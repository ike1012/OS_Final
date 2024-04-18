#include "bank_operations.h"
#include <pthread.h>

struct UserAccount *AllAccounts;
pthread_mutex_t lock;

int main(char *args)
{
    int sel;
    AllAccounts = NULL;

    // Initialize mutex lock
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex lock initialization failed.\n");
        return 1;
    }

    char *inputFileName = "inputFile.txt";
    
    // Open input file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    int fSize = 0;

    if (inputFile == NULL)
    {
        printf("Input file not found.\n");
        exit(0);
    }

    // Get the file size
    fseek(inputFile, 0, SEEK_END);
    fSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Read the file contents
    char *fData = malloc(fSize);
    fread(fData, fSize, 1, inputFile);

    // Close the file
    fclose(inputFile);

    printf("Parsing input file (Size %d)...\n", fSize);
    
    // Replace all \r's with \n's
    for (int i = 0; i < fSize; i++)
    {
        if (fData[i] == '\r')
            fData[i] = '\n';
    }

    int index = 0;
    char *cLine = readLine(fData, index, fSize);
    int lineCounter = 0;
    while (index < fSize)
    {
        cLine = readLine(fData, index, fSize);
        
        if (cLine != NULL)
        {
            // Processing each line
            if (lineCounter > 0)
            {
                int lineIndex = 0;

                if (len(cLine) > 0)
                {
                    char *acct = readSplit(cLine, lineIndex);
                    lineIndex += len(acct) + 1;

                    char *action = readSplit(cLine, lineIndex);
                    lineIndex += len(action) + 1;

                    printf("acct: %s -> action: %s\n", acct, action);

                    pthread_mutex_lock(&lock); // Lock before accessing shared data

                    if (findAccount(AllAccounts, acct) == NULL)
                    {
                        if (strcmp(action, "Create") == 0)
                        {
                            // Create account
                            char *startingBalance = readSplit(cLine, lineIndex);
                            int bal = strToInt(startingBalance);

                            AllAccounts = createNewAccount(AllAccounts, acct, bal);
                            if (AllAccounts == NULL)
                                AllAccounts = newAccount;

                            debug_DisplayAccountListings(AllAccounts);
                        }
                        else
                        {
                            printf("Account \'%s\' doesn't exist!\n", acct);
                        }
                    }
                    else
                    {
                        // Account exists, perform action
                        if (strcmp(action, "Create") == 0)
                        {
                            printf("Account \'%s\' already exists!\n", acct);
                        }
                        else if (strcmp(action, "Close") == 0)
                        {
                            UserAccount *newAccountList = closeAccount(AllAccounts, acct);
                            if (newAccountList == NULL)
                            {
                                printf("Close Account Error: Account did not exist!\n");
                            }
                            else
                            {
                                AllAccounts = newAccountList;
                                debug_DisplayAccountListings(AllAccounts);
                            }
                        }
                        else if (strcmp(action, "Withdraw") == 0)
                        {
                            char *withdrawAmountStr = readSplit(cLine, lineIndex);
                            int withdrawAmount = strToInt(withdrawAmountStr);

                            AllAccounts = withdrawFunds(AllAccounts, acct, withdrawAmount);
                            debug_DisplayAccountListings(AllAccounts);
                        }
                        else if (strcmp(action, "Deposit") == 0)
                        {
                            char *depositAmountStr = readSplit(cLine, lineIndex);
                            int depositAmount = strToInt(depositAmountStr);

                            AllAccounts = depositFunds(AllAccounts, acct, depositAmount);
                            debug_DisplayAccountListings(AllAccounts);
                        }
                        else if (strcmp(action, "Inquiry") == 0)
                        {
                            checkBalance(AllAccounts, acct);
                        }
                        else if (strcmp(action, "Transfer") == 0)
                        {
                            char *transferAmountStr = readSplit(cLine, lineIndex);
                            int transferAmount = strToInt(transferAmountStr);
                            char *recipientID = readSplit(cLine, lineIndex);
                            
                            AllAccounts = transferFunds(AllAccounts, acct, recipientID, transferAmount);
                            debug_DisplayAccountListings(AllAccounts);
                        }
                        else
                        {
                            // Handle unsupported action
                        }
                    }

                    pthread_mutex_unlock(&lock); // Unlock after accessing shared data
                }
            }

            lineCounter++;
            
            index += len(cLine);
            while (cLine[index] == '\n')
                index++;
        }
        else
        {
            index++;
        }

        if (index >= fSize)
            break;
    }

    // Destroy mutex lock
    pthread_mutex_destroy(&lock);

    return 0;
}
