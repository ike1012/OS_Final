#include "includes.h"

// Declare the process array
struct UserProcess **Processes;

pid_t mainThreadPID;
int mainReady;

int main(char *args)
{
    mainThreadPID = getpid();
    printf("MAIN THREAD: %d\n", mainThreadPID);


    //-------------------------------------------------- Set up the shared memory for transaction details
    if (initSharedMemory() < 0)
    {
        printf("Failed to initialize the shared memory\n");
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------- Read input file

    char *inputFileName = "inputFile.txt";
    
    if (fileExists(inputFileName) < 0)
    {
        printf("Input file not found.\n");
        exit(0);
    }

    int fSize = fileSize(inputFileName);
    char *fData = readFile(inputFileName);

    //-------------------------------------------------- Initialize user account directory

    int dirRet = mkdir("accounts", 0777);
    printf("Initializing directory %d\n", dirRet);

    printf("Parsing input file (Size %d)...\n", fSize);
    
    // Replace all \r's with \n's
    for (int i = 0; i < fSize; i++)
    {
        if (fData[i] == '\r')
            fData[i] = '\n';
    }

    //-------------------------------------------------- Read 1st line of inputFile for user process count
    int index = 0;
    char *cLine = readLine(fData, index, fSize);
    int lineCounter = 0;

    int processCount = strToInt(cLine);

    printf("Preparing [%d] processes...\n", processCount);
    
    //-------------------------------------------------- Initialize processes database
    Processes = malloc(sizeof(struct UserProcess) * processCount);
    for (int i = 0; i < processCount; i++)
    {
        Processes[i] = malloc(sizeof(struct UserProcess));
        clearStr(Processes[i]->ID, 10);
        Processes[i]->pID = -1;
    }

    mainReady = 0;
    printf("Preparing links for processes...\n");
    
    //-------------------------------------------------- Create the processes
    int pIndex = -1;
    pid_t forked_pid = 0;

    if (forked_pid == 0)
    {
        for (int i = 0; i < processCount; i++)
        {
            int tmpI = 0;
            int LC = 0;
            int goNext = 0;

            while ((tmpI < fSize) && (goNext == 0))
            {
                cLine = readLine(fData, tmpI, fSize);
                if (cLine != NULL)
                {
                    
                    if (LC > 0) // Make sure we aren't on the first line that has the accounts count
                    {
                        char *acct = readSplit(cLine, 0);
                        if (i == 0)
                        {
                            printf("linking ID %s to sub-process %d\n", acct, i);
                            strcpy(Processes[i]->ID, acct);
                            goNext = 1;
                        }
                        else
                        {
                            int canUse = 1;
                            for (int i2 = 0; i2 < i; i2++)
                            {
                                if (strcmp(Processes[i2]->ID, acct) == 0) // Check for existing ID link
                                    canUse = 0;
                            }

                            if (canUse == 1)
                            {
                                printf("linking ID %s to sub-process %d\n", acct, i);
                                strcpy(Processes[i]->ID, acct);
                                goNext = 1;
                            }
                        }
                    }

                    LC++;

                    tmpI += len(cLine);
                    while (cLine[tmpI] == '\n')
                        tmpI++;
                } 
                else
                {
                    tmpI++;
                }

                if (tmpI >= fSize)
                    break;
            }
        }

        mainReady = 1;
    }
    
    printf("Forking processes...\n");

    for (int i = 0; i < processCount; i++)
    {
        if (forked_pid == 0)
        {
            forked_pid = fork();
            //printf("pid fork [%d/%d]: %d\n", i, processCount, forked_pid);
            //-------------------------------------------------- Index each process in the database
            if ((forked_pid != 0) && (forked_pid != mainThreadPID))
            {
                pIndex = i;
                Processes[i]->pID = forked_pid;
                break;
            }
        }
    }


    if (forked_pid != mainThreadPID)
    {
        printf("Process Operation: %d\tIndex: %d\tAccount ID: %s\n", forked_pid, pIndex, Processes[pIndex]->ID);
    }

    while ((index < fSize) && (forked_pid != 0))
    {
        cLine = readLine(fData, index, fSize);
        
        if (cLine != NULL)
        {
            /*
            
                Do stuff right here with the line to parse individual parts
                Structure is as follows:
                    Line 0: Total Accounts
                    Line 1+: {AccountID} {Action} {Value} {AltAccountID}
            
            */


            if (lineCounter > 0) // Make sure we aren't on the first line that has the accounts count
            {
                int lineIndex = 0;

                if (len(cLine) > 0)
                {
                    char *acct = readSplit(cLine, lineIndex);
                    lineIndex += len(acct) + 1;

                    char *action = readSplit(cLine, lineIndex);
                    lineIndex += len(action) + 1;

                    //printf("acct: %s -> action: %s\n", acct, action);

                    if (strcmp(Processes[pIndex]->ID, acct) == 0) // Only allow the thread to operate with it's own account
                    {

                        if (strcmp(action, "Create") == 0) //----------------------- Create Account
                        {

                            int startingBalance = strToInt(readSplit(cLine, lineIndex));
                            printf("Process %d, AccountID [%s]: Create-> start with %d\n", forked_pid, Processes[pIndex]->ID, startingBalance);
                            int r = createNewAccount(acct, startingBalance);
                            if (r == 0)
                                printf("Process %d, AccountID [%s]: Create-> Created Successfully!\n", forked_pid, Processes[pIndex]->ID);
                            else
                                printf("Create returned %d\n", r);

                        }
                        else if (strcmp(action, "Close") == 0) //----------------------- Close Account
                        {
                            printf("Process %d, AccountID [%s]: Close\n", forked_pid, Processes[pIndex]->ID);
                            int r = closeAccount(acct);
                            if (r == 0)
                                printf("Process %d, AccountID [%s]: Closed Successfully!\n", forked_pid, Processes[pIndex]->ID);
                        }
                        else if (strcmp(action, "Withdraw") == 0) //----------------------- Withdraw Funds
                        {

                        }
                        else if (strcmp(action, "Deposit") == 0) //----------------------- Deposit Funds
                        {

                        }
                        else if (strcmp(action, "Inquiry") == 0) //----------------------- Inquire Funds
                        {

                        }
                        else if (strcmp(action, "Transfer") == 0) //----------------------- Transfer Funds
                        {

                        }
                        else
                        {

                        }

                        
                    }
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


    // Wait for all processes to complete before exiting
    if (getpid() == mainThreadPID)
    {
        for (int i = 0; i < processCount; i++)
        {
            int r;
            waitpid(Processes[i]->pID, &r, 0);
        }
        
        displayTransactionLogs();
    }

}

