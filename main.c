#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pa2.h"
#include "pa2Strings.h"
#include "test.h"

#define FALSE 0
#define TRUE 1
int main( int argc, char *argv[] ) {
    unsigned long clock;
    struct timeInfo time;
    struct tm t;
    int numTicks;
    int startTime;
    char *ptr;
    void *nptr;
    unsigned long interpretTimeErrors;
    errno = FALSE;
    int errors = FALSE;
    if(argc > MAX_ARGS) {
        printf(STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, MIN_HR, MAX_HR,
                    MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], STR_HELP) == FALSE) {
        printf(STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, MIN_HR, MAX_HR,
                    MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
        return EXIT_SUCCESS;
    }
    if(argc > 0) {
        numTicks = strtol(argv[1], &ptr, BASE);
        
        if(errno != FALSE || *ptr != '\0') {
             fprintf(stderr, STR_TICK_PARSE_ERR);
             errors = TRUE;
         }
         else {
            if(rangeCheck(numTicks, MIN_TICKS, MAX_TICKS) == FALSE) {
                fprintf(stderr, STR_TICKS_RANGE_ERR, numTicks, MIN_TICKS, MAX_TICKS);
                errors = TRUE;
            }
         }
         
    }
    else {
        numTicks = DEF_TICKS;
    }

    if(argc > 1) {
        interpretTimeErrors = interpretTime(&time, argv[2]);

        if((interpretTimeErrors & 0x1) == 0x1) {
            fprintf(stderr, STR_TIME_FORMAT_ERR);
            errors = TRUE;
        }
        if((interpretTimeErrors & 0x2) == 0x2) {
            fprintf(stderr, STR_TIME_PARSE_ERR);
            errors = TRUE;
        }
        if((interpretTimeErrors & 0x4) == 0x4) {
            fprintf(stderr, STR_TIME_RANGE_ERR);
            errors = TRUE;
        }
    }
    /*
    else {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        getCurrentTime(&tv, NULL);
        t = *localtime(&tv.sec);
    }
*/
    if(errors == TRUE) {
        printf(STR_USAGE, argv[0], MIN_TICKS, MAX_TICKS, DEF_TICKS, MIN_HR, MAX_HR,
                    MIN_MIN, MAX_MIN, MIN_SEC, MAX_SEC);
        return EXIT_FAILURE;
    }

   

    if(argc < 1) {
        printf(asctime(&t));
        printf("\n");
    }
    setClock(&clock, &time);
    for(int i = 0; i <= numTicks; i++) {
        printClock(&clock);
        tickClock(&clock);
    }
    return EXIT_SUCCESS;


}



