#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // For fork()
#include <sys/wait.h>  // For wait()

typedef struct UserAccount {
    char accountID[8];
    char action[10];
    int balance;
    int amount;
    char targetAccountID[8];
    struct UserAccount *next;
} UserAccount;

UserAccount *AllAccounts;

int main() {
    FILE *inputFile;
    char line[256];
    int numUsers;
    UserAccount transactions[100]; 
    int transactionCount = 0;

    inputFile = fopen("input file.txt", "r"); 
    if (inputFile == NULL) {
        perror("Error could not open file");
        return EXIT_FAILURE;
    }

    if (fgets(line, sizeof(line), inputFile) != NULL) { 
        numUsers = atoi(line);
    }

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char *split = strtok(line, " ");
        strcpy(transactions[transactionCount].accountID, split);

        split = strtok(NULL, " ");
        strcpy(transactions[transactionCount].action, split);

        if (strcmp(transactions[transactionCount].action, "Transfer") == 0) {
            //Setting amount for Transfer
            split = strtok(NULL, " ");
            transactions[transactionCount].amount = atoi(split); 

            split = strtok(NULL, " ");
            strcpy(transactions[transactionCount].targetAccountID, split);
        } 
        else if (strcmp(transactions[transactionCount].action, "Create") == 0 || strcmp(transactions[transactionCount].action, "Deposit") == 0 || strcmp(transactions[transactionCount].action, "Withdraw") == 0) {
            //Setting amount for Deposit, Create, Withdraw
            split = strtok(NULL, " ");
            transactions[transactionCount].amount = atoi(split); 
        }
        // Else INQUIRY or CLOSE

        transactionCount++;
    }

    fclose(inputFile); // Corrected variable name to inputFile

    
    /*
    if (numUsers > 0) {
        for (int i = 0; i < numUsers; i++) {
            pid_t pid = fork();
            if (pid == 0) {
                // Child executes one transaction[i].action
                return 0; 
            }
        }
        while (wait(NULL) > 0);
    } else {
        printf("No transactions parsed.\n");
    }
    */

    return EXIT_SUCCESS;
}

}
