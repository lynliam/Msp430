###########################################################
# 说明
# 更改变量：
#	MSPGCC_ROOT_DIR    //MSP430 GCC根目录
#   FLASHER_BIN_DIR    //MSP430Flasher所在目录
#   DEVICE             //目标芯片型号
#
# 参考文件:
# 	MSP430 GCC Toolchain User's Guide.pdf  (https://www.ti.com.cn/cn/lit/pdf/SLAU646F)
#   MSP Flasher User's Guide.pdf (https://www.ti.com/lit/pdf/SLAU654)
#   将 MSP430 .out （elf） 文件转换为 TI-TXT 十六进制文件 
#		(https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/f/msp-low-power-microcontroller-forum/971809/msp430f2274-converting-an-msp430-out-elf-file-into-the-ti-txt-hex-file) 
#   	(https://www.embeddedrelated.com/showthread/msp430/22295-1.php)
#
# File Tree:
# .
# ├─.vscode
# ├─Build
# ├─Driver
# │  └─include         // ld文件 和 msp430f5529.h 在这里
# ├─Inc
# │  └─MSP430F5xx_6xx  // driverlib.h 在这里
# │      └─inc
# └─Src                // main.c 在这里
# 
# Author: Lyn Liam (quan.2003@outlook.com)
# For HITsz Course: 电子工艺实习
# version 1.0 (only support Windows temporarily.  Ubuntu Later...)
###########################################################

all: clean MKDIR-BUILD TO-OBJECTS TO-OUT TO-ELF TO-HEX

# Toolchain
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc
GDB = $(MSPGCC_BIN_DIR)/msp430-elf-gdb
SIZE = $(MSPGCC_BIN_DIR)/msp430-elf-size
COPY = $(MSPGCC_BIN_DIR)/msp430-elf-objcopy
FLASHER = MSP430Flasher.exe

# Directories
MSPGCC_ROOT_DIR = F:/bsp/msp430/tool/msp430-gcc-9.3.1.11_win64
FLASHER_BIN_DIR = C:/ti/MSPFlasher_1.3.20
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin

SUPPORT_FILE_DIRECTORY = Driver/include
BUILD_DIR = build

# Files
SOURCES = $(wildcard ./Src/*.c)
C_INCLUDES = -IInc\
-I$(SUPPORT_FILE_DIRECTORY)

# Flags
OBJECTS=$(BUILD_DIR)/$(DEVICE).o
CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -T $(DEVICE).ld


# DEVICE
DEVICE = msp430f5529


# Commands
TO-OBJECTS:
	@echo "compiling..."
	$(CC) -I $(SUPPORT_FILE_DIRECTORY) $(C_INCLUDES) -L $(SUPPORT_FILE_DIRECTORY)  -mmcu=$(DEVICE) -o2 -g $(SOURCES) -o $(BUILD_DIR)/$(DEVICE).o
	$(SIZE) -t $(OBJECTS)

TO-OUT: ${OBJECTS}
	@echo "To outFile..."
	$(CC) -nostartfiles $(CFLAGS) $(LFLAGS) $? -o $(BUILD_DIR)/$(DEVICE).out
	$(SIZE)	-t $(BUILD_DIR)/$(DEVICE).out
TO-ELF: $(OBJECTS)
	@echo "To elfFile..."
	$(CC) -nostartfiles $(CFLAGS) $(LFLAGS) $? -o $(BUILD_DIR)/$(DEVICE).elf
	$(SIZE) -t $(BUILD_DIR)/$(DEVICE).elf
TO-HEX: $(OBJECTS)
	@echo "To hexFile..."
	$(COPY) -O ihex $(BUILD_DIR)/$(DEVICE).elf $(BUILD_DIR)/$(DEVICE).hex
MKDIR-BUILD:
	mkdir Build
flash:
	$(FLASHER_BIN_DIR)/$(FLASHER) -w "$(BUILD_DIR)/$(DEVICE).hex" -v -g -z [VCC] -n "$(DEVICE)"
debug: 
	$(GDB) $(BUILD_DIR)/$(DEVICE).elf
clean:
	del /q $(BUILD_DIR)
	rd /s /q $(BUILD_DIR)
Test:
	$(CC) --version