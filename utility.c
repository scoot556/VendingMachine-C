/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

unsigned getNumLength(unsigned length) {
   int temp = length;
   length = 0;

   while((double) temp / 10 > 0) {
      length++;
      if ((double) temp / 10 < 1) {
         break;
      }
      temp /= 10;
   }

   return length;
}