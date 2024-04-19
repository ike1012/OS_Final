#include "includes.h"

int fileExists(char *fileName)
{
    FILE * f = fopen(fileName, "r");

    if (f == NULL)
        return -1;

    fclose(f);
    return 0;
}

char *readFile(char *fileName)
{
    FILE * f = fopen(fileName, "r");

    if (f == NULL)
        return NULL;


    // Get the file size
    fseek(f, 0, SEEK_END);
    int fSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Read the file contents
    char *fData = malloc(fSize);
    fread(fData, fSize, 1, f);

    // Close the file
    fclose(f);

    return fData;
}

int fileSize(char *fileName)
{
    FILE * f = fopen(fileName, "r");

    if (f == NULL)
        return -1;

    // Get the file size
    fseek(f, 0, SEEK_END);
    int fSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    fclose(f);

    return fSize;
}

int writeFile(char *fileName, char *fileData)
{
    FILE * f = fopen(fileName, "w");

    if (f == NULL)
    {
        printf("writeFile: ERROR! COULD NOT WRITE FILE %s\n", fileName);
        return -1;
    }

    fwrite(fileData, 1, len(fileData), f);

    fclose(f);

    return 0;
}