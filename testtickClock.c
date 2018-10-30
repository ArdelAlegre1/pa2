/*
 * Author: Ardel Alegre
 * Userid: cs30fac
 * StudentID: A15752566
 * Description: Unit test program to test the function setClock.s
 * Date: TODO
 * Sources of Help: TODO
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for setClock.s
 *
 * void setClock( const struct tInfo * tmPtr, unsigned char clock[] );
 *
 * The setClock function should set the Binary coded decimal values for the
 * time into our clock arrauy.
 *
 * Purpose: Tests our setClock implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testtickClock() {
    unsigned long clock = 0x10203061;
    tickClock(&clock);
    TEST(clock == 0x10203161);

    clock = 0x05195970;
    tickClock(&clock);
    TEST(clock == 0x05200070);

    clock = 0x09595961;
    tickClock(&clock);
    TEST(clock == 0x10000061);

    clock = 0x11595970;
    tickClock(&clock);
    TEST(clock == 0x12000061);
    printf("%lx\n", clock);

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testtickClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
