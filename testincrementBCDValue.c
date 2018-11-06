/*
 * Author: Ardel Alegre
 * Userid: cs30fac
 * StudentID: A15752566
 * Description: Unit test program to test the function incrementBCDValues
 */ 

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for incrementBCDValues.s
 *
 * incrementBCDValues( unsigned char* BCDdigits, const unsigned char
 * resetThreshold, const unsigned char resetValue  );
 *
 * The incrementBCDValue function should take BCDdigits and inrement them by
 * one.
 *
 * Purpose: Tests our incrementBCDValue implementation by passing a variety of values
 * in as test cases for our function. Tests edge cases like 0:0:0 times, larger
 * times, and others.
 */
void testincrementBCDValue() {
   
   //testing for transition from 12 -> 1
   unsigned char BCDdigits = 0x12;
   unsigned char resetThreshold = 0x13;
   unsigned char resetValue = 0x1;
   TEST(incrementBCDValue(&BCDdigits, resetThreshold, resetValue) == 1);
   TEST(BCDdigits == 0x1);
 
   //testing for 12 -> 13
   BCDdigits = 0x12;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x13);

   //testing for 19 -> 20
   BCDdigits = 0x19;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x20);

   //testing for 59 -> 0
   BCDdigits = 0x59;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x00);

   //testing for 0 -> 1
   BCDdigits = 0x00;
   resetThreshold = 0x60;
   resetValue = 0x0;
   incrementBCDValue(&BCDdigits, resetThreshold, resetValue);
   TEST(BCDdigits == 0x01);

}

int main( void ) {

  fprintf(stderr, "Running tests for setClock...\n");
  testincrementBCDValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
