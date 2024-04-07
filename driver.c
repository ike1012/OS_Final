#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct
{

    char ID[10];
    int balance;

    struct UserAccount *next;

} UserAccount;

typedef struct {

    char accountID[10];
    char action[10];
    int amount; 
    char targetAccountID[10]; 

} Transaction;

struct UserAccount *AllAccounts;

char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);

int main(char *args)
{
    int sel;
    AllAccounts = NULL;

   char *inputFileName = "/uploads/input file.txt";
      FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Input file not found.\n");
        exit(EXIT_FAILURE);
    }

    //get numUsers from line 1
    int numUsers;
    fscanf(inputFile, "%d\n", &numUsers); 
    printf("Total Accounts: %d\n", numUsers);

    Transaction tx;
    int lineCounter = 1; 
    //parse file to get each transactions accountID action amount, and if a transfer, target accountID
    while (fscanf(inputFile, "%9s %9s %d %9s", tx.accountID, tx.action, &tx.amount, tx.targetAccountID) != EOF) {
        if (strcmp(tx.action, "Inquiry") == 0 || strcmp(tx.action, "Close") == 0) {
            tx.amount = 0; 
            tx.targetAccountID[0] = '\0'; 
        }
        lineCounter++; 
        memset(&tx, 0, sizeof(Transaction));
    }

    fclose(inputFile); 



}

int len(char *str)
{
    int ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}

char *readLine(char *data, int index, int size)
{
    int i = index;
    while ((data[i] != '\n') && (i < size))
        i++;

    int lineSize = i - index;
    if (lineSize > 0)
    {
        char *lineData = malloc(lineSize + 1);
        clearStr(lineData, lineSize + 1);

        int i2 = 0;
        for (i = index; i < (index + lineSize); i++)
        {
            lineData[i2] = data[i];
            lineData[i2 + 1] = '\0';

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
