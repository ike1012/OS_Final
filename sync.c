#include "bank_operations.h"

// Define a mutex lock to synchronize access to shared resources
pthread_mutex_t lock;

// Function to initialize mutex lock
void initializeLock() {
    pthread_mutex_init(&lock, NULL);
}

// Function to destroy mutex lock
void destroyLock() {
    pthread_mutex_destroy(&lock);
}

// Function to perform inquiry operation
void checkBalance(UserAccount *accounts, char *accountID) {
    // Lock mutex before accessing shared resources
    pthread_mutex_lock(&lock);

    // Find the account
    UserAccount *current = findAccount(accounts, accountID);

    // If account is not found
    if (current == NULL) {
        printf("Account \"%s\" not found.\n", accountID);
    } else {
        // Display account balance
        printf("Account ID: %s, Balance: %d\n", current->ID, current->balance);
    }

    // Unlock mutex after accessing shared resources
    pthread_mutex_unlock(&lock);
}
