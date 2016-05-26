#ifndef ZMN_H
#define ZMN_H

#include <stdint.h>
#include <LPC11xx.h>


#include "zmn_adc.h"
#include "zmn_gpio.h"
#include "zmn_pwm.h"
#include "zmn_routines.h"
#include "zmn_thread.h"
#include "zmn_timer.h"
#include "zmn_uart.h"


void     zmn_init(void);
uint32_t zmn_device_id(void);

#endif
