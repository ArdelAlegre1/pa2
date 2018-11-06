/* 
 * Author: Ardel Alegre
 * AccountID: cs30fac
 * StudentID: A15752566
 * Description: setClock( unsigned long * clock, const struct timeInfo *
 * timeInfo ) will take the hours, mins, secs, and ammp vlaues and represent
 * them as a BCD long in clock.
 *
 */

@Standard Prologue
        .cpu        cortex-a53
        .syntax     unified
        .equ        FP_OFFSET, 4
        .equ        CLOCK_OFFSET, -8
        .equ        TIMEINFO_OFFSET, -4
        .section    .rodata
        .global     setClock
        .text
        .align      2
setClock:
    
    push        {fp, lr}
    add         fp, sp, FP_OFFSET
    sub         sp, sp, 8                   @make space on stack                 


    ldr         r2, =timeInfo_hourOffset    @load the pointer to timeInfo_hourOffset into r2
    ldr         r2, [r2]                    @access vlaue of timeInfo_hourOffset                  
    ldr         r2, [r1, r2]                @r2 = timeInfo.hours
    mov         r3, 10                      @r3 = 10
    sdiv        r3, r2, r3                  @r3 = timeInfo.hours/10
    mov         r2, 0x0000                  @r2 = 0x00
    orr         r2, r2, r3                  @copy the first digit of hours into r2
    lsl         r2, r2, 4                   @shift r2 left 4 bits to laod in 0's                     
    str         r2, [r0]                    @r2 into clock
    
    str         r1, [fp, TIMEINFO_OFFSET]   @store timeInfo on stack             
    str         r0, [fp, CLOCK_OFFSET]      @store clock on stack
    ldr         r2, =timeInfo_hourOffset    @r2 = address of hourOffset
    ldr         r2, [r2]                    @r2 = hourOffset
    ldr         r0, [r1, r2]                @r0 = timeInfo.hours
    mov         r1, 10                      @r1 = 10 
    bl          getRemainder                @find remainder of hours/10
    mov         r2, r0                      @move remainder to r2                    
    ldr         r1, [fp, TIMEINFO_OFFSET]   @load struct pointer from stack
    ldr         r0, [fp, CLOCK_OFFSET]      @load clock pointer from stack
    ldr         r3, [r0]                    @load clock into r3
    orr         r2, r3, r2                  @copy remiander into first 4 bits
    lsl         r2, r2, 4                   @shift clock 4 4 bit  
    str         r2, [r0]                    @store new value into clock

    ldr         r2, =timeInfo_minOffset     @r2 = address of timeIndo_minOffset
    ldr         r2, [r2]                    @r2 = timeInfo_minOffset
    ldr         r2, [r1, r2]                @r2 = timeInfo.min
    mov         r3, 10                      @r3 = 10
    sdiv        r3, r2, r3                  @r3 = timeInfo.min/10
    ldr         r2, [r0]                    @load clock into r2
    orr         r2, r2, r3                  @copy r3 into clock
    lsl         r2, r2, 4                   @shift clock left 4 bits loading 0's
    str         r2, [r0]                    @store new clock value in clock
   
    /*
     * The following block is the same procedure to find load the first digit
     * of hours into clock, but we are doing it with mins.
     */
    str         r1, [fp, TIMEINFO_OFFSET]                
    str         r0, [fp, CLOCK_OFFSET]
    ldr         r2, =timeInfo_minOffset
    ldr         r2, [r2]
    ldr         r0, [r1, r2]
    mov         r1, 10
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, TIMEINFO_OFFSET]
    ldr         r0, [fp, CLOCK_OFFSET]
    ldr         r3, [r0]
    orr         r2, r3, r2
    lsl         r2, r2, 4
    str         r2, [r0]    

    /*
     * This block is the same procedure to loading the first digit of
     * mins into clock, but we are doing it with seconds.
     */
    ldr         r2, =timeInfo_secOffset
    ldr         r2, [r2]
    ldr         r2, [r1, r2]
    mov         r3, 10
    sdiv        r3, r2, r3
    ldr         r2, [r0]
    orr         r2, r2, r3
    lsl         r2, r2, 4
    str         r2, [r0]

    /*
     * This block is the same procedure to loading the second digit of mins
     * into clock, but we are doing it with secs
     */
    str         r1, [fp, TIMEINFO_OFFSET]
    str         r0, [fp, CLOCK_OFFSET]
    ldr         r2, =timeInfo_secOffset
    ldr         r2, [r2]
    ldr         r0, [r1, r2]
    mov         r1, 10
    bl          getRemainder
    mov         r2, r0
    ldr         r1, [fp, TIMEINFO_OFFSET]
    ldr         r0, [fp, CLOCK_OFFSET]
    ldr         r3, [r0]
    orr         r2, r3, r2
    lsl         r2, r2, 8                       @instead we shift 8 bits to load
                                                @8 bits of ampm vlaue
    str         r2, [r0]   

    
    ldr         r2, =timeInfo_ampmOffset        @load address of ampmoffst into r2
    ldr         r2, [r2]                        @r2 = ampmoffset
    ldr         r2, [r1, r2]                    @load ampm value to r2
    str         r1, [fp, TIMEINFO_OFFSET]       @store *timeInfo
    str         r0, [fp, CLOCK_OFFSET]          @store *clock
    mov         r0, r2                          @r0 = ampm vlaue
    mov         r1, 2                           @r1 = 2
    bl          getRemainder                    @r0 = remainder of ampm/2
    mov         r2, r0                          @r2 = remainder of ampm/2
    ldr         r1, [fp, TIMEINFO_OFFSET]       @load *timeinfo into r1
    ldr         r0, [fp, CLOCK_OFFSET]          @load *clock into r0
    cmp         r2, 0x0                         @compare remainder of ampm/2 to 0
    beq         seventy                         @if ampm/2 = 0 skip to seventy


    mov         r2, 0x61                        @r2 = 0x61 = 'a'
    ldr         r3, [r0]                        @r3 = clock value
    orr         r2, r3, r2                      @copy 0x61 to clock
    str         r2, [r0]                        @store new value into clock
    b           end                             @end routine

seventy:
    
    
    mov         r2, 0x70                        @r2 = 0x70 = 'p'
    ldr         r3, [r0]                        @r3 = clock value
    orr         r2, r3, r2                      @copy 0x70 to clock
    str         r2, [r0]                        @store new value into clock
end:

@Standard Epilogue
    sub         sp, fp, FP_OFFSET
    pop         {fp, pc}
