#include "includes.h"
UserAccount *transferFunds(UserAccount *accounts, char *senderID, char *recipientID, int amount)
{
    UserAccount *sender = findAccount(accounts, senderID);
    UserAccount *recipient = findAccount(accounts, recipientID);

    // Check if both sender and recipient accounts exist
    if (sender == NULL || recipient == NULL)
    {
        printf("Transfer failed: Sender or recipient account not found.\n");
        return accounts; // No changes to accounts list
    }

    // Check if sender has sufficient balance
    if (sender->balance < amount)
    {
        printf("Transfer failed: Insufficient funds in sender's account.\n");
        return accounts; // No changes to accounts list
    }

    // Transfer funds
    sender->balance -= amount;
    recipient->balance += amount;
    printf("Transfer successful: $%d transferred from account %s to account %s\n", amount, senderID, recipientID);
    return accounts;
}
