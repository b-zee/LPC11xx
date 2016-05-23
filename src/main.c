#include "zmn.h"

#include <LPC11xx.h>

void t1(void)
{
    zmn_gpio_out(LPC_GPIO1, 9);

    uint32_t until = zmn_timer_get() + 1000 * 100;

    while (1) {
        zmn_gpio_set(LPC_GPIO1, 9);

        while (zmn_timer_get() < until);
        until += 1000 * 100;

        zmn_gpio_clear(LPC_GPIO1, 9);

        while (zmn_timer_get() < until);
        until += 1000 * 100;
    }
}

void t2(void)
{
    zmn_gpio_out(LPC_GPIO1, 8);

    uint32_t until = zmn_timer_get() + 1000 * 100;

    while (1) {
        zmn_gpio_set(LPC_GPIO1, 8);

        while (zmn_timer_get() < until);
        until += 1000 * 100;

        zmn_gpio_clear(LPC_GPIO1, 8);

        while (zmn_timer_get() < until);
        until += 1000 * 100;
    }
}

void main(void)
{
    zmn_init();
    zmn_uart_init();
    zmn_timer_init();

    zmn_thread_init();
    zmn_thread_create(t1);
    zmn_thread_create(t2);

    zmn_uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    // Echo back
    while (1) {
        zmn_uart_putc(zmn_uart_getc());
    }
}
