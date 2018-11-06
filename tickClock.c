/*
 * Author: Ardel Alegre
 * UserId: cs30fac
 * StudentID: A15752566
 * Description: tickClock( unsigned long * clock ) This function will increment
 * the clock by one second using incrementBCDValue(). 
 */

#include "pa2.h"
#include <stdio.h>
#define HOUR_INDEX 3
#define MIN_INDEX 2
#define SEC_INDEX 1
#define AMPM_INDEX 0
#define AMPM_HOUR_CHANGE 0x12
#define RETURNED_RESET 1
void tickClock( unsigned long * clock) {
    //create pointer to chars instead of individual digits
    unsigned char* ptr = (unsigned char *) clock;
    //declare values
    unsigned char hour = ptr[HOUR_INDEX];
    unsigned char min = ptr[MIN_INDEX];
    unsigned char sec = ptr[SEC_INDEX];
    unsigned char ampm = ptr[AMPM_INDEX];

    //increments seconds
    if (incrementBCDValue(&sec, SEC_THRESHOLD, SEC_RESERT) == RETURNED_RESET) {
        //if seconds resets to 0 increment mins
        if (incrementBCDValue(&min, MIN_THRESHOLD, MIN_RESERT) == RETURNED_RESET) {
            //if mins resets to 0 increment hours
            incrementBCDValue(&hour, HR_THRESHOLD, HR_RESET);
            //if hours increments to 12 change ampm
            if(hour == AMPM_HOUR_CHANGE) {
                if(ampm == AM_VALUE) {
                    ampm = PM_VALUE;
                } 
                else{
                    ampm = AM_VALUE;
                }
            }
        }
    }

    //update pointers
    ptr[HOUR_INDEX] = hour;
    ptr[MIN_INDEX] = min;
    ptr[SEC_INDEX] = sec;
    ptr[AMPM_INDEX] = ampm;
}
