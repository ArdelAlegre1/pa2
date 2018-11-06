/* 
 * Author: Ardel Alegre
 * AccountID: cs30fac
 * StudentID: A15752566
 * Description:incrementBCDValue(unsigned char* BCDdigits, const unsigned char
 * resetThreshold, const unsigned char resetValue) takes BCDdigits and
 * increments it by one, and if it equals resetThreshold after it increments,
 * then it will be set to the resetValue.
 */
@Standard Prologue
        .cpu        cortex-a53
        .syntax     unified
        .equ        FP_OFFSET, 4
        .section    .rodata
        .global     incrementBCDValue
        .text
        .align      2

incrementBCDValue:

    push        {fp, lr}
    add         fp, sp, FP_OFFSET
    sub         sp, sp, 16              @make space for local variables
@check if ones BCDValue has 9           
    ldrb        r3, [r0]                @set r3 to BCDdigits          
    str         r0, [fp, -4]            @store all the arguments onto the stack
    strb        r1, [fp, -5]
    strb        r2, [fp, -6]
    mov         r0, r3                  @set r0 to BCDdigits
    mov         r1, 0x10                @set r1 to 0x10
    @bl         getRemainder            @get remainder but this didnt find the
    sdiv        r2, r0, r1              @file so the following lines will fin it
    mul         r3, r2, r1
    sub         r2, r0, r3              @r2 is the remainder of BCDdigits/10
    ldr         r0, [fp, -4]            @set r0 to address of BCDdigits
    ldrb        r3, [r0]                @r3 = BCDdigits
    cmp         r2, 9                   @compares the remainderofBCD to 9
    bne         skip                    @if the remainder is not 9 move to skip
@if it has 9 then increment tens place and set ones place to 0
increment_tens:
    lsr         r3, r3, 4               @shift the bits right: get rid of 1's place
    add         r3, r3, 1               @add one to the 10's place
    lsl         r3, r3, 4               @shift right loading 0's into ones place
    @str         r3, [r0]
    b           compare                 @move to compare
@if no 9 then increment ones place
skip:
    add         r3, r3, 0x1             @increment BCDdigits by 1

@compares incremented value to threshold value
compare:
    ldrb        r1, [fp, -5]            @load resetThreshold to r1
    ldrb        r2, [fp, -6]            @load resetValue to r2
    cmp         r3, r1                  @compare BCDdiggits to resetThreshold
    beq        reset_value              @if they are equal move to reset_value
  
    strb        r3, [r0]                @store incremented BCDdigit
    mov         r0, 0                   @0 into r0 to return 0
    b           end

reset_value:
    strb        r2, [r0]                @store resetValue as BCDdigits
    mov         r0, 1                   @1 into r0 to return 1

end:

@Standard Epilogue
    sub         sp, fp, FP_OFFSET
    pop         {fp, pc}
