#include "adc.h"

#include <LPC11xx.h>

// Todo: specify port and pin
void adc_init(void)
{
    // Enable AD clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 13);

    // Make ADC powered
    LPC_SYSCON->PDRUNCFG &= ~(1 << 4);

    // Set FUNC to AD1
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
uint16_t adc_get(void)
{
    // Start conversion
    LPC_ADC->CR |= (1 << 24);

    // Wait for DONE bit to be set.
    while ((LPC_ADC->GDR & (1 << 31)) == 0);

    // Return binary fraction result from conversion
    return ((LPC_ADC->GDR & 0xFFC0) >> 6);
}
