TTY  ?= /dev/ttyUSB0
BAUD ?= 19200

FILE   = $(LPC)core_cm0 $(LPC)system_LPC11xx $(basename $(wildcard $(SRC)*.c))
#$(SRC)_start $(SRC)main $(SRC)uart
OBJECT = $(addsuffix .o,   $(FILE))
LST    = $(addsuffix .lst, $(FILE))

# Folders
SRC = src/
LPC = LPC11xx/

# File names
BIN = $(SRC)LPC1114FN28.bin
ELF = $(SRC)LPC1114FN28.elf
HEX = $(SRC)LPC1114FN28.hex
LD  = $(SRC)LPC1114FN28.ld
MAP = $(SRC)LPC1114FN28.map

# C compiler flags
C_FLAGS  = -mcpu=cortex-m0 -mthumb
C_FLAGS += -std=c11 -O0 -I$(LPC)
#C_FLAGS += -ffunction-sections -fdata-sections
C_FLAGS += $(if $(DEBUG), -g)
#-Wall -Wextra -Werror -pedantic


all: clean $(HEX) $(BIN)
lst: $(LST)
size: $(OBJECT) $(ELF)
	@size $(OBJECT) $(ELF)

$(HEX): $(ELF)
	@arm-none-eabi-objcopy -O ihex $(ELF) $(HEX)
	@echo "Build" $@

$(BIN): $(ELF)
	@arm-none-eabi-objcopy -O binary $(ELF) $(BIN)
	@echo "Build" $@

$(ELF): $(LD) $(OBJECT)
	@arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -nostartfiles -nostdlib -nodefaultlibs -T $(LD) -Wl,-gc-sections -Wl,-Map,$(MAP) -o $@ $(OBJECT) -lgcc
	@echo "Build" $@


%.o: %.c
	@arm-none-eabi-gcc $(C_FLAGS) -o $@ -c $<
	@echo "Build" $@

%.lst: %.c
	@arm-none-eabi-gcc $(C_FLAGS) -fverbose-asm -o $@ -S $<
	@echo "Build" $@
#	arm-none-eabi-objdump -S -d $< > $@


clean:
	@rm -rf $(OBJECT) $(LST)
	@rm -rf $(BIN) $(ELF) $(HEX) $(MAP)
	@echo "Cleaned project"


upload: $(BIN)
	lpc21isp -control -verify -term -bin $(BIN) $(TTY) $(BAUD) 12000
#	lpc21isp -termonly $(TTY) $(BAUD) 12000
