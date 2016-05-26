#include <stdint.h>

void _start(void)
{
    extern void main(void);

    // Clear .bss segment
    extern uint32_t __bss_start;
    extern uint32_t __bss_end;

    uint32_t *p = &__bss_start;
    while (p != &__bss_end) {
        *p++ = 0;
    }

    // Copy .data from FLASH (ROM) to RAM
    extern uint32_t __data_start_lma;
    extern uint32_t __data_start;
    extern uint32_t __data_end;

    uint32_t *s = &__data_start_lma;
    uint32_t *d = &__data_start;
    while(d != &__data_end){
        *d++ = *s++;
    }

    main();

    while (1);
}
