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
#include <sys/stat.h>
#include <sys/mman.h>
#include <wait.h>

// Define the structure to hold the process to a specific user account
typedef struct UserProcess
{
    char ID[10];
    pid_t pID;

} UserProcess;

// Define a structure to represent transaction details
typedef struct TransactionDetails
{
    char transactionType[10];
    char accountID[10];
    int amount;
    char targetID[10];
    char status[10];
    time_t timeStamp;

    struct TransactionDetails *next;
} TransactionDetails;

// Main functions to handle the actions with the accounts
int createNewAccount(char *accountID, int startingBalance);
int closeAccount(char *accountID);
int depositIntoAccount(char *accountID, int balance);
int withdrawFromAccount(char *accountID, int balance);
int inquireAccount(char *accountID);
int transferFunds(char *acctFrom, char *acctTo, int balance);

// Various string-related functions to make life easier
char *concat(char *str1, char *str2);
void copy(char *dst, char *src);
char *readSplit(char *data, int index);
char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);
char *intToStr(int val);
char byteToChar(int b);
int strToInt(char *str);
int charToInt(char c);

// File functions
int fileExists(char *fileName);
char *readFile(char *fileName);
int fileSize(char *fileName);
int writeFile(char *fileName, char *fileData);

// Inter-Process Communication
int initSharedMemory();
int logTransaction(char *acctID, char *transType, int ammount, char *targetID, char *status);
void displayTransactionLogs();

// Mutex thread locking
int initMutex();
void closeMutex();
void lockThreads();
void unlockThreads();