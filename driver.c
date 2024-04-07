#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

//#include "create.c"

int main()
{
    int sel;
    
    while (1)
    {
        printf("Welcome to the banking application.\n");
        printf("1. Create an Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer Balance\n");
        printf("5. Balance Inquiry\n");
        printf("6. Close an Account\n");
        printf("7. Exit\n");

        printf("\nEnter selection: ");
        scanf("%d", &sel);
        printf("\n");

        switch (sel)
        {
            case 1: // --------------------------- Create Account
                printf("Not implemented yet.");
                break;
            case 2: // --------------------------- Deposit
                printf("Not implemented yet.");
                break;
            case 3: // --------------------------- Withdraw
                printf("Not implemented yet.");
                break;
            case 4: // --------------------------- Transfer Balance
                printf("Not implemented yet.");
                break;
            case 5: // --------------------------- Balance Inquiry
                printf("Not implemented yet.");
                break;
            case 6: // --------------------------- Close an Account
                printf("Not implemented yet.");
                break;
            case 7: // --------------------------- Exit
                exit(0);
                break;
            default:
                printf("Invalid selection.");
        }
    }
}
