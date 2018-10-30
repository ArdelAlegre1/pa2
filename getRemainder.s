/*
 *Author: Ardel Alegre
 *UserID: cs30fac
 *StudentID: A15752566
 *DEscription: Function takes 2 parameters, and finds the remainder of the first 
 *parameter divided by the second parameter.
 */

    .cpu    cortex-a53
    .syntax unified
    .equ    FP_OFFSET, 18 
    .global getRemainder
    .text
    .align  2

getRemainder:
@Standard prologue
    push    {fp, lr}
    add     fp, sp, FP_OFFSET
/*
  *  cmp     r0, r1          @compares divisor and dividend
   * blt     end_loop        @if the dividor is less than the dividend skip to
   *                         @end loop
   * @if the dividend is larger than the divisor run loop
   * loop:
*
 *       sub     r0, r0, r1  @subtract dividend by the divisor
  *      
   *     cmp     r0, r1      @compares divisor and dividend
    *    bge     loop        @if divisor is greater than or equal to dividend
     */                       @return to loop

    sdiv    r2, r0, r1
    mul     r3, r2, r1
    sub     r2, r0, r3

    @end_loop:

    mov     r0, r2
@standard epilogue
    sub     sp,fp, FP_OFFSET
    pop     {fp,pc}
