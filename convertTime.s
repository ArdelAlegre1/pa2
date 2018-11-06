/* 
 * Author: Ardel Alegre
 * AccountID: cs30fac
 * StudentID: A15752566
 * Description: convertTime( struct timeInfo * timeTinfo, const struct tm* tm)
 * uses hours, mins, secs in tm to populate the tm_sec, tm_min, tm_hour and
 * am_pm members of the struct pointed to by timeInfo.
 */

        .cpu        cortex-a53
        .syntax     unified
        .equ        FP_OFFSET, 4
        .section    .rodata
        .global     convertTime
        .text
        .align      2

convertTime:
@Standard Prologue
    push        {fp, lr}
    add         fp, sp, FP_OFFSET

    ldr         r2, =tm_hour_offset         @access address to tm_hour_offset
    ldr         r2, [r2]                    @get value of tm_hour_offset
    ldr         r2, [r1, r2]                @set r2 to hour in struct tm
    ldr         r3, =timeInfo_hourOffset    @access address to timeInfo_hourOffset
    ldr         r3, [r3]                    @set r3 to value of timeIf_hourOffset
    cmp         r2, 0x12                    @compares r2 to 0x12
    bge         PM                          @if r2 >= 0x12 then go to PM
AM:
    cmp         r2, 0x0                     @compares r2 to 0x0
    bne         not0                        @if its != move to not0
    mov         r2, 0x12                    @if it equal to 0 then set r2 to 12
not0:
    str         r2, [r0, r3]                @store r2 into hours of timeInfo struct
    mov         r2, 0x61                    @set r2 to 0x61 which is = 'a'
    ldr         r3, =timeInfo_ampmOffset
    ldr         r3, [r3]                    @load address of timeInfo_ampmOffset
    str         r2, [r0,r3]                 @store 'a' into ampm of timeInfo struct
    b           end_ampm                    @skip pm

PM:
    sub         r2, r2, 0x12                @subtract 12 from r2 to make it under 13
    str         r2, [r0, r3]                @store new r2 into timeinfo struct as hour
    mov         r2, 0x70                    @set r2 to 70 which is = 'p'
    ldr         r3, =timeInfo_ampmOffset
    ldr         r3, [r3]                    @load address of timeInfo_ampmOffset
    str         r2, [r0, r3]                @store 'p' into ampm of timeInfo struct

end_ampm:
/*
 *each of the last two sections finds the address of min or sec in
 *both tm and timeInfo structs, and takes the value of min or sec
 *from tm and stores it in the corresponding min or sec of the 
 *timeInfo struct
*/
    ldr         r2, =timeInfo_minOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    ldr         r3, =tm_min_offset
    ldr         r3, [r3]
    str         r2, [r0, r3]


    ldr         r2, =timeInfo_secOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    ldr         r3, =tm_sec_offset
    ldr         r3, [r3]
    str         r2, [r0, r3]

@Standard Epilogue
    sub         sp, fp, FP_OFFSET
    pop         {fp, pc}
