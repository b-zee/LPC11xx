#include "LPC11xx.h"

#include <stddef.h>
#include <stdint.h>


// Set pin from port to input or output direction
#define GPIO_IN(port, pin)   (port->DIR  &= ~(1 << pin))
#define GPIO_OUT(port, pin)  (port->DIR  |=  (1 << pin))
// Set pin from port to low or high logical state
#define GPIO_LO(port, pin)   (port->DATA &= ~(1 << pin))
#define GPIO_HI(port, pin)   (port->DATA |=  (1 << pin))
#define GPIO_GET(port, pin)  (port->DATA & (1 << pin))


#define IRC_FREQ          12000000UL
#define SYSAHBCLKDIV_int  0x01
#define   UARTCLKDIV_int  0x01

#define BAUD_RATE     19200
#define UART_DIVISOR  (IRC_FREQ / SYSAHBCLKDIV_int / UARTCLKDIV_int / BAUD_RATE / 16)


static void sys_init(void)
{
    LPC_SYSCON->SYSAHBCLKDIV   = SYSAHBCLKDIV_int;
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
    LPC_SYSCON->UARTCLKDIV     = UARTCLKDIV_int;

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
void uart_putu(uint32_t i)
{
    // Approximation of chars needed to fit int digits
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

// Todo: specify port and pin
void adc_init(void) {
    // Set FUNC to AD1
    LPC_IOCON->R_PIO1_0 &= ~(0x7 << 0);
    LPC_IOCON->R_PIO1_0 |=  (0x2 << 0);

    // Set MODE to inactive
    LPC_IOCON->R_PIO1_0 &= ~(0x3 << 3);

    // Set ADMODE to analog input
    LPC_IOCON->R_PIO1_0 &= ~(0x1 << 7);

    // Enable AD clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 13);

    // Make ADC powered
    LPC_SYSCON->PDRUNCFG      &= ~(1 << 4);

    // Select AD1 to be sampled
    LPC_ADC->CR  &= ~0xFF;
    LPC_ADC->CR  |= (1 << 1);
    //LPC_ADC->CR  &= ~0x1FFFF;     // reset pin select, clkdiv and burst to 0

    // Set clock divider to 2 so 12 / 3 == 4 MHz
    LPC_ADC->CR  &= ~(0xFF   << 8);
    LPC_ADC->CR  |= ((3 - 1) << 8);

    // Reset START
    //LPC_ADC->CR  &= ~(0x7 << 24);
}
uint16_t adc_get(void) {
    // Start conversion
    LPC_ADC->CR |= (1 << 24);

    // Wait for DONE bit to be set.
    while((LPC_ADC->GDR & (1 << 31)) == 0);

    // Return binary fraction result from conversion
    return ((LPC_ADC->GDR & 0xFFC0) >> 6);
}


void timer_init()
{
    // Enable TMR32B0
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);

    // Enable the counter
    LPC_TMR32B0->TCR |= (1 << 0);

    // TC increments every PR+1 (12 MHz / 12 = 1 MHz = 1 tick per microsecond)
    LPC_TMR32B0->PR = 12 - 1;
}
uint32_t timer_count(void)
{
    return LPC_TMR32B0->TC;
}
void wait(uint32_t usec)
{
    const uint32_t post = timer_count() + usec;
    while (timer_count() < post);
}


void pwm_init(void)
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


int a = 3;
int b;

int main(void)
{
    sys_init();
    uart_init();
    timer_init();
    adc_init();
    pwm_init();

    uart_puts("Hello from the other side.\nHappy hacking.\n\n");

    volatile int16_t v1 = adc_get();
    volatile int16_t min = v1 - 32, max = v1 + 32;
    while (1) {
        do {
            v1 = adc_get();
        } while (v1 > min && v1 < max);
        min = v1 - 32;
        max = v1 + 32;

        LPC_TMR16B1->MR0 = 18000 + v1;
        uart_puti(v1);
        uart_putc('\n');
    }

    while (1);
	return 0;
}
