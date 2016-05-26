#include "zmn.h"

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
}
