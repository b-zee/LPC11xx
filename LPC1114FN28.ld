MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 32K
    RAM   (rwx) : ORIGIN = 0x10000000, LENGTH =  4K
}

ENTRY(_start)

SECTIONS
{
    . = ORIGIN(FLASH);
    .text : {
        KEEP(*(.vectors))
        *(.text)
        *(.rodata)
    } >FLASH

    . = ORIGIN(RAM);
    .data : {
        *(.data)
    } >RAM AT >FLASH

    __bss_start = .;
    .bss : {
        *(.bss)
        *(COMMON)
    } >RAM
    __bss_end = .;

    . = ALIGN(4);
    __stack_start = .;
    . = . + 1K;
    __stack_end = .;

    /* /DISCARD/ : { *(*) } */
}
