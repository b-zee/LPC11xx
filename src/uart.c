#include "uart.h"

#include "config.h"

#include <LPC11xx.h>
#include <stddef.h>

void uart_init(void)
{
    // Set RXD and TXD functions
    LPC_IOCON->PIO1_6 = (LPC_IOCON->PIO1_6 & ~0x7) | 0x1;
    LPC_IOCON->PIO1_7 = (LPC_IOCON->PIO1_7 & ~0x7) | 0x1;

    // Enable clock for UART
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);
    LPC_SYSCON->UARTCLKDIV     = UARTCLKDIV_int;

    // Set Word Length Select to 8-bit character length
    LPC_UART->LCR |= 0x3;

    // Enable access to Divisor Latches
    LPC_UART->LCR |= (1 << 7);

    // Write divisor to latches
    LPC_UART->DLM = (UART_DIVISOR >> 8) & 0xFF;
    LPC_UART->DLL = (UART_DIVISOR >> 0) & 0xFF;

    // Enable fractional baud rate generator
    //LPC_UART->U0LCR &= ~0xFF;
    //LPC_UART->U0LCR |= (1 << 4) | (1 << 0);

    // Enable FIFO
    LPC_UART->FCR |= (1 << 0);

    // Disable access to Divisor Latches (thus allowing to put chars in THR)
    LPC_UART->LCR &= ~(1 << 7);
}
char uart_getc(void) {
    while (!(LPC_UART->LSR & (1 << 0)))
        ;

    return LPC_UART->RBR;
}
void uart_putc(const char c)
{
    while (!(LPC_UART->LSR & (1 << 6)))
        ;

    LPC_UART->THR = c;
}
void uart_puts(const char *str)
{
    while (*str != '\0') {
        uart_putc(*str++);
    }
}
void uart_putu(uint32_t i)
{
    // Approximation of chars needed to fit digits
    char buffer[sizeof(i) * 8 / 3];
    size_t index = 0;
    do {
        buffer[index++] = i % 10 + '0';
    } while (i /= 10);

    while (index--) {
        uart_putc(buffer[index]);
    }
}
void uart_puti(int32_t i)
{
    if (i < 0) {
        uart_putc('-');
        i = -i;
    }
    uart_putu(i);
}
