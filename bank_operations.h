#ifndef BANK_OPERATIONS_H
#define BANK_OPERATIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// Define the structure to hold all the accounts as a linked list
typedef struct UserAccount {
    char ID[10];
    int balance;
    struct UserAccount *next;
} UserAccount;

// Main functions to handle the actions with the accounts
UserAccount *createNewAccount(UserAccount *accounts, char *accountID, int startingBalance);
UserAccount *closeAccount(UserAccount *accounts, char *accountID);
UserAccount *findAccount(UserAccount *accounts, char *accountID);
// Function prototype for withdrawing funds
UserAccount *withdrawFunds(UserAccount *accounts, char *accountID, int amount);
// Function prototype for depositing funds
UserAccount *depositFunds(UserAccount *accounts, char *accountID, int amount);
// Function prototype for transferring funds
UserAccount *transferFunds(UserAccount *accounts, char *senderID, char *recipientID, int amount);
// Function prototype for checking account balance
void checkBalance(UserAccount *accounts, char *accountID);
// Various string-related functions to make life easier
char *readSplit(char *data, int index);
char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);
int strToInt(char *str);
int charToInt(char c);

// Debug functions
void debug_DisplayAccountListings(UserAccount *accounts);

#endif /* BANK_OPERATIONS_H */
