#include "LPC11xx.h"

#include <stdint.h>

int main(void)
{
	LPC_GPIO1->DIR  |= (1 << 8); // Configure as output

    volatile uint32_t count, count_max = 200000;

	while (1) {
        LPC_GPIO1->DATA |= (1 << 8); // Set level to high

        for (count = 0; count < count_max; count++);

        LPC_GPIO1->DATA &= ~(1 << 8); // Set level to low

        for (count = 0; count < count_max; count++);
    };

	return 0;
}
