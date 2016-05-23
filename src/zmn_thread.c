#include "zmn_thread.h"

void zmn_thread_init(void)
{
    (void)SysTick_Config(SystemCoreClock); // Todo: error handling

    // Essentially make this flow a thread (main thread)
    // // Todo: Copy main stack to new process stack and run further from there
    // __set_CONTROL(1 << 1); // Use PSP
    // __ISB();               // Ensure execution with PSP
}

/*void zmn_thread_create(void (*f)(void))
{

}*/

__attribute__ ((interrupt)) void _sys_tick(void)
{
    // SCB->ICSR |= 1 << 28; // Trigger PendSV
}

/*__attribute__ ((interrupt)) void _pendSV(void)
{
// SP + 0x00 | R0
// SP + 0x04 | R1
// SP + 0x08 | R2
// SP + 0x0C | R3
// SP + 0x10 | R12
// SP + 0x14 | LR
// SP + 0x18 | PC
// SP + 0x1C | xPSR


//__set_PSP(); // Set stack pointer to next thread's stack
// Todo: modify PC in exception entry stack frame ^

}*/
