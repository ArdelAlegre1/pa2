/*
 * Author: Ardel Alegre
 * UserId: cs30fac
 * StudentID: A15752566
 * Description: interpretTime( struct timeInfo* timeInfo, const char * time )
 * will parse the time string and populate the tm_sec, tm_min, tm_hour and am_pm
 * members of the struct timeInfo pointed to by the timeInfo. If there are no
 * errors it will return zero, otherwise it will return approriaate error flags.
 */

#include "pa2.h"
#include <stdio.h>
#include "test.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DIGIT_SEPARATOR 10
#define TRUE 1
#define FALSE 0
#define STR_EQUALS 0

unsigned long interpretTime( struct timeInfo* timeInfo, const char * time ) {
  unsigned long errorBitmap = 0x0;
  char t[TIME_STRING_SIZE];
  int digitCounter = 0;
  strncpy(t, time, TIME_STRING_SIZE);
  char * ptr;
  long interpret;
  int storable = TRUE;
  int semi = 0;
  for(int i = 0; i < strlen(t); i++) {
      if(t[i] == CHAR_SEPARATOR) {
          semi++;
      }
  }
  if( semi != REQ_SEPARATORS) {
      //set ERR_TIM_FORMAT and return
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
      return errorBitmap;
  }




  interpret = strtol(t, &ptr, BASE);
  //test interpret for errors
  //set hour to interpret
  
  while(t[digitCounter] != CHAR_SEPARATOR) {
      digitCounter++;
  }
  if(digitCounter == 0) {
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
  }
  else if(digitCounter != MAX_DIGIT_LENGTH) {
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
      errorBitmap = errorBitmap | ERR_TIME_NUM;
      storable = FALSE;
  }
  
  
  if(storable == TRUE) {
    if(rangeCheck(interpret / DIGIT_SEPARATOR, MIN_TENS_HOUR, MAX_TENS_HR + 1) == FALSE) {
         errorBitmap = errorBitmap | ERR_TIME_LIMITS;
         storable = FALSE;
    }
    if(storable == TRUE) {
        if(interpret / DIGIT_SEPARATOR == 0) {
            if(rangeCheck((interpret % DIGIT_SEPARATOR), MIN_ONES_HOUR, 
                                MAX_ONES_HR + 1) == FALSE) {
                errorBitmap = errorBitmap | ERR_TIME_LIMITS;
                storable = FALSE;
            }
        } else {
            if(rangeCheck((interpret % DIGIT_SEPARATOR), MIN_ONES_HOUR, 
                                MAX_ONES_HR_ABOVE_TEN + 1) == FALSE) {
                errorBitmap = errorBitmap | ERR_TIME_LIMITS;
                storable = FALSE;
            }
        }
    }
  }
  if(storable == TRUE) {
    (*timeInfo).tm_hour = 0x0 | (interpret / DIGIT_SEPARATOR);
    (*timeInfo).tm_hour = (*timeInfo).tm_hour << 4;
    (*timeInfo).tm_hour = (*timeInfo).tm_hour | (interpret % DIGIT_SEPARATOR);
  }
  storable = TRUE;


  
  char * cut  = strchr(t, CHAR_SEPARATOR);
  cut++;
  interpret = strtol(cut, &ptr, BASE);
  //test interpret for errors
  //set mins to interpret
  char * counter = (char *)cut;
  digitCounter = 0;
  while(*counter != CHAR_SEPARATOR) {
      counter++;
      digitCounter++;

  }
  if(digitCounter == 0) {
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
  }
  else if(digitCounter != MAX_DIGIT_LENGTH) {
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
      errorBitmap = errorBitmap | ERR_TIME_NUM;
      storable = FALSE;
  }
  if(storable == TRUE) {
    if(rangeCheck(interpret / DIGIT_SEPARATOR, MIN_TENS_MIN, MAX_TENS_MIN) == FALSE) {
         errorBitmap = errorBitmap | ERR_TIME_LIMITS;
         storable = FALSE;
    }
    if(rangeCheck((interpret % DIGIT_SEPARATOR) , 
                                MIN_ONES_MIN, MAX_ONES_MIN) == FALSE) {
         errorBitmap = errorBitmap | ERR_TIME_LIMITS;
         storable = FALSE;
    }
  }
  if(storable == TRUE) {
    (*timeInfo).tm_min = 0x0 | (interpret / DIGIT_SEPARATOR);
    (*timeInfo).tm_min = (*timeInfo).tm_min << 4;
    (*timeInfo).tm_min = (*timeInfo).tm_min | (interpret % DIGIT_SEPARATOR);
  }
  storable = TRUE;

  
  
  
  
  
  
  
  cut = strchr(cut, CHAR_SEPARATOR);
  cut++;
  interpret = strtol(cut, &ptr, BASE);
  //test interprte for erros
  //set secs to interpret
  counter = (char *)cut;
  digitCounter = 0;
  while(*counter != *ptr) {
      counter++;
      digitCounter++;

  }
  if(digitCounter == 0) {
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
  }
  else if(digitCounter != MAX_DIGIT_LENGTH) {
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
      errorBitmap = errorBitmap | ERR_TIME_NUM;
      storable = FALSE;
  }
  if(storable == TRUE) {
    if(rangeCheck(interpret / DIGIT_SEPARATOR, MIN_TENS_SEC, MAX_TENS_SEC + 1) == FALSE) {
         errorBitmap = errorBitmap | ERR_TIME_LIMITS;
         storable = FALSE;
    }
     if(rangeCheck((interpret % DIGIT_SEPARATOR), MIN_ONES_SEC, 
                                MAX_ONES_SEC + 1) == FALSE) {
         errorBitmap = errorBitmap | ERR_TIME_LIMITS;
         storable = FALSE;
    }
  }
  if(storable == TRUE) {
    (*timeInfo).tm_sec = 0x0 | (interpret / DIGIT_SEPARATOR);
    (*timeInfo).tm_sec = (*timeInfo).tm_sec << 4;
    (*timeInfo).tm_sec = (*timeInfo).tm_sec | (interpret % DIGIT_SEPARATOR);
  }
  storable = TRUE;
  
  
  
  
  
  //cut -> last part of string
  cut = strchr(cut, *ptr);
  if(*cut == AM_VALUE) {
    //store am
      (*timeInfo).am_pm = AM_VALUE;
  } 
  else if(*cut == PM_VALUE)  {
    //store pm
      (*timeInfo).am_pm = PM_VALUE;
  }
  else {
     //error checks
      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
  }

  cut++;
  if(*cut != '\0')  {

      errorBitmap = errorBitmap | ERR_TIME_FORMAT;
  }

  
  return errorBitmap;


}
