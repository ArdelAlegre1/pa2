/*
 * Author: Ardel Alegre
 * UserId: cs30fac
 * StudentID: A15752566
 * Description: tickClock( unsigned long * clock ) This function will increment
 * the clock by one second using incrementBCDValue(). 
 */

#include "pa2.h"
#include <stdio.h>
//#include "pa2Globals.c"

void tickClock( unsigned long * clock) {
    unsigned char* ptr = (unsigned char *) clock;
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    unsigned char ampm;


    hour = ptr[3];
    min = ptr[2];
    sec = ptr[1];
    ampm = ptr[0];

    if (incrementBCDValue(&sec, 0x60, 0x00) == 1) {
        if (incrementBCDValue(&min, 0x60, 0x00) == 1) {
            incrementBCDValue(&hour, 0x13, 0x01);
            if(hour == 0x12) {
                if(ampm == 0x70) {
                    ampm = 0x61;
                } 
                else{
                    ampm = 0x70;
                }
            }
        }
    }


    ptr[3] = hour;
    ptr[2] = min;
    ptr[1] = sec;
    ptr[0] = ampm;
}
