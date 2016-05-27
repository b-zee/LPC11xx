#include "zmn_thread.h"
#include "zmn_routines.h"

#include "zmn_uart.h"

#include <LPC11xx.h>
#include <stdint.h>
//#include <stddef.h>  // size_t

#define STACK_SIZE 256

struct thread {
    struct thread *next; // Linked list
    uint32_t       sp;
    uint32_t       r4;
    uint32_t       r5;
    uint32_t       r6;
    uint32_t       r7;
    uint32_t       r8;
    uint32_t       r9;
    uint32_t       r10;
    uint32_t       r11;
};

struct stack_frame {
    __IO uint32_t r0;   // SP + 0x00 | R0    <-- PSP points here after interrupt
    __IO uint32_t r1;   // SP + 0x04 | R1
    __IO uint32_t r2;   // SP + 0x08 | R2
    __IO uint32_t r3;   // SP + 0x0C | R3
    __IO uint32_t r12;  // SP + 0x10 | R12
    __IO uint32_t lr;   // SP + 0x14 | LR
    __IO uint32_t pc;   // SP + 0x18 | PC
    __IO uint32_t xpsr; // SP + 0x1C | xPSR
};

//static thread *main_thread;


void zmn_thread_init(void (*main_fp)(void))
{
    extern uint32_t __stack_end;

    // Point to beginning of new thread stack
    uint32_t *psp = &__stack_end - (STACK_SIZE / sizeof(uint32_t *));

    struct thread      *t;
    //struct stack_frame *f;

    t   = (struct thread *)psp - 1;
    //f   = (stack_frame *)t - 1;
    //f   = (stack_frame *)((uintptr_t)f & ~0x4); // Align on 8-byte (2-word)
    psp = (uint32_t *)t;

    t->next = t;

    zmn_switch_to_psp(psp, &__stack_end);

    // Enable SysTick interrupt
    (void)SysTick_Config(SystemCoreClock); // Todo: error handling

    main_fp();

    while (1);
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
    SCB->ICSR |= 1 << 28; // Trigger PendSV
}
