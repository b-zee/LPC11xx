#include "LPC11xx.h"


#define IRC_FREQ           12000000UL
#define SYSAHBCLKDIV_value 0x01
#define   UARTCLKDIV_value 0x01

#define BAUD_RATE    19200
#define UART_DIVISOR (IRC_FREQ / SYSAHBCLKDIV_value / UARTCLKDIV_value / BAUD_RATE / 16)


static void sys_init(void)
{
    LPC_SYSCON->SYSAHBCLKDIV   = SYSAHBCLKDIV_value;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 16);
}

// Assumes values have reset values
void uart_init()
{
    // Set RXD and TXD functions
    LPC_IOCON->PIO1_6 = (LPC_IOCON->PIO1_6 & ~0x7) | 0x1;
    LPC_IOCON->PIO1_7 = (LPC_IOCON->PIO1_7 & ~0x7) | 0x1;

    // Enable clock for UART
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);
    LPC_SYSCON->UARTCLKDIV     = UARTCLKDIV_value;

    // Set Word Length Select to 8-bit character length
    LPC_UART->LCR &= ~0x3;
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

void uart_putc(const char c)
{
    while(!(LPC_UART->LSR & (1 << 6)))
        ;

    LPC_UART->THR = c;
}

void uart_puts(const char *str)
{
    while (*str != '\0') {
        uart_putc(*str++);
    }
}

void uart_puti(int i)
{
    do {
        uart_putc(i % 10 + '0');
    } while (i /= 10);
}

int main(void)
{
    sys_init();

    uart_init();

    uart_puts("AB");
    uart_putc('0');
    uart_puts("CD");
    uart_puti(10);
    uart_puts("EF");
    //uart_puts("ABCDEF");

    LPC_GPIO1->DIR |= (1 << 8); // Configure as output

    volatile uint32_t count;
    volatile const uint32_t count_max = 100000;


	while (1) {
        LPC_GPIO1->DATA |= (1 << 8); // Set level to high

        for (count = 0; count < count_max; count++);

        LPC_GPIO1->DATA &= ~(1 << 8); // Set level to low

        for (count = 0; count < count_max; count++);
    }

	return 0;
}
