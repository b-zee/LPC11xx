void _start(void)
{
    extern void main(void);

    // Clear .bss segment
    extern int __bss_start;
    extern int __bss_end;

    int *p = &__bss_start;
    while (p != &__bss_end) {
        *p++ = 0;
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

    main();
}
