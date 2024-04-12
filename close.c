#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "includes.h"

void closeAccount(UserAccount *accounts, char *accountID)
{
    // Make sure we have accounts first
    if (accounts == NULL)
        return;

    // Need action for closing

}
