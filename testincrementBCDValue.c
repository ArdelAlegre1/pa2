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
void testincrementBCDValue() {
   unsigned char BCDdigits = 0x12;
   unsigned char resetThreshold = 0x13;
   unsigned char resetValue = 0x1;
   TEST(incrementBCDValue(&BCDdigits, resetThreshold, resetValue) == 1);
   TEST(BCDdigits == 0x1);
   printf("0x%x\n", BCDdigits);
   printf("%d\n", incrementBCDValue(&BCDdigits, resetThreshold, resetValue));

   BCDdigits = 0x12;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x13);
   printf("0x%x\n", BCDdigits);
   printf("%d\n", incrementBCDValue(&BCDdigits, resetThreshold, resetValue));

   BCDdigits = 0x19;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x20);
   printf("0x%x\n", BCDdigits);
   printf("%d\n", incrementBCDValue(&BCDdigits, resetThreshold, resetValue));

   BCDdigits = 0x59;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x00);
   printf("0x%x\n", BCDdigits);
   printf("%d\n", incrementBCDValue(&BCDdigits, resetThreshold, resetValue));

   BCDdigits = 0x00;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x01);
   printf("0x%x\n", BCDdigits);
   printf("%d\n", incrementBCDValue(&BCDdigits, resetThreshold, resetValue));

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testincrementBCDValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
