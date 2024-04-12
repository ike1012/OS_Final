
typedef struct UserAccount
{

    char ID[10];
    int balance;

    struct UserAccount *next;

} UserAccount;

char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);

UserAccount *createNewAccount(UserAccount *accounts, char *accountID, int startingBalance);
void closeAccount(UserAccount *accounts, char *accountID);
UserAccount *findAccount(UserAccount *accounts, char *accountID);
