#include "sys.h"
#include "uart.h"

#include <LPC11xx.h>

void sys_init(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    (void)SysTick_Config(SystemCoreClock); // Todo: error handling
}

uint32_t sys_device_id(void)
{
    return LPC_SYSCON->DEVICE_ID;
}

__attribute__ ((interrupt)) void _sys_tick(void)
{
    uart_puts("_sys_tick\n");

    SCB->ICSR |= 1 << 28; // Trigger PendSV
}

__attribute__ ((interrupt)) void _pendSV(void)
{
    uart_puts("_pendSV\n");
}
