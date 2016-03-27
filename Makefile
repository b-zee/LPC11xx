TTY  ?= /dev/ttyUSB0
BAUD ?= 19200

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
C_FLAGS  = -mcpu=cortex-m0 -mthumb
C_FLAGS += -std=c11 -O0
#C_FLAGS += -ffunction-sections -fdata-sections
C_FLAGS += $(if $(DEBUG), -g) -fverbose-asm
#-Wall -Wextra -Werror -pedantic


all: clean $(LST) $(HEX) $(BIN)
	@size $(OBJECT) $(HEX) $(ELF)


$(HEX): $(ELF)
	arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $(ELF) $(BIN)

$(ELF): $(LD) $(OBJECT)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -nostartfiles -nostdlib -nodefaultlibs -T $(LD) -Wl,-Map,$(MAP) -o $(ELF) $(OBJECT) -lgcc
#-Wl,-gc-sections


%.o: %.c
	arm-none-eabi-gcc $(C_FLAGS) -o $@ -c $<

%.lst: %.c
	arm-none-eabi-gcc $(C_FLAGS) -o $@ -S $<
#	arm-none-eabi-objdump -S -d $< > $@


clean:
	rm -rf $(OBJECT) $(LST)
	rm -rf $(BIN) $(ELF) $(HEX) $(MAP)


upload: $(BIN)
	lpc21isp -control -verify -term -bin -logfile $(BIN) $(TTY) $(BAUD) 12000
#	lpc21isp -termonly $(TTY) $(BAUD) 12000
