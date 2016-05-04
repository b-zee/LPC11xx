// Reset handler
void _reset(void) __attribute__ ((interrupt));
void _start(void);

extern void __stack_end(void); // Provided by linker
extern int main(void);         // Application entry point

// Function pointer type
typedef void (*handler)(void);

// Array of function pointers
const handler table[] __attribute__ ((section(".vectors"))) = {
    &__stack_end,  // 0x00 | SP
    _reset,        // 0x04 | Reset (PC)
    _reset,        // 0x08 | NMI
    _reset,        // 0x0C | HardFault
    0,             // 0x10
    0,             // 0x14
    0,             // 0x18
    0,             // 0x1C
    0,             // 0x20
    0,             // 0x24
    0,             // 0x28
    _reset,        // 0x2C | SVCall
    0,             // 0x30
    0,             // 0x34
    _reset,        // 0x38 | PendSV
    _reset,        // 0x3C | SysTick
    _reset,        // 0x40 | IRQ1
    _reset,        // 0x44 | IRQ2
    _reset,        // 0x48 | IRQ3
    _reset,        // 0x4C | IRQ4
    _reset,        // 0x50 | IRQ5
    _reset,        // 0x54 | IRQ6
    _reset,        // 0x58 | IRQ7
    _reset,        // 0x5C | IRQ8
    _reset,        // 0x60 | IRQ9
    _reset,        // 0x64 | IRQ10
    _reset,        // 0x68 | IRQ11
    _reset,        // 0x6C | IRQ12
    _reset,        // 0x70 | IRQ13
    _reset,        // 0x74 | IRQ14
    _reset,        // 0x78 | IRQ15
    _reset,        // 0x7C | IRQ16
    _reset,        // 0x80 | IRQ17
    _reset,        // 0x84 | IRQ18
    _reset,        // 0x88 | IRQ19
    _reset,        // 0x8C | IRQ20
    _reset,        // 0x90 | IRQ21
    _reset,        // 0x94 | IRQ22
    _reset,        // 0x98 | IRQ23
    _reset,        // 0x9C | IRQ24
    _reset,        // 0xA0 | IRQ25
    _reset,        // 0xA4 | IRQ26
    _reset,        // 0xA8 | IRQ27
    _reset,        // 0xAC | IRQ28
    _reset,        // 0xB0 | IRQ29
    _reset,        // 0xB4 | IRQ30
    _reset,        // 0xB8 | IRQ31
    _reset         // 0xBC | IRQ32
};

void _reset(void) {
    _start();
    while (1);
}


void _start(void)
{
    // Clear .bss segment
    extern int __bss_start;
    extern int __bss_end;

    int *p = &__bss_start;
    while (p != &__bss_end) {
        *p = 0;
        p++;
    }

    // Copy .data from FLASH (ROM) to RAM
    extern int __data_start_lma;
    extern int __data_start;
    extern int __data_end;

    int *s = &__data_start_lma;
    int *d = &__data_start;
    while(d != &__data_end){
        *d++ = *s++;
    }

    (void)main();
}
