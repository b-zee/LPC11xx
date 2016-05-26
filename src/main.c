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

    int a,b;
    a = 3;
    b = 4;
    b = a + b;

    zmn_uart_puti(b);
    zmn_uart_putc('\n');

    uint32_t psp = __get_PSP();

    zmn_uart_putu(psp);

    while (1);
}
