MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 32K
    RAM   (rwx) : ORIGIN = 0x10000000, LENGTH =  4K
}

__stack_size = 1K;

ENTRY(_start)

SECTIONS
{
    .text : ALIGN(4)
    {
        KEEP(*(.vectors))
        *(.text .text.*)
        *(.rodata)
    } >FLASH

    .data : ALIGN(4)
    {
        __data_start_lma = LOADADDR(.data);
        __data_start = .;
        *(.data)
        __data_end = .;
    } >RAM AT >FLASH

    .bss : ALIGN(4)
    {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;
    } >RAM

    .stack : ALIGN(4)
    {
        __stack_start = .;
        . = ORIGIN(RAM) + LENGTH(RAM) - 4;
        __stack_end = .;
    } >RAM

    /* /DISCARD/ : { *(*) } */
}
