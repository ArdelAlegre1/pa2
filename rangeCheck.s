/*
 *Author: Ardel Alegre
 *UserID: cs30fac
 *StudentID: A15752566
 */
    .cpu    cortex-a53
    .syntax unified
    .equ    FP_OFFSET, 18 
    .global rangeCheck
    .text
    .align  2

rangeCheck:
    push    {fp, lr}
    add     fp, sp, FP_OFFSET

        cmp     r1, r2
        bge     else
        
        cmp     r0, r1
        blt     else_if

        cmp     r0, r2
        bge     else_if

        mov     r0, 1
        b       end_else
    else_if:
            mov     r0, 0
            b       end_else
    else:
            mov     r0, -1
    
    end_else:

    sub     sp,fp, FP_OFFSET
    pop     {fp,pc}
