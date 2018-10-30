        .cpu        cortex-a53
        .syntax     unified
        .equ        FP_OFFSET, 4
        .section     .rodata
fmt:    .asciz  "%c"
        .global     printChar
        .text
        .align      2

printChar:
        push        {fp, lr}
        add         fp, sp, FP_OFFSET

        mov         r1, r0
        ldr         r0, =fmt
        bl          printf

        sub         sp, fp, FP_OFFSET
        pop         {fp, pc}
