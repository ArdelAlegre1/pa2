/*
 * Author: Ardel Alegre
 * UserId: cs30fac
 * StudentID: A15752566
 * Description: printClock( const unsigned long * clock ) will take the vlaues
 * of the clock long and print out a BCD clock
 */

#include "pa2.h"
#include <stdio.h>
#include "test.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define HOUR_INDEX 3
#define MIN_INDEX 2 
#define SEC_INDEX 1
#define AMPM_INDEX 0
void printClock( const unsigned long * clock ) {
    
    unsigned char * ptr = (unsigned char *) clock;
    unsigned char hour = ptr[HOUR_INDEX];
    unsigned char min = ptr[MIN_INDEX];
    unsigned char sec = ptr[SEC_INDEX];
    unsigned char ampm = ptr[AMPM_INDEX];
    unsigned long * nptr = (unsigned long *) clock;
    
    printf("\n");
    //print top border with ampm value
    for (int i = 1; i <= CLOCK_WIDTH; i++) {
        printChar(ampm);
    }
    printf("\n");
    
    //print binary portion of clock

    for(int i = NUM_BITS_IN_NIBBLE; i >= 1; i--) {
        printf("%c ", CHAR_BORDER);
        for(int j = 6; j >= 1; j--) {
            int shift = 4 * (j+1) + (i-1);
            int bitmask = 0x1;
            bitmask = bitmask << shift;
            bitmask = bitmask & *clock;
            bitmask = bitmask >> shift;
            if(bitmask == 1) {
                printChar(CHAR_BIT_SET);
            } else {
                printChar(CHAR_BIT_UNSET);
            }
            if(j == 5 || j == 3) {
                printChar(CHAR_SPACER);
            }

        }
        printf(" %c\n", CHAR_BORDER);
    }

    //prints the numeric time
    printf("%c ", CHAR_BORDER);
    printf("%x", hour / BASE);
    printf("%x", hour % BASE);
    printChar(CHAR_SPACER);
    printf("%x", min / BASE);
    printf("%x", min % BASE);
    printChar(CHAR_SPACER);
    printf("%x", sec / BASE);
    printf("%x", sec % BASE);
    printf(" %c\n", CHAR_BORDER);

    //prints bottom bordr with ampm value
    for (int i = 1; i <= CLOCK_WIDTH; i++) {
        printChar(ampm);
    }
    printf("\n");



}
