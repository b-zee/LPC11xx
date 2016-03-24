OBJECTS = _start.o main.o
# core_cm0.o system_LPC11xx.o

BIN = LPC1114FN28.bin
ELF = LPC1114FN28.elf
HEX = LPC1114FN28.hex
LD  = LPC1114FN28.ld
MAP = LPC1114FN28.map

all: clean $(HEX) $(BIN)


$(HEX): $(ELF)
	arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $(ELF) $(BIN)

$(ELF): $(OBJECTS) $(LD)
	arm-none-eabi-gcc -nostartfiles -T $(LD) -Wl,-Map,$(MAP) -o $(ELF) $(OBJECTS) #-Wl,-gc-sections
	arm-none-eabi-readelf -S $(ELF)

%.o: %.c
	arm-none-eabi-gcc -std=c11 -mcpu=cortex-m0 -mthumb -O0 -o $@ -c $<
# -Wall -Wextra -Werror -pedantic

clean:
	rm -rf $(OBJECTS)
	rm -rf $(BIN) $(ELF) $(HEX) $(MAP)

upload: $(BIN)
	lpc21isp -control -verify -term -bin $(BIN) /dev/ttyUSB0 115200 12000
