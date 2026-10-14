PROJECT     ?= firmware
CC          = arm-none-eabi-gcc
OBJCOPY     = arm-none-eabi-objcopy
SIZE        = arm-none-eabi-size
FLASH_TOOL  = st-flash

CPU         ?= -mcpu=cortex-m3
MCU         ?= $(CPU) -mthumb
BUILD_DIR   ?= Build
BIN_DIR     ?= Bin
LINKER_SCRIPT ?= Linker/STM32F103C8.ld

# Set these to the locations of the FreeRTOS kernel and the MCU startup file.
FREERTOS_DIR    ?= Lib/FreeRTOS-Kernel
FREERTOS_PORT   ?= $(FREERTOS_DIR)/portable/GCC/ARM_CM3
FREERTOS_HEAP   ?= $(FREERTOS_DIR)/portable/MemMang/heap_4.c
FREERTOS_CONFIG ?= .
STARTUP_SRC     ?= startup.c

SOURCES = \
	main.c \
	$(STARTUP_SRC) \
	$(FREERTOS_DIR)/tasks.c \
	$(FREERTOS_DIR)/queue.c \
	$(FREERTOS_DIR)/list.c \
	$(FREERTOS_PORT)/port.c \
	$(FREERTOS_HEAP)

OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))
INCLUDES = \
	-I. \
	-I$(FREERTOS_CONFIG) \
	-I$(FREERTOS_DIR)/include \
	-I$(FREERTOS_PORT)

CFLAGS = \
	$(MCU) \
	-std=c11 \
	-O0 \
	-g3 \
	-Wall \
	-Wextra \
	-ffreestanding \
	-fno-builtin \
	-fno-unwind-tables \
	-fno-asynchronous-unwind-tables \
	-ffunction-sections \
	-fdata-sections \
	$(INCLUDES)

LDFLAGS = \
	$(MCU) \
	-T$(LINKER_SCRIPT) \
	-nostdlib \
	-Wl,--gc-sections \
	-Wl,-Map=$(BUILD_DIR)/$(PROJECT).map \
	-lc \
	-lgcc

all: $(BIN_DIR)/$(PROJECT).bin

$(BIN_DIR)/$(PROJECT).elf: $(OBJECTS) $(LINKER_SCRIPT)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BIN_DIR)/$(PROJECT).bin: $(BIN_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.o: %.c main.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(BIN_DIR)/$(PROJECT).bin
	$(FLASH_TOOL) write $< 0x08000000
	$(FLASH_TOOL) reset

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all flash clean
