#include "zmn.h"

#include <LPC11xx.h>

void t1(void)
{
    zmn_uart_puts("t1\n");
}

void t2(void)
{
    zmn_uart_puts("t2\n");
}

void main(void)
{
    zmn_init();
    zmn_uart_init();
    zmn_timer_init();

    zmn_thread_init();
    //zmn_thread_create(t1);
    //zmn_thread_create(t2);

    zmn_uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    // Echo back
    while (1) {
        zmn_uart_putc(zmn_uart_getc());
    }
}
