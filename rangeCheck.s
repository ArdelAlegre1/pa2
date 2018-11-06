/*
 *Author: Ardel Alegre
 *UserID: cs30fac
 *StudentID: A15752566
 *Description: rangeCheck(long value, long minRange, longmaxRange) Checks if
 *value is between minRange and maxRange, inclusive and
 *exclusive, and returns 1 if yeas and 0 if no. If minRange >== maxRange, returns
 *-1
 */
    .cpu    cortex-a53
    .syntax unified
    .equ    FP_OFFSET, 18 
    .global rangeCheck
    .text
    .align  2
@Standard Prologue
rangeCheck:
    push    {fp, lr}
    add     fp, sp, FP_OFFSET
        @checks for error case of minRange >= maxRange
        cmp     r1, r2          @comnpares minRange and maxRange          
        bge     else            @if minRange >= maxRange, skip to else
        
        @checks if value is in range
        cmp     r0, r1          @compares value and minRange
        blt     else_if         @if value < minRange skip to else_if
        cmp     r0, r2          @compares value to maxRange
        bge     else_if         @if value >= maxRange, skip to else_if
        @runs if value is in range
        mov     r0, 1           @set r0 to 1     
        b       end_else        @returns 1

    @else if runs if value not in range
    else_if:              
            mov     r0, 0       @set r0 to 0
            b       end_else    @returns 0

    @else runs for error case
    else:
            mov     r0, -1      @sets r0 to -1 to be returned
    
    end_else:

    sub     sp,fp, FP_OFFSET
    pop     {fp,pc}
