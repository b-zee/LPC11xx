/**
 * @author Benno Zeeman <bzeeman@live.nl>
 * @todo   Make use of burst mode for more accurate measuring
 * @todo   Allow selecting specific pin
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

#include "zmn_adc.h"

#include <LPC11xx.h>

/**
 * @details  The conversion is setup to use pin 1-0, function AD1. It uses a 4 MHz clock.
 */
void zmn_adc_init(void)
{
    // Enable AD clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 13);

    // Make ADC powered
    LPC_SYSCON->PDRUNCFG &= ~(1 << 4);

    // Set pin 1-0 FUNC to AD1
    LPC_IOCON->R_PIO1_0 &= ~(0x7 << 0);
    LPC_IOCON->R_PIO1_0 |=  (0x2 << 0);

    // Set MODE to inactive
    LPC_IOCON->R_PIO1_0 &= ~(0x3 << 3);

    // Set ADMODE to analog input
    LPC_IOCON->R_PIO1_0 &= ~(0x1 << 7);

    // Select AD1 to be sampled
    LPC_ADC->CR &= ~0xFF;
    LPC_ADC->CR |=  0x02; // 0000 0010
    //LPC_ADC->CR  &= ~0x1FFFF;     // reset pin select, clkdiv and burst to 0

    // Set clock divider to 12 / (CLKDIV + 1) == 4 MHz (< 4.5 MHz)
    LPC_ADC->CR &= ~(0xFF   << 8);
    LPC_ADC->CR |= ((3 - 1) << 8);

    // Reset START
    //LPC_ADC->CR  &= ~(0x7 << 24);
}

uint16_t zmn_adc_get(void)
{
    // Start conversion
    LPC_ADC->CR |= (1 << 24);

    // Wait for DONE bit to be set.
    while ((LPC_ADC->GDR & (1 << 31)) == 0);

    // Return binary fraction result from conversion
    return ((LPC_ADC->GDR & 0xFFC0) >> 6);
}
