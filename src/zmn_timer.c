/**
 * @brief   Timer interface
 * @author  Benno Zeeman <bzeeman@live.nl>
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
