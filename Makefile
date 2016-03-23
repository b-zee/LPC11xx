BIN = bin/
INC = inc/
OBJ = obj/
SRC = src/

ELF = $(BIN)LPC1114FN28.elf
HEX = $(BIN)LPC1114FN28.hex
LD  = LPC1114FN28.ld
MAP = $(BIN)LPC1114FN28.map

OBJECTS = $(OBJ)core_cm0.o $(OBJ)system_LPC11xx.o $(OBJ)vector_table.o $(OBJ)startup.o $(OBJ)main.o


all: $(HEX)


$(HEX): $(ELF)
	arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)

$(ELF): $(OBJECTS) $(LD)
	arm-none-eabi-gcc -fno-ident  -nostartfiles -nodefaultlibs -Wl,--gc-sections -Wl,-Map,$(MAP) -T $(LD) -o $(ELF) $(OBJECTS)

$(OBJ)%.o: $(SRC)%.c
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -o $@ -I"$(INC)" -c $<


clean:
	rm -rf $(OBJECTS)
	rm -rf $(ELF) $(MAP) $(HEX)
