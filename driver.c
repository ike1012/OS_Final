#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "includes.h"

struct UserAccount *AllAccounts;

int main(char *args)
{
    int sel;
    AllAccounts = NULL;

    char *inputFileName = "inputFile.txt";
    

    // Open input file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    int fSize = 0;

    if (inputFile == NULL)
    {
        printf("Input file not found.\n");
        exit(0);
    }

    // Get the file size
    fseek(inputFile, 0, SEEK_END);
    fSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Read the file contents
    char *fData = malloc(fSize);
    fread(fData, fSize, 1, inputFile);

    // Close the file
    fclose(inputFile);

    printf("Parsing input file (Size %d)...\n", fSize);
    int index = 0;
    
    // Replace all \r's with \n's
    for (int i = 0; i < fSize; i++)
    {
        if (fData[i] == '\r')
            fData[i] = '\n';
    }

    char *cLine = readLine(fData, index, fSize);
    int lineCounter = 0;
    while (cLine != NULL)
    {
        cLine = readLine(fData, index, fSize);
        if (cLine != NULL)
        {
            //printf("%d (len: %d): %s\n", lineCounter, len(cLine), cLine);
            /*
            
                Do stuff right here with the line to parse individual parts
                Structure is as follows:
                    Line 0: Total Accounts
                    Line 1+: {AccountID} {Action} {Value} {AltAccountID}
            
            */

            lineCounter++;
            
            index += len(cLine) + 1;
        }
        else
        {
            index++;
        }

        if (index >= fSize)
            break;
    }


}

int len(char *str)
{
    int ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}

char *readLine(char *data, int index, int size)
{
    int i = index;
    while ((data[i] != '\n') && (i < size))
        i++;

    int lineSize = i - index;
    if (lineSize > 0)
    {
        char *lineData = malloc(lineSize + 1);
        clearStr(lineData, lineSize + 1);

        int i2 = 0;
        for (i = index; i < (index + lineSize); i++)
        {
            lineData[i2] = data[i];
            lineData[i2 + 1] = '\0';

            i2++;
        }

        return lineData;
    }
    else
        return NULL;
}

void clearStr(char *str, int len)
{
    for (int i = 0; i < len; i++)
        str[i] = '\0';
}
