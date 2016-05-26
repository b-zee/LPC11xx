#include "zmn_timer.h"

#include <LPC11xx.h>

void zmn_timer_init(void)
{
    // Enable CT32B0
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);

    // TC increments every PR+1 (12 MHz / 12 = 1 MHz = 1 tick per microsecond)
    LPC_TMR32B0->PR = 12 - 1;

    // Enable the counter
    LPC_TMR32B0->TCR |= (1 << 0);
}
uint32_t zmn_timer_get(void)
{
    return LPC_TMR32B0->TC;
}
