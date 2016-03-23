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
        *(.vectors)
        *(.text)
        *(.rodata)
    } >FLASH

    . = ORIGIN(RAM);
    .data : {
        *(.data)
    } >RAM AT >FLASH
    .bss : {
        *(.bss)
        *(COMMON)
    } >RAM

    . = ALIGN(4);
    . = . + 0x1000;
    stack_top = .;

    /* /DISCARD/ : { *(*) } */
}
