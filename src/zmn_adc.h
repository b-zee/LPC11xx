#ifndef ZMN_ADC_H
#define ZMN_ADC_H

#include <stdint.h>

/**
 * @brief  Setup Analog Digital Converter peripheral for conversion.
 */
void zmn_adc_init(void);

/**
 * @brief  Start and retreive the result of a conversion.
 *
 * @return  Digital value in the range [0, 1024)
 */
uint16_t zmn_adc_get(void);

#endif
