/*
 * Author: Ardel Alegre
 * Userid: cs30fac
 * StudentID: A15752566
 * Description: Unit test program to test the function tickClock.c
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for tickClock.c
 *
 * void tickClock( unsigned long * clock );
 *
 * The tickClock.c function should use incrementBCDValue to increment the
 * seconds value of time and update mins, hours, or ampm value when needed.
 *
 * Purpose: Tests our tickClock.c implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 11:59:59p ->
 * 12:00:00a.
 */
void testtickClock() {
    //10:0:30a -> 10:20:31a
    unsigned long clock = 0x10203061;
    tickClock(&clock);
    TEST(clock == 0x10203161);

    //05:19:59p -> 05:20:00p
    clock = 0x05195970;
    tickClock(&clock);
    TEST(clock == 0x05200070);

    //09:59:59a -> 10:00:00a
    clock = 0x09595961;
    tickClock(&clock);
    TEST(clock == 0x10000061);

    //11:59:59p -> 12:00:00a
    clock = 0x11595970;
    tickClock(&clock);
    TEST(clock == 0x12000061);
}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testtickClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
