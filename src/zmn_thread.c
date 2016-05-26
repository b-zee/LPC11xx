#include "zmn_thread.h"

#include "zmn_uart.h"

#include <LPC11xx.h>
#include <stdint.h>
#include <stddef.h>  // size_t

//#if UINTPTR_MAX < UINT32_MAX
//#error UINTPTR_MAX < UINT32_MAX
//#endif

#define ZMN_THREADS 8

typedef struct thread {
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
} thread;

//static thread threads[ZMN_THREADS];
//static size_t thread_current;


void zmn_thread_init(void (*f)(void))
{
    // Setup stacks for threads
    // Create main thread
    // Start main thread


    // Essentially make this flow a thread (main thread)

    //extern uint32_t __stack_start;
    //extern uint32_t __stack_end;

    //__set_PSP(__get_MSP()); // Point PSP to main stack area
    //__set_CONTROL(1 << 1);  // Use PSP
    //__ISB();                // Ensure execution with PSP

    //__set_MSP(__stack_start + 200); // Point MSP to new area


    // // Todo: Copy main stack to new process stack and run further from there

    // Enable SysTick interrupt
    //(void)SysTick_Config(SystemCoreClock); // Todo: error handling
}

/*void zmn_thread_create(void (*f)(void))
{
    size_t i;
    for (i = 0; i < ZMN_THREADS; ++i) {
        if (threads[i].pc == 0) {
            break;
        }
    }

    threads[i].pc = (uint32_t)f;
    threads[i].lr = (uint32_t)zmn_thread_return;
}*/

__attribute__ ((interrupt)) void _sys_tick(void)
{
    //SCB->ICSR |= 1 << 28; // Trigger PendSV
}

__attribute__ ((interrupt)) void _pendSV(void)
{
    /*
    //size_t thread_next; // Todo: figure out next thread

    typedef struct {
        __IO uint32_t r0;   // SP + 0x00 | R0   <- PSP points here
        __IO uint32_t r1;   // SP + 0x04 | R1
        __IO uint32_t r2;   // SP + 0x08 | R2
        __IO uint32_t r3;   // SP + 0x0C | R3
        __IO uint32_t r12;  // SP + 0x10 | R12
        __IO uint32_t lr;   // SP + 0x14 | LR
        __IO uint32_t pc;   // SP + 0x18 | PC
        __IO uint32_t xpsr; // SP + 0x1C | xPSR
        __IO uint32_t sp;   // SP + 0x20 | <before interrupt>
    } stack_frame;

    uint32_t     psp = __get_PSP();
    stack_frame *sf  = (stack_frame *)psp;

    threads[thread_current].sp = sf->sp;



    //__set_PSP(threads[thread_current + 1]); // Set stack pointer to next thread's stack
    // Todo: modify PC and LR in exception entry stack frame ^
    */

}
