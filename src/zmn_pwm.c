#include "zmn_pwm.h"

#include <LPC11xx.h>

void zmn_pwm_init(void)
{
    // Set pin 1.1 to function CT16B1_MAT0
    LPC_IOCON->PIO1_9 &= ~0x7;
    LPC_IOCON->PIO1_9 |=  0x1;


    // Enable TMR16B1
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 8);

    // TC increments every PR+1
    LPC_TMR16B1->PR = 12 - 1;

    LPC_TMR16B1->MR0 = 18500; // LOW duration
    LPC_TMR16B1->MR1 = 20000; // Period

    // Enable PWM mode for MAT0
    LPC_TMR16B1->PWMC |= (1 << 0);

    // Reset counter when MR1 is matched
    LPC_TMR16B1->MCR |= (1 << 4);

    // Enable counter
    LPC_TMR16B1->TCR |= (1 << 0);
}
