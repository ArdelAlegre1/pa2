/* 
 * Author: Ardel Alegre
 * AccountID: cs30fac
 * StudentID: A15752566
 * Date:
 * Description:
 *
 */
@Standard Prologue
        .cpu        cortex-a53
        .syntax     unified
        .equ        FP_OFFSET, 4
        .section    .rodata
        .global     setClock
        .text
        .align      2

setClock:

    push        {fp, lr}
    add         fp, sp, FP_OFFSET
    sub         sp, sp, 36


    ldr         r2, =timeInfo_hourOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    mov         r3, 10
    sdiv        r3, r2, r3
    mov         r2, 0x0000
    orr         r2, r2, r3
    lsl         r2, r2, 4
    str         r2, [r0]
    
    str         r1, [fp, -4]
    str         r0, [fp, -8]
    ldr         r2, =timeInfo_hourOffset
    ldr         r2, [r2]
    ldr         r0, [r1, r2]
    mov         r1, 10
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, -4]
    ldr         r0, [fp, -8]
    ldr         r3, [r0]
    orr         r2, r3, r2
    lsl         r2, r2, 4
    str         r2, [r0]    

    ldr         r2, =timeInfo_minOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    mov         r3, 10
    sdiv        r3, r2, r3
    ldr         r2, [r0]
    orr         r2, r2, r3
    lsl         r2, r2, 4
    str         r2, [r0]
   
    str         r1, [fp, -4]
    str         r0, [fp, -8]
    ldr         r2, =timeInfo_minOffset
    ldr         r2, [r2]
    ldr         r0, [r1, r2]
    mov         r1, 10
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, -4]
    ldr         r0, [fp, -8]
    ldr         r3, [r0]
    orr         r2, r3, r2
    lsl         r2, r2, 4
    str         r2, [r0]    


    ldr         r2, =timeInfo_secOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    mov         r3, 10
    sdiv        r3, r2, r3
    ldr         r2, [r0]
    orr         r2, r2, r3
    lsl         r2, r2, 4
    str         r2, [r0]


    str         r1, [fp, -4]
    str         r0, [fp, -8]
    ldr         r2, =timeInfo_secOffset
    ldr         r2, [r2]
    ldr         r0, [r1, r2]
    mov         r1, 10
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, -4]
    ldr         r0, [fp, -8]
    ldr         r3, [r0]
    orr         r2, r3, r2
    lsl         r2, r2, 8
    str         r2, [r0]   


    ldr         r2, =timeInfo_ampmOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2] 
    str         r1, [fp, -4]
    str         r0, [fp, -8]
    mov         r0, r2
    mov         r1, 2
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, -4]
    ldr         r0, [fp, -8]
    cmp         r2, 0x0
    beq         seventy


    ldr         r2, =timeInfo_ampmOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2] 
    mov         r1, 0x61
    and         r2, r2, r1
    ldr         r3, [r0]
    orr         r2, r3, r2
    str         r2, [r0]
    b           end

seventy:
    
    
    ldr         r2, =timeInfo_ampmOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2] 
    mov         r1, 0x70
    and         r2, r2, r1
    ldr         r3, [r0]
    orr         r2, r3, r2
    str         r2, [r0]
end:

/*
    ldr         r2, =timeInfo_ampmOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    mov         r3, 10
    sdiv        r3, r2, r3
    ldr         r2, [r0]
    orr         r2, r2, r3
    lsl         r2, r2, 4
    str         r2, [r0]

    str         r1, [fp, -4]
    str         r0, [fp, -8]
    ldr         r2, =timeInfo_ampmOffset
    ldr         r2, [r2]
    ldr         r0, [r1, r2]
    mov         r1, 10
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, -4]
    ldr         r0, [fp, -8]
    ldr         r3, [r0]
    orr         r2, r3, r2
    str         r2, [r0]   

    */
@Standard Epilogue
    sub         sp, fp, FP_OFFSET
    pop         {fp, pc}
