# LPC11xx

Software to control an LPC11xx device.

## Installation

This project uses [GNU Make](https://www.gnu.org/software/make/) to build the project.

`make upload` uploads the image to the LPC11xx. By default to `/dev/ttyUSB0`, but can manually provided, just like the BAUD rate, which is 19200 by default:

    make TTY=COM4 BAUD=9600 upload


## Features

- Controlling logical levels of GPIOs;
- Pulse width modulation;
- Analog digital converter;
- Writing to UART.

### Future

- Handling interrupts and exceptions;
- Threading.


## Requirements

To build the software an `arm-none-eabi` toolchain is needed, and to upload the software [`lpc21isp`](http://sourceforge.net/projects/lpc21isp/) is used.
