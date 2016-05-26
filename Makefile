TTY  ?= /dev/ttyUSB0
BAUD ?= 19200

# Folders
SRC = src/
LPC = LPC11xx/

C_FILES = $(basename $(wildcard $(SRC)*.c)) $(basename $(wildcard $(LPC)*.c))
S_FILES = $(basename $(wildcard $(SRC)*.S))
OBJ     = $(addsuffix .o,   $(S_FILES) $(C_FILES))
ASM     = $(addsuffix .asm, $(C_FILES))

# File names
BIN = $(SRC)LPC1114FN28.bin
ELF = $(SRC)LPC1114FN28.elf
HEX = $(SRC)LPC1114FN28.hex
LD  = $(SRC)LPC1114FN28.ld
MAP = $(SRC)LPC1114FN28.map

# C compiler flags
C_FLAGS  = -mcpu=cortex-m0 -mthumb
C_FLAGS += -Wall -Wextra -Werror -pedantic
C_FLAGS += -std=c11 -O0 -ffreestanding -fno-tree-loop-distribute-patterns
C_FLAGS += -ffunction-sections -fdata-sections
C_FLAGS += $(if $(DEBUG), -g) -I$(LPC) -D BAUD_RATE=$(BAUD)

# Linker flags
LD_FLAGS  = -mcpu=cortex-m0 -mthumb -nostdlib
LD_FLAGS += -Wl,-gc-sections

all: $(HEX) $(BIN)
asm: $(ASM)
size: $(OBJ) $(ELF)
	@size $(OBJ) $(ELF)

$(HEX): $(ELF)
	@echo "Creating" $@
	@arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)

$(BIN): $(ELF)
	@echo "Creating" $@
	@arm-none-eabi-objcopy -O binary $(ELF) $(BIN)

$(ELF): $(LD) $(OBJ)
	@echo "Linking into" $@
	@arm-none-eabi-gcc $(LD_FLAGS) -T $(LD) -Wl,-Map,$(MAP) -o $@ $(OBJ) -lgcc


%.o: %.c
	@echo "Building" $@
	@arm-none-eabi-gcc $(C_FLAGS) -o $@ -c $<

%.o: %.S
	@echo "Building" $@
	@arm-none-eabi-gcc $(C_FLAGS) -o $@ -c $<

%.asm: %.c
	@echo "Building" $@
	@arm-none-eabi-gcc $(C_FLAGS) -fverbose-asm -o $@ -S $<


clean:
	@rm -rf $(OBJ) $(ASM)
	@rm -rf $(BIN) $(ELF) $(HEX) $(MAP)
	@echo "Cleaned project"


upload: $(BIN)
	lpc21isp -control -verify -term -bin $(BIN) $(TTY) $(BAUD) 12000
#	lpc21isp -termonly $(TTY) $(BAUD) 12000
