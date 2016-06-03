    .section    .text.zmn_thread_my_routine
    .align      2
    .thumb_func
    .global     zmn_switch_to_psp
zmn_switch_to_psp:
    MOV  r2,      #0x2 // bit[1] of CONTROL selects SP
    MSR  psp,     r0   // Set PSP value
    MSR  control, r2   // Switch to PSP
    ISB                // Synchronize to ensure PSP use
    MSR  msp,     r1   // Set MSP value
    BX   LR


    .section    .text._pendSV
    .align      2
    .thumb_func
    .global     _pendSV
_pendSV:
    BX LR
