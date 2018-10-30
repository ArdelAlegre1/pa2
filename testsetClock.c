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
void testsetClock() {

  // Declare our struct tInfo to hold our times
  struct timeInfo time;

  // Set the times to all 0 for a zeroed out test
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;
  time.am_pm = 'a'; 
  unsigned long clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x00000061); // 'a' has ascii value 0x61
  printf("%ld\n", clock);

  // // Test some random times
  time.tm_hour = 12;
  time.tm_min = 23;
  time.tm_sec = 50;
  time.am_pm = 'p'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x12235070);
  printf("%ld\n", clock);


  time.tm_hour = 3;
  time.tm_min = 9;
  time.tm_sec = 2;
  time.am_pm = 'p'; 
  clock = 0;
  setClock(&clock, &time);
  TEST(clock == 0x03090270);
  printf("%ld\n", clock);
  
  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testsetClock();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
