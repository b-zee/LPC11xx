#include <LPC11xx.h>
#include "system_LPC11xx.h"

#define LED (1 << 9)   /* PIO1_9 */

int main(void)
{
	LPC_SYSCON ->SYSAHBCLKCTRL |= (1 << 8); // Enable Clock for TMR1
	LPC_IOCON ->PIO1_9 |= (1 << 0);         // PIN1_9 = CT16B1_MAT0
	LPC_TMR16B1->MR0  = 2000;               // 50% Duty Cycle
	LPC_TMR16B1->PR   = 12000;
	LPC_TMR16B1->MR3  = 4000;          // Cycle Length
	LPC_TMR16B1->MCR  |= (1 << 10);    // TC Reset on MR3 Match
	LPC_TMR16B1->PWMC |= (1 << 0);     // PWM Mode
	LPC_TMR16B1->TCR  |= (1 << 0);     // GO
	while (1) {};

	return 0;
}
