extern int main(void);

int _start(void)
{
    extern int __bss_start;
    extern int __bss_end;

    int *p = &__bss_start;

    while (p != &__bss_end) {
        *p = 0;
        p++;
    }

    // Todo: copy .data from FLASH to RAM

    (void)main();

    while (1);

    return 0;
}
