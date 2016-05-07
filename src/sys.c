#include "sys.h"

#include "config.h"
#include <LPC11xx.h>

void sys_init(void)
{
    LPC_SYSCON->SYSAHBCLKDIV   = SYSAHBCLKDIV_int;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);
}

uint32_t sys_device_id(void)
{
    return LPC_SYSCON->DEVICE_ID;
}
