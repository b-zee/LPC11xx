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
    //zmn_thread_create(t1);
    //zmn_thread_create(t2);

    zmn_uart_puts("main\n");

    zmn_uart_putu(__get_PSP());
    zmn_uart_putc('\n');

    zmn_uart_putu(__get_MSP());
    zmn_uart_putc('\n');

    while (1);
}
