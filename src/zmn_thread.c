/**
 * @brief   Multi-tasking functionality
 * @author  Benno Zeeman <bzeeman@live.nl>
 * @todo    Everything; design stack layout
 */
//  Copyright (C) 2016 Benno Zeeman
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "zmn_thread.h"
#include "zmn_routines.h"

#include <LPC11xx.h>
#include <stdint.h>
#include <stddef.h>

#define MAIN_STACK_SIZE 64 // 64 words = 256 bytes

struct thread {
    struct thread *next; // Linked list
    size_t         size; // Stack word size
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

//static struct thread *thread_main;
//static struct thread *thread_current;


void zmn_thread_init(void (*main_fp)(void))
{
    extern uint32_t __stack_end;

    // Point to beginning of new main thread stack
    uint32_t *psp = &__stack_end - MAIN_STACK_SIZE;

    struct thread      *t;
    //struct stack_frame *f;

    t   = (struct thread *)psp - 1;
    //f   = (stack_frame *)t - 1;
    //f   = (stack_frame *)((uintptr_t)f & ~0x4); // Align on 8-byte (2-word)
    psp = (uint32_t *)t;

    t->next = t; // Only one thread, so points to itself
    t->size = MAIN_STACK_SIZE;

    // Set and use process stack, and reset main stack
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
