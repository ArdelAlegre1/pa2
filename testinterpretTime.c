/*
 * Author: Ardel Alegre
 * Userid: cs30fac
 * StudentID: A15752566
 * Description: Unit test program to test the function 
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
void testinterpretTime() {
    struct timeInfo time;


    char t[] = "12:13:14p";
    printf(t);
    printf("\n");
    TEST(interpretTime(&time, t) == 0x0);
    printf("%lx\n", interpretTime(&time, t));
    TEST(time.tm_hour == 0x12);
    printf("%x\n", time.tm_hour);
    TEST(time.tm_min == 0x13);
    printf("%x\n", time.tm_min);
    TEST(time.tm_sec == 0x14);
    printf("%x\n", time.tm_sec);
    TEST(time.am_pm == 0x70);
    printf("%x\n", time.am_pm);

    char a[]  = "03:05:aA";
    printf(a);
    printf("\n");
    TEST(interpretTime(&time, a) == 0x01);
    printf("%lx\n", interpretTime(&time, a));
    TEST(time.tm_hour == 0x03);
    printf("%x\n", time.tm_hour);
    TEST(time.tm_min == 0x05);
    printf("%x\n", time.tm_min);
    printf("%x\n", time.tm_sec);
    //TEST(time.tm_sec == 0x05);
    //printf("%x\n", time.am_pm);

    char b[]  = "12:03:05b";
    printf(b);
    printf("\n");
    TEST(interpretTime(&time, b) == 0x01);
    printf("%lx\n", interpretTime(&time, b));
    TEST(time.tm_hour == 0x12);
    printf("%x\n", time.tm_hour);
    TEST(time.tm_min == 0x03);
    printf("%x\n", time.tm_min);
    TEST(time.tm_sec == 0x05);
    printf("%x\n", time.tm_sec);
    printf("%x\n", time.am_pm);


    char c[] = "13:13:14a";
    printf(c);
    printf("\n");
    TEST(interpretTime(&time, c) == 0x4);
    printf("%lx\n", interpretTime(&time, c));
    TEST(time.tm_hour != 0x13);
    printf("%x\n", time.tm_hour);
    TEST(time.tm_min == 0x13);
    printf("%x\n", time.tm_min);
    TEST(time.tm_sec == 0x14);
    printf("%x\n", time.tm_sec);
    TEST(time.am_pm == 0x61);
    printf("%x\n", time.am_pm);

    char d[] = "1z0:16y20";
    printf(d);
    printf("\n");
    TEST(interpretTime(&time, d) == 0x1);

    char e[] = "12:03:05a9";
    printf(e);
    printf("\n");
    TEST(interpretTime(&time, e) == 0x1);
    printf("%lx\n", interpretTime(&time, e));
    printf("%c\n", time.am_pm);

    char f[] = "1g2:03:05";
    printf(f);
    printf("\n");
    TEST(interpretTime(&time, f) == 0x3);
    printf("%lx\n", interpretTime(&time, f));

    char g[] = "12a:66:05";
    printf(g);
    printf("\n");
    TEST(interpretTime(&time, g) == 0x7);
    printf("%lx\n", interpretTime(&time, g));
    printf("HOUR:%x\n", time.tm_hour);
    printf("MIN:%x\n", time.tm_min);
    printf("SEC:%x\n", time.tm_sec);

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testinterpretTime();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
