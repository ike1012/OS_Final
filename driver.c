#include "includes.h"

struct UserAccount *AllAccounts;

int main(char *args)
{
    int sel;
    AllAccounts = NULL;

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
        //printf("cLine: {%s}\n", cLine);
        if (cLine != NULL)
        {
            //printf("%d (len: %d): %s\n", lineCounter, len(cLine), cLine);
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
                    //printf("[%d] %d\t{%s}\n", lineCounter, len(cLine), cLine);

                    char *acct = readSplit(cLine, lineIndex);
                    lineIndex += len(acct) + 1;

                    char *action = readSplit(cLine, lineIndex);
                    lineIndex += len(action) + 1;

                    printf("acct: %s -> action: %s\n", acct, action);

                    // Check if the account exists before performing any actions
                    if (findAccount(AllAccounts, acct) == NULL)
                    {
                        if (strcmp(action, "Create") == 0)  //----------------------- Create account
                        {
                            // Create account here

                            char *startingBalance = readSplit(cLine, lineIndex);
                            int bal = strToInt(startingBalance);

                            UserAccount *newAccount = createNewAccount(AllAccounts, acct, bal);
                            if (AllAccounts == NULL)
                                AllAccounts = newAccount;

                            debug_DisplayAccountListings(AllAccounts);
                        }
                        else
                        {
                            // Attempting account action on non-existent account
                            printf("Account \'%s\' doesn't exist!\n", acct);
                        }
                    }
                    else
                    {
                        // Account exists, check what action is being performed
                        if (strcmp(action, "Create") == 0) //----------------------- Create Account ERROR Account Already Exists!
                        {
                            // Attempting account creation when account already exists, throw 
                            // error out to the screen.
                            printf("Account \'%s\' already exists!\n", acct);
                        }
                        else if (strcmp(action, "Close") == 0) //----------------------- Close Account
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
                        else if (strcmp(action, "Withdraw") == 0) //----------------------- Withdraw Funds
                        {
                            char *withdrawAmountStr = readSplit(cLine, lineIndex);
                            int withdrawAmount = strToInt(withdrawAmountStr);

                            AllAccounts = withdrawFunds(AllAccounts, acct, withdrawAmount);
                            debug_DisplayAccountListings(AllAccounts);
                        }

                        else if (strcmp(action, "Deposit") == 0) //----------------------- Deposit Funds
                        {
                            char *depositAmountStr = readSplit(cLine, lineIndex);
                            int depositAmount = strToInt(depositAmountStr);

                            AllAccounts = depositFunds(AllAccounts, acct, depositAmount);
                            debug_DisplayAccountListings(AllAccounts);
                        }

                        else if (strcmp(action, "Inquiry") == 0) //----------------------- Inquire Funds
                        {
                            checkBalance(AllAccounts, acct);
                        }

                        else if (strcmp(action, "Transfer") == 0) //----------------------- Transfer Funds
                        {
                            char *transferAmountStr = readSplit(cLine, lineIndex);
                            int transferAmount = strToInt(transferAmountStr);
                            char *recipientID = readSplit(cLine, lineIndex);
                            
                            AllAccounts = transferFunds(AllAccounts, acct, recipientID, transferAmount);
                            debug_DisplayAccountListings(AllAccounts);
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


}

UserAccount *findAccount(UserAccount *accounts, char *accountID)
{
    if (accounts == NULL)
        return NULL;

    if (strcmp(accounts->ID, accountID) == 0)
        return accounts;

    struct UserAccount *ua = accounts->next;
    while (ua != NULL)
    {
        if (strcmp(ua->ID, accountID) == 0)
            return accounts;

        ua = ua->next;
    }
    return NULL;
}


int len(char *str)
{
    int ret = 0;
    while (str[ret] != '\0')
        ret++;
    return ret;
}

char *readSplit(char *data, int index)
{
    int stopIndex = index;
    while ((data[stopIndex] != ' ') && (stopIndex < len(data)))
        stopIndex++;

    int dataLen = stopIndex - index;
    char *ret = malloc(dataLen + 1);

    clearStr(ret, dataLen + 1);

    int i2 = 0;
    for (int i = index; i < stopIndex; i++)
    {
        ret[i2] = data[i];
        
        i2++;
    }

    if (dataLen > 0)
        return ret;
    else    
        return NULL;
}

char *readLine(char *data, int index, int size)
{
    int stopIndex = index;
    while ((data[stopIndex] != '\n') && (stopIndex < len(data)))
        stopIndex++;

    int lineSize = stopIndex - index;

    if (lineSize > 0)
    {
        char *lineData = malloc(lineSize + 1);
        clearStr(lineData, lineSize + 1);

        int i2 = 0;
        for (int i = index; i < stopIndex; i++)
        {
            lineData[i2] = data[i];

            i2++;
        }

        return lineData;
    }  
    else
        return NULL;
}

void clearStr(char *str, int len)
{
    for (int i = 0; i < len; i++)
        str[i] = '\0';
}

int strToInt(char *str)
{
    int ret = 0;
    int counter = 0;

    int i = len(str) - 1;
    while (i >= 0)
    {
        int v = charToInt(str[i]);

        ret += v * (int)pow((double)10, (double)counter);

        i--;
        counter++;
    }

    return ret;
}
int charToInt(char c)
{
    switch (c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return 0;
    }
}

void debug_DisplayAccountListings(UserAccount *accounts)
{
    printf("\n\n");
    if (accounts == NULL)
    {
        printf("DEBUG: Accounts listings is empty.");
        return;
    }

    printf("DEBUG DISPLAY: ACCOUNT LISTINGS\n");
    printf("\tAccount ID: %s\n", accounts->ID);
    printf("\t\tBalance: %d\n", accounts->balance);

    UserAccount *ua = accounts->next;
    while (ua != NULL)
    {
        printf("\tAccount ID: %s\n", ua->ID);
        printf("\t\tBalance: %d\n", ua->balance);
        ua = ua->next;
    }
    
    printf("\n\n");
}
