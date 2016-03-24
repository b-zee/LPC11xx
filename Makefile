OBJECTS = core_cm0.o system_LPC11xx.o vector_table.o startup.o main.o

BIN = LPC1114FN28.bin
ELF = LPC1114FN28.elf
HEX = LPC1114FN28.hex
LD  = LPC1114FN28.ld
MAP = LPC1114FN28.map

all: clean $(HEX)


$(HEX): $(ELF)
	arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)
	arm-none-eabi-objcopy -O binary $(ELF) $(BIN)

$(ELF): $(OBJECTS) $(LD)
	arm-none-eabi-gcc -nostartfiles -T $(LD) -Wl,-Map,$(MAP) -Wl,-gc-sections -o $(ELF) $(OBJECTS)

%.o: %.c
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -o $@ -c $<


clean:
	rm -rf $(OBJECTS)
	rm -rf $(BIN) $(ELF) $(HEX) $(MAP)
