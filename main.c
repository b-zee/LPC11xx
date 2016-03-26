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
void adc_initialize(void) {
    LPC_IOCON->R_PIO1_0       &= ~0x87;        // reset FUNC (first 3 bits) and ADMODE to 0 (analog input mode)
    LPC_IOCON->R_PIO1_0       |= (1 << 1);     // set pin as analog input (AD1)
    LPC_IOCON->R_PIO1_0       &= ~(0x03 << 3);
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 13);    // Enable ADC clock
    LPC_SYSCON->PDRUNCFG      &= ~(1 << 4);    // enable power to ADC
    LPC_ADC->CR               &= ~0x1FFFF;     // reset pin select, clkdiv and burst to 0
    LPC_ADC->CR               |= 0x202;        // select pin AD1 and set clkdiv to 2. PCLK == 12, so 12/(2+1)== 4Mhz APB clock
    LPC_ADC->CR               &= ~(0x7 << 24); // reset all start conversion bits to 0
}
uint32_t adc_get(void) {
    LPC_ADC->CR |= (1 << 24);

    while((LPC_ADC->GDR & (1 << 31)) == 0);

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
    // Set pin 1.1 to function CT32B1_MAT0
    LPC_IOCON->R_PIO1_1 &= ~0x7;
    LPC_IOCON->R_PIO1_1 |=  0x3;


    // Enable TMR32B1
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 10);

    // TC increments every PR+1 (12 MHz / 12 = 1 MHz = 1 tick per microsecond)
    LPC_TMR32B1->PR = 256 - 1;

    LPC_TMR32B1->MR0 = 30000;     // TC match
    LPC_TMR32B1->MR3 = 65536 - 1; // Period

    // Enable PWM modes for MAT0
    LPC_TMR32B1->PWMC |= (1 << 0);

    // Reset counter when MR3 is matched
    LPC_TMR32B1->MCR |= (1 << 10);

    // Enable counter
    LPC_TMR32B1->TCR |= (1 << 0);
}


int main(void)
{
    sys_init();
    uart_init();
    //timer_init();
    //adc_initialize();
    pwm_init();

    uart_puts("Hello, World.\n");

    GPIO_LO(LPC_GPIO1, 1);
    uart_puti(GPIO_GET(LPC_GPIO1, 1));
    uart_putc('\n');

    while (1) {
        uart_puti(LPC_TMR32B1->TC);
        uart_putc('-');
        uart_puti(GPIO_GET(LPC_GPIO1, 1));
        uart_putc('\n');
    }

    /*while (1) {
        uart_putu(adc_get());
        uart_putc('\n');
    }*/

    /* //Software PWM

    GPIO_OUT(LPC_GPIO1, 8); // Configure as output

    const uint32_t period1 = 2300,
                   period2 = 20000 - period1;

    uint32_t post = timer_count();

	while (1) {
        GPIO_HI(LPC_GPIO1, 8);

        post += period1;
        while (timer_count() < post);

        GPIO_LO(LPC_GPIO1, 8);

        post += period2;
        while (timer_count() < post);
    }*/

    while (1);

	return 0;
}
