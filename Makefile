TTY  ?= /dev/ttyUSB0
BAUD ?= 115200

FILE   = _start main
#core_cm0 system_LPC11xx
OBJECT = $(addsuffix .o,   $(FILE))
LST    = $(addsuffix .lst, $(FILE))


# File names
BIN = LPC1114FN28.bin
ELF = LPC1114FN28.elf
HEX = LPC1114FN28.hex
LD  = LPC1114FN28.ld
MAP = LPC1114FN28.map

# C compiler flags
C_FLAGS = -std=c11 -O0 -mcpu=cortex-m0 -mthumb
# -Wall -Wextra -Werror -pedantic


all: clean $(HEX) $(BIN) $(LST)
	@size $(OBJECT) $(HEX) $(ELF)


$(HEX): $(ELF)
	arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $(ELF) $(BIN)

$(ELF): $(LD) $(OBJECT)
	arm-none-eabi-gcc -nostartfiles -T $(LD) -Wl,-Map,$(MAP) -o $(ELF) $(OBJECT)
#-Wl,-gc-sections


%.o: %.c
	arm-none-eabi-gcc $(C_FLAGS) -g -o $@ -c $<

%.lst: %.o
	arm-none-eabi-objdump -S -d $< > $@


clean:
	rm -rf $(OBJECT) $(LST)
	rm -rf $(BIN) $(ELF) $(HEX) $(MAP)


upload: $(BIN)
	lpc21isp -control -verify -term -bin $(BIN) $(TTY) $(BAUD) 12000
#	lpc21isp -termonly $(TTY) $(BAUD) 12000
