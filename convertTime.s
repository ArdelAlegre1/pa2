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
        .global     convertTime
        .text
        .align      2

convertTime:

    push        {fp, lr}
    add         fp, sp, FP_OFFSET

    ldr         r2, =tm_hour_offset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    ldr         r3, =timeInfo_houOffset
    ldr         r3, [r3]
    cmp         r2, 0x12
    bgt         PM
AM:
    cmp         r2, 0x0
    bne         not0
    mov         r2, 0x12
not0:
    str         r2, [r0, r3]
    mov         r2, 0x61
    ldr         r3, =timeInfo_ampmOffset
    ldr         r3, [r3]
    str         r2, [r0,r3]
    b           end_ampm

PM:
    sub         r2, r2, 0x12
    str         r2, [r0, r3]
    mov         r2, 0x70
    ldr         r3, =timeInfo_ampmOffset
    ldr         r3, [r3]
    str         r2, [r0, r3]

emd_ampm:

    ldr         r2, =timeInfo_minOffset
    ldr         r2, [r2]
    ldr         r2, [r0, r2]
    ldr         r3, =tm_min_offset
    ldr         r3, [r3]
    str         r2, [r1, r3]


    ldr         r2, =timeInfo_secOffset
    ldr         r2, [r2]
    ldr         r2, [r0, r2]
    ldr         r3, =tm_sec_offset
    ldr         r3, [r3]
    str         r2, [r1, r3]

/*
    @write function here
    ldr         r2, timeInfo_ampmOffset
    ldr         r2, [r2]
    ldr         r3, =tm_hour_offset
    ldr         r3, [r3]
    ldr         r3, [r1, r3]
    cmp         r3, 12
    bgt         setPM

    mov         r3, 61
   */ 
@Standard Epilogue
    sub         sp, fp, FP_OFFSET
    pop         {fp, pc}
