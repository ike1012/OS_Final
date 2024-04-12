#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep function
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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

// Shared memory structure
typedef struct {
    pthread_mutex_t mutex;
    TransactionDetails transactions[3]; // Assuming 3 transactions
} SharedMemory;

int main() {
    // Create shared memory segment
    key_t key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(key, sizeof(SharedMemory), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory segment
    SharedMemory* shared_memory = (SharedMemory*)shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize mutex in shared memory
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&(shared_memory->mutex), &attr);

    // Simulate transaction details
    TransactionDetails transaction1;
    strcpy(transaction1.transaction_type, "Withdraw");
    strcpy(transaction1.account_id, "A332131");
    transaction1.amount = 40;
    strcpy(transaction1.target_account_id, "");
    strcpy(transaction1.status, "Pending");
    strcpy(transaction1.timestamp, "");

    TransactionDetails transaction2;
    strcpy(transaction2.transaction_type, "Create");
    strcpy(transaction2.account_id, "A342131");
    transaction2.amount = 40;
    strcpy(transaction2.target_account_id, "");
    strcpy(transaction2.status, "Pending");
    strcpy(transaction2.timestamp, "");

    TransactionDetails transaction3;
    strcpy(transaction3.transaction_type, "Transfer");
    strcpy(transaction3.account_id, "A342131");
    transaction3.amount = 40;
    strcpy(transaction3.target_account_id, "A382131");
    strcpy(transaction3.status, "Pending");
    strcpy(transaction3.timestamp, "");

    // Acquire mutex in shared memory
    pthread_mutex_lock(&(shared_memory->mutex));
    printf("Main process acquired shared memory mutex\n");

    // Write transaction details to shared memory
    shared_memory->transactions[0] = transaction1;
    shared_memory->transactions[1] = transaction2;
    shared_memory->transactions[2] = transaction3;

    // Release mutex in shared memory
    pthread_mutex_unlock(&(shared_memory->mutex));
    printf("Main process released shared memory mutex\n");

    // Detach shared memory segment
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Destroy shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
