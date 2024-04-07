
typedef struct
{

    char ID[10];
    int balance;

    struct UserAccount *next;

} UserAccount;

char *readLine(char *data, int index, int size);
void clearStr(char *str, int len);
int len(char *str);

void createNewAccount(char *accountID, int startingBalance);
