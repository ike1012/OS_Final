#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep function

// Define mutexes for resource synchronization
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t shared_memory_mutex = PTHREAD_MUTEX_INITIALIZER;

// Define a structure to represent transaction details
typedef struct {
    char transaction_type[20];
    char account_id[10];
    int amount;
    char target_account_id[10];
    char status[20];
    char timestamp[20];
} TransactionDetails;

// Function to perform transactions
void* perform_transaction(void* arg) {
    // Obtain transaction details from arguments
    TransactionDetails* transaction = (TransactionDetails*)arg;

    // Acquire file mutex to access file system
    pthread_mutex_lock(&file_mutex);
    printf("Thread %s acquired file mutex to perform transaction\n", transaction->account_id);

    // Simulate accessing file system
    // Perform transaction operations like deposit, withdraw, etc.

    // Release file mutex
    pthread_mutex_unlock(&file_mutex);
    printf("Thread %s released file mutex\n", transaction->account_id);

    // Acquire shared memory mutex to update transaction status
    pthread_mutex_lock(&shared_memory_mutex);
    printf("Thread %s acquired shared memory mutex to update transaction status\n", transaction->account_id);

    // Simulate updating shared memory with transaction status
    // Update transaction status, timestamp, etc.

    // Release shared memory mutex
    pthread_mutex_unlock(&shared_memory_mutex);
    printf("Thread %s released shared memory mutex\n", transaction->account_id);

    // Free memory allocated for transaction details
    free(transaction);

    return NULL;
}

int main() {
    // Create threads to perform transactions
    pthread_t threads[3]; // Assuming 3 transactions for demonstration

    // Simulated transaction details
    TransactionDetails* transaction1 = malloc(sizeof(TransactionDetails));
    strcpy(transaction1->transaction_type, "Withdraw");
    strcpy(transaction1->account_id, "A332131");
    transaction1->amount = 40;
    strcpy(transaction1->target_account_id, "");
    strcpy(transaction1->status, "Pending");
    strcpy(transaction1->timestamp, "");

    TransactionDetails* transaction2 = malloc(sizeof(TransactionDetails));
    strcpy(transaction2->transaction_type, "Create");
    strcpy(transaction2->account_id, "A342131");
    transaction2->amount = 40;
    strcpy(transaction2->target_account_id, "");
    strcpy(transaction2->status, "Pending");
    strcpy(transaction2->timestamp, "");

    TransactionDetails* transaction3 = malloc(sizeof(TransactionDetails));
    strcpy(transaction3->transaction_type, "Transfer");
    strcpy(transaction3->account_id, "A342131");
    transaction3->amount = 40;
    strcpy(transaction3->target_account_id, "A382131");
    strcpy(transaction3->status, "Pending");
    strcpy(transaction3->timestamp, "");

    // Create threads for each transaction
    pthread_create(&threads[0], NULL, perform_transaction, (void*)transaction1);
    pthread_create(&threads[1], NULL, perform_transaction, (void*)transaction2);
    pthread_create(&threads[2], NULL, perform_transaction, (void*)transaction3);

    // Wait for threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&file_mutex);
    pthread_mutex_destroy(&shared_memory_mutex);

    return 0;
}
