#include "zmn.h"

#include <LPC11xx.h>

void zmn_init(void)
{
    SystemInit();
    SystemCoreClockUpdate();
}

uint32_t zmn_device_id(void)
{
    return LPC_SYSCON->DEVICE_ID;
}
