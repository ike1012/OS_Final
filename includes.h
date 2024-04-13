#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct UserAccount
{

    char ID[10];
    int balance;

    struct UserAccount *next;

} UserAccount;

char *readSplit(char *data, int index);
char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);
int strToInt(char *str);
int charToInt(char c);

void debug_DisplayAccountListings(UserAccount *accounts);

UserAccount *createNewAccount(UserAccount *accounts, char *accountID, int startingBalance);
UserAccount *closeAccount(UserAccount *accounts, char *accountID);
UserAccount *findAccount(UserAccount *accounts, char *accountID);
