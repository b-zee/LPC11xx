/**
 * @brief   Pulse Width Modulation interface
 * @author  Benno Zeeman <bzeeman@live.nl>
 * @todo    Configurable period time
 * @todo    Allow selecting pin other than 1.9
 */
//  Copyright (C) 2016 Benno Zeeman
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "zmn_pwm.h"

#include <LPC11xx.h>

void zmn_pwm_init(void)
{
    // Set pin 1.9 to function CT16B1_MAT0
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
