#include "sys.h"
#include "uart.h"
#include "timer.h"

#include <LPC11xx.h>

void t1(void)
{
    GPIO_OUT(LPC_GPIO1, 9);

    uint32_t until = timer_get() + 1000 * 100;

    while (1) {
        GPIO_HI(LPC_GPIO1, 9);

        while (timer_get() < until);
        until += 1000 * 100;

        GPIO_LO(LPC_GPIO1, 9);

        while (timer_get() < until);
        until += 1000 * 100;
    }
}

void t2(void)
{
    GPIO_OUT(LPC_GPIO1, 8);

    uint32_t until = timer_get() + 1000 * 100;

    while (1) {
        GPIO_HI(LPC_GPIO1, 8);

        while (timer_get() < until);
        until += 1000 * 100;

        GPIO_LO(LPC_GPIO1, 8);

        while (timer_get() < until);
        until += 1000 * 100;
    }
}

void main(void)
{
    sys_init();
    uart_init();
    timer_init();

    uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    // Echo back
    while (1) {
        uart_putc(uart_getc());
    }
}
