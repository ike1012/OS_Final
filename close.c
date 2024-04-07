#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "includes.h"

extern struct UserAccount *AllAccounts;

void closeAccount(char *accountID)
{
    if (AllAccounts == NULL)
        return;

}
