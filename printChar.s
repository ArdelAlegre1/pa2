/* 
 * Author: Ardel Alegre
 * UserID: cs30fac
 * StudentID: A15752566
 * Description: printChar(char c) takes parameter char and prints it.
 */
        
        
        .cpu        cortex-a53
        .syntax     unified
        .equ        FP_OFFSET, 4
        .section     .rodata
fmt:    .asciz      "%c"
        .global     printChar
        .text
        .align      2
@Standard prologue
printChar:
        push        {fp, lr}
        add         fp, sp, FP_OFFSET

        mov         r1, r0              @move char into r1
        ldr         r0, =fmt            @set r0 to "%c"
        bl          printf              @printf("%c", char)

@Standard Epilogue
        sub         sp, fp, FP_OFFSET
        pop         {fp, pc}
