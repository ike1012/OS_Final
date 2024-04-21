#include "includes.h"

pthread_mutex_t threadMutexLock;

int initMutex()
{
    if (pthread_mutex_init(&threadMutexLock, NULL) != 0)
    {
        printf("Failed to initialize mutex lock!\n");
        return -1;
    }

    return 0;
}

void closeMutex()
{
    pthread_mutex_destroy(&threadMutexLock);
}

void lockThreads()
{
     pthread_mutex_lock(&threadMutexLock);
}

void unlockThreads()
{
     pthread_mutex_unlock(&threadMutexLock);
}