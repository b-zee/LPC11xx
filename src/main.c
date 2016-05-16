#include "sys.h"
#include "uart.h"


void main(void)
{
    sys_init();
    uart_init();
    //timer_init();
    //adc_init();
    //pwm_init();

    uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    while (uart_getc() != '\n');

    uart_putu(sys_device_id());
}
