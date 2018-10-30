/* 
 * Author: Ardel Alegre
 * AccountID: cs30fac
 * StudentID: A15752566
 * Date:
 * Description:
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
    sub         sp, sp, 16
@check if ones BCDValue has 9
    ldrb        r3, [r0]
    str         r0, [fp, -4]
    strb        r1, [fp, -5]
    strb        r2, [fp, -6]
    mov         r0, r3
    mov         r1, 0x10
    @bl         getRemainder    
    sdiv        r2, r0, r1
    mul         r3, r2, r1
    sub         r2, r0, r3
    ldr         r0, [fp, -4]
    ldrb        r3, [r0]
    cmp         r2, 9
    bne         skip
@if it has 9 then increment tens place and set ones place to 0
increment_tens:
    lsr         r3, r3, 4
    add         r3, r3, 1
    lsl         r3, r3, 4
    @str         r3, [r0]
    b           compare
@if no 9 then increment ones place
skip:
    add         r3, r3, 0x1

@compares incremented value to threshold value
compare:
    ldrb        r1, [fp, -5]
    ldrb        r2, [fp, -6]
    cmp         r3, r1
    beq        reset_value
  
    strb        r3, [r0]
    mov         r0, 0
    b           end

reset_value:
    strb        r2, [r0]
    mov         r0, 1

end:

@Standard Epilogue
    sub         sp, fp, FP_OFFSET
    pop         {fp, pc}
