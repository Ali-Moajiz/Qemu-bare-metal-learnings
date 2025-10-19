    .global _start
_start:
    ldr sp, =_stack_top     /* initialize stack pointer */
    bl _custom_main                 /* jump to C code's funtion */
loop:  
    b loop                    /* loop forever (unconditional jump to the defined local lable loop) */
