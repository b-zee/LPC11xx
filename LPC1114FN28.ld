MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 32K
    RAM   (rwx) : ORIGIN = 0x10000000, LENGTH =  4K
}

ENTRY(_start)

SECTIONS
{
    .text : {
        KEEP(*(.vectors))
        *(.text)
        *(.rodata)
    } >FLASH

    .data : {
        __data_start_lma = LOADADDR(.data);
        __data_start = .;
        *(.data)
        __data_end = .;
    } >RAM AT >FLASH

    .bss : {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;
    } >RAM

    .stack ALIGN(4) : {
        __stack_start = .;
        . = . + 1K;
        __stack_end = .;
    }

    /* /DISCARD/ : { *(*) } */
}
