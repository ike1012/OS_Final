#include "includes.h"

char *concat(char *str1, char *str2)
{
    int L = len(str1) + len(str2);
    char *ret = malloc(L);

    clearStr(ret, L);

    int index = 0;
    for (int i = 0; i < len(str1); i++)
    {
        ret[index] = str1[i];
        index++;
    }
    for (int i = 0; i < len(str2); i++)
    {
        ret[index] = str2[i];
        index++;
    }

    return ret;
}

int len(char *str)
{
    int ret = 0;
    while (str[ret] != '\0')
        ret++;
    return ret;
}

char *readSplit(char *data, int index)
{
    int stopIndex = index;
    while ((data[stopIndex] != ' ') && (stopIndex < len(data)))
        stopIndex++;

    int dataLen = stopIndex - index;
    char *ret = malloc(dataLen + 1);

    clearStr(ret, dataLen + 1);

    int i2 = 0;
    for (int i = index; i < stopIndex; i++)
    {
        ret[i2] = data[i];
        
        i2++;
    }

    if (dataLen > 0)
        return ret;
    else    
        return NULL;
}

char *readLine(char *data, int index, int size)
{
    int stopIndex = index;
    while ((data[stopIndex] != '\n') && (stopIndex < len(data)))
        stopIndex++;

    int lineSize = stopIndex - index;

    if (lineSize > 0)
    {
        char *lineData = malloc(lineSize + 1);
        clearStr(lineData, lineSize + 1);

        int i2 = 0;
        for (int i = index; i < stopIndex; i++)
        {
            lineData[i2] = data[i];

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

char *intToStr(int val)
{

    int L = 0;
    int tmp = val;
    while (tmp != 0)
    {
        tmp /= 10;
        L++;
    }

    char *ret;
    if (val < 0)
    {
        L++;
        ret = malloc(L);
        clearStr(ret, L);
        ret[0] = '-';
    }
    else
    {
        ret = malloc(L);
        clearStr(ret, L);
    }


    tmp = val;
    int tmp2 = val;
    int i = 0;

    if (tmp < 0)
        tmp = 0 - tmp;
    if (tmp2 < 0)
        tmp2 = 0 - tmp2;

    while (tmp != 0)
    {
        tmp2 /= 10;
        tmp2 *= 10;

        int tmp3 = tmp - tmp2;

        ret[(L-1)- i] = byteToChar(tmp3);

        tmp /= 10;
        tmp2 /= 10;
        i++;
    }

    return ret;
}
char byteToChar(int b)
{
    switch (b)
    {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        default:
            return '0';
    }
}

int strToInt(char *str)
{
    int ret = 0;
    int counter = 0;

    int i = len(str) - 1;
    while (i >= 0)
    {
        int v = charToInt(str[i]);

        ret += v * (int)pow((double)10, (double)counter);

        i--;
        counter++;
    }

    return ret;
}
int charToInt(char c)
{
    switch (c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return 0;
    }
}
