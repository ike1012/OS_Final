// All of the important headers to include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Define the structure to hold all the accounts as a linked list
typedef struct UserAccount
{

    char ID[10];
    int balance;

    struct UserAccount *next;

} UserAccount;

// Main functions to handle the actions with the accounts
UserAccount *createNewAccount(UserAccount *accounts, char *accountID, int startingBalance);
UserAccount *closeAccount(UserAccount *accounts, char *accountID);
UserAccount *findAccount(UserAccount *accounts, char *accountID);

// Various string-related functions to make life easier
char *readSplit(char *data, int index);
char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);
int strToInt(char *str);
int charToInt(char c);

// Debug functions
void debug_DisplayAccountListings(UserAccount *accounts);
