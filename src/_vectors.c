#include <LPC11xx.h> // NVIC_SystemReset

extern void __stack_end(void);

__attribute__ ((interrupt, weak, noreturn)) void _dummy_handler(void);
__attribute__ ((interrupt, weak, noreturn)) void _reset(void);
__attribute__ ((interrupt, weak, alias("_dummy_handler"))) void _nmi(void);
__attribute__ ((interrupt, weak, alias("_dummy_handler"))) void _hard_fault(void);
__attribute__ ((interrupt, weak, alias("_dummy_handler"))) void _SV_call(void);
__attribute__ ((interrupt, weak, alias("_dummy_handler"))) void _pendSV(void);
__attribute__ ((interrupt, weak, alias("_dummy_handler"))) void _sys_tick(void);

// Vectors type
typedef void (*handler)(void);

// Vector table
__attribute__ ((section(".vectors"))) const handler table[] = {
    &__stack_end,   // 0x00 | SP
    _reset,         // 0x04 | Reset (PC)
    _nmi,           // 0x08 | NMI
    _hard_fault,    // 0x0C | HardFault
    _dummy_handler, // 0x10 | Reserved
    _dummy_handler, // 0x14 | Reserved
    _dummy_handler, // 0x18 | Reserved
    _dummy_handler, // 0x1C | Reserved
    _dummy_handler, // 0x20 | Reserved
    _dummy_handler, // 0x24 | Reserved
    _dummy_handler, // 0x28 | Reserved
    _SV_call,       // 0x2C | SVCall
    _dummy_handler, // 0x30 | Reserved
    _dummy_handler, // 0x34 | Reserved
    _pendSV,        // 0x38 | PendSV
    _sys_tick,      // 0x3C | SysTick
    _dummy_handler, // 0x40 | IRQ1
    _dummy_handler, // 0x44 | IRQ2
    _dummy_handler, // 0x48 | IRQ3
    _dummy_handler, // 0x4C | IRQ4
    _dummy_handler, // 0x50 | IRQ5
    _dummy_handler, // 0x54 | IRQ6
    _dummy_handler, // 0x58 | IRQ7
    _dummy_handler, // 0x5C | IRQ8
    _dummy_handler, // 0x60 | IRQ9
    _dummy_handler, // 0x64 | IRQ10
    _dummy_handler, // 0x68 | IRQ11
    _dummy_handler, // 0x6C | IRQ12
    _dummy_handler, // 0x70 | IRQ13
    _dummy_handler, // 0x74 | IRQ14
    _dummy_handler, // 0x78 | IRQ15
    _dummy_handler, // 0x7C | IRQ16
    _dummy_handler, // 0x80 | IRQ17
    _dummy_handler, // 0x84 | IRQ18
    _dummy_handler, // 0x88 | IRQ19
    _dummy_handler, // 0x8C | IRQ20
    _dummy_handler, // 0x90 | IRQ21
    _dummy_handler, // 0x94 | IRQ22
    _dummy_handler, // 0x98 | IRQ23
    _dummy_handler, // 0x9C | IRQ24
    _dummy_handler, // 0xA0 | IRQ25
    _dummy_handler, // 0xA4 | IRQ26
    _dummy_handler, // 0xA8 | IRQ27
    _dummy_handler, // 0xAC | IRQ28
    _dummy_handler, // 0xB0 | IRQ29
    _dummy_handler, // 0xB4 | IRQ30
    _dummy_handler, // 0xB8 | IRQ31
    _dummy_handler  // 0xBC | IRQ32
};

void _dummy_handler(void)
{
    NVIC_SystemReset();

    while (1);
}

void _reset(void)
{
    extern void _start(void);
    _start();

    while (1);
}
