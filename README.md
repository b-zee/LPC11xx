# LPC11xx

Software to control an LPC11xx device.

## Installation

This project uses [GNU Make](https://www.gnu.org/software/make/) to build the project.

`make upload` uploads the image to the LPC11xx. By default to `/dev/ttyUSB0` with BAUD rate 19200, but can be manually provided:

    make TTY=COM4 BAUD=9600 upload


## Features

- Controlling logical levels of GPIOs;
- Pulse width modulation;
- Analog digital converter;
- Writing to UART.

### Future

- Reading from UART;
- Handling interrupts and exceptions;
- Threading.


## Requirements

To build the software an `arm-none-eabi` toolchain is needed, and to upload the software [`lpc21isp`](http://sourceforge.net/projects/lpc21isp/) is used.


## License

This project is licensed under GPLv3. See `/LICENSE` file for the complete license.
