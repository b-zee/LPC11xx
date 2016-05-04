#include "sys.h"
#include "uart.h"

#include <LPC11xx.h>

int main(void)
{
    sys_init();
    uart_init();
    //timer_init();
    //adc_init();
    //pwm_init();

    uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    uint32_t a = __get_MSP();
    uart_putu(a);

    while (1);
	return 0;
}
