// Default handler function declaration
void default_handler(void) __attribute__ ((interrupt));

extern char stack_top;
extern void _start(void);

// Function pointer type
typedef void (*handler)(void);

// Array of function pointers
const handler table[]  __attribute__ ((section(".vectors"))) = {
    (handler)&stack_top, /* 0x00 - SP */
    _start,          /* 0x04 - Reset (PC) */
    default_handler, /* 0x08 - NMI */
    default_handler, /* 0x0C - HardFault*/
    default_handler, /* 0x10 - -Reserved- */
    default_handler, /* 0x14 - -Reserved- */
    default_handler, /* 0x18 - -Reserved- */
    default_handler, /* 0x1C - -Reserved- */
    default_handler, /* 0x20 - -Reserved- */
    default_handler, /* 0x24 - -Reserved- */
    default_handler, /* 0x28 - -Reserved- */
    default_handler, /* 0x2C - SVCall */
    default_handler, /* 0x30 - -Reserved- */
    default_handler, /* 0x34 - -Reserved- */
    default_handler, /* 0x38 - PendSV */
    default_handler, /* 0x3C - SysTick */
    default_handler, /* 0x40 - IRQ1 */
    default_handler, /* 0x44 - IRQ2 */
    default_handler, /* 0x48 - IRQ3 */
    default_handler, /* 0x4C - IRQ4 */
    default_handler, /* 0x50 - IRQ5 */
    default_handler, /* 0x54 - IRQ6 */
    default_handler, /* 0x58 - IRQ7 */
    default_handler, /* 0x5C - IRQ8 */
    default_handler, /* 0x60 - IRQ9 */
    default_handler, /* 0x64 - IRQ10 */
    default_handler, /* 0x68 - IRQ11 */
    default_handler, /* 0x6C - IRQ12 */
    default_handler, /* 0x70 - IRQ13 */
    default_handler, /* 0x74 - IRQ14 */
    default_handler, /* 0x78 - IRQ15 */
    default_handler, /* 0x7C - IRQ16 */
    default_handler, /* 0x80 - IRQ17 */
    default_handler, /* 0x84 - IRQ18 */
    default_handler, /* 0x88 - IRQ19 */
    default_handler, /* 0x8C - IRQ20 */
    default_handler, /* 0x90 - IRQ21 */
    default_handler, /* 0x94 - IRQ22 */
    default_handler, /* 0x98 - IRQ23 */
    default_handler, /* 0x9C - IRQ24 */
    default_handler, /* 0xA0 - IRQ25 */
    default_handler, /* 0xA4 - IRQ26 */
    default_handler, /* 0xA8 - IRQ27 */
    default_handler, /* 0xAC - IRQ28 */
    default_handler, /* 0xB0 - IRQ29 */
    default_handler, /* 0xB4 - IRQ30 */
    default_handler, /* 0xB8 - IRQ31 */
    default_handler  /* 0xBC - IRQ32 */
};

void default_handler(void) {}
