MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 32K
    RAM   (rwx) : ORIGIN = 0x10000000, LENGTH =  4K
}

ENTRY(_start)

SECTIONS
{
    .text : ALIGN(4)
    {
        KEEP(*(.vectors))
        *(.text .text.*)
        *(.rodata)

        . = ALIGN(4);
    } >FLASH

    .data : ALIGN(4)
    {
        __data_start_lma = LOADADDR(.data);
        __data_start = .;
        *(.data)
        __data_end = .;

        . = ALIGN(4);
    } >RAM AT >FLASH

    .bss : ALIGN(4)
    {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;

        . = ALIGN(4);
    } >RAM

    .stack : ALIGN(4)
    {
        __stack_start = .;
        . = . + 1K;
        __stack_end = .;

        . = ALIGN(4);
    }

    /* /DISCARD/ : { *(*) } */
}
