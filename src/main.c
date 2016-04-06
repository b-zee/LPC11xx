#include "sys.h"
#include "uart.h"

int main(void)
{
    sys_init();
    uart_init();
    //timer_init();
    //adc_init();
    //pwm_init();

    uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    while (1);
	return 0;
}
