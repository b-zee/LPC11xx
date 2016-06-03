/**
 * @brief   UART interface
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

#include "zmn_uart.h"

#include <LPC11xx.h> // LPC_
#include <stddef.h>  // size_t

void zmn_uart_init(void)
{
    // Enable clock for UART
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);
    //LPC_SYSCON->UARTCLKDIV     = 1; // Already done by SystemInit

    // Set RXD and TXD functions
    LPC_IOCON->PIO1_6 = (LPC_IOCON->PIO1_6 & ~0x7) | 0x1;
    LPC_IOCON->PIO1_7 = (LPC_IOCON->PIO1_7 & ~0x7) | 0x1;

    // Set Word Length Select to 8-bit character length
    LPC_UART->LCR |= 0x3;

    // Enable access to Divisor Latches
    LPC_UART->LCR |= (1 << 7);

    // Write divisor to latches
    uint16_t uart_divisor = SystemCoreClock / LPC_SYSCON->SYSAHBCLKDIV / LPC_SYSCON->UARTCLKDIV / BAUD_RATE / 16;
    LPC_UART->DLM = (uart_divisor >> 8) & 0xFF;
    LPC_UART->DLL = (uart_divisor >> 0) & 0xFF;

    // Enable fractional baud rate generator
    //LPC_UART->U0LCR &= ~0xFF;
    //LPC_UART->U0LCR |= (1 << 4) | (1 << 0);

    // Enable FIFO
    LPC_UART->FCR |= (1 << 0);

    // Disable access to Divisor Latches (thus allowing to put chars in THR)
    LPC_UART->LCR &= ~(1 << 7);
}
char zmn_uart_getc(void) {
    while (!(LPC_UART->LSR & (1 << 0)))
        ;

    return LPC_UART->RBR;
}
void zmn_uart_putc(const char c)
{
    while (!(LPC_UART->LSR & (1 << 6)))
        ;

    LPC_UART->THR = c;
}
void zmn_uart_puts(const char *str)
{
    while (*str != '\0') {
        zmn_uart_putc(*str++);
    }
}
void zmn_uart_putu(uint32_t i)
{
    // Approximation of chars needed to fit digits
    char buffer[sizeof(i) * 8 / 3];
    size_t index = 0;
    do {
        buffer[index++] = i % 10 + '0';
    } while (i /= 10);

    while (index--) {
        zmn_uart_putc(buffer[index]);
    }
}
void zmn_uart_puti(int32_t i)
{
    if (i < 0) {
        zmn_uart_putc('-');
        i = -i;
    }
    zmn_uart_putu(i);
}
