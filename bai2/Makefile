PROJECT = firmware
APP     ?= b2

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CPU = -mcpu=cortex-m3
MCU = $(CPU) -mthumb

BUILD_DIR  = Build
BIN_DIR    = Bin
LINKER_DIR = Linker

OBJECTS = \
	$(BUILD_DIR)/$(APP).o \
	$(BUILD_DIR)/startup.o

CFLAGS = \
	$(MCU) \
	-O0 \
	-g3 \
	-Wall \
	-Wextra \
	-ffreestanding \
	-ffunction-sections \
	-fdata-sections

LDFLAGS = \
	$(MCU) \
	-T$(LINKER_DIR)/STM32F103C8.ld \
	-nostdlib \
	-Wl,--gc-sections \
	-Wl,-Map=$(BUILD_DIR)/$(PROJECT).map

all: directories $(BIN_DIR)/$(PROJECT).bin

directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/$(APP).o: Src/$(APP).c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/startup.o: Src/startup.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/$(PROJECT).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BIN_DIR)/$(PROJECT).bin: $(BIN_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

flash: all
	st-flash write $(BIN_DIR)/$(PROJECT).bin 0x08000000
	st-flash reset

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BIN_DIR)/*

.PHONY: all clean flash directories
