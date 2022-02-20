
# wizardry makefile

.SUFFIXES:
.PHONY: all clean lyn


# Tools
TOOLS_DIR := c:/FE-Tools
include $(TOOLS_DIR)/tools.mk

# Including devkitARM tool definitions
include $(DEVKITARM)/base_tools

# C-Lib
LYNREF := $(CLIB_DIR)/reference/FE8U-decompatible.o
INC_DIRS := $(realpath include) $(CLIB_DIR)/include $(TOOLS_DIR)

CLEAN_FILES :=

# ==================
# = OBJECTS & DMPS =
# ==================

# OBJ to event
%.lyn.event: %.o $(LYNREF)
	$(NOTIFY_PROCESS)
	@$(LYN) $< $(LYNREF) > $@

# OBJ to DMP rule
%.dmp: %.o
	$(NOTIFY_PROCESS)
	@$(OBJCOPY) -S $< -O binary $@




# ========================
# = ASSEMBLY/COMPILATION =
# ========================

# Setting C/ASM include directories up
INCFLAGS     := $(foreach dir, $(INC_DIRS), -I "$(dir)")

# setting up compilation flags
ARCH    := -mcpu=arm7tdmi -mthumb -mthumb-interwork
CFLAGS  := $(ARCH) $(INCFLAGS) -Wall -Os -mtune=arm7tdmi -ffreestanding -mlong-calls
ASFLAGS := $(ARCH) $(INCFLAGS)

# defining dependency flags
CDEPFLAGS = -MMD -MT "$*.o" -MT "$*.asm" -MF "$(CACHE_DIR)/$(notdir $*).d" -MP
SDEPFLAGS = --MD "$(CACHE_DIR)/$(notdir $*).d"

# ASM to OBJ rule
%.o: %.s
	$(NOTIFY_PROCESS)
	@$(AS) $(ASFLAGS) $(SDEPFLAGS) -I $(dir $<) $< -o $@ $(ERROR_FILTER)

# C to ASM rule
# I would be fine with generating an intermediate .s file but this breaks dependencies
%.o: %.c
	@$(CC) $(CFLAGS) $(CDEPFLAGS) -g -c $< -o $@ $(ERROR_FILTER)

# C to ASM rule
%.asm: %.c
	$(NOTIFY_PROCESS)
	@$(CC) $(CFLAGS) $(CDEPFLAGS) -S $< -o $@ -fverbose-asm $(ERROR_FILTER)

# Avoid make deleting objects it thinks it doesn't need anymore
# Without this make may fail to detect some files as being up to date
.PRECIOUS: %.o;



# ==============
# = MAKE CLEAN =
# ==============
CFILES := $(shell find -type f -name '*.c')
ASM_TARGET := $(CFILES:.c=.asm)
OBJ_TARGET := $(CFILES:.c=.o)
LYN_TARGET := $(CFILES:.c=.lyn.event)

ASM_C_GENERATED := $(CFILES:.c=.o) $(SFILES:.s=.o) $(CFILES:.c=.asm)
ASM_C_GENERATED += $(ASM_C_GENERATED:.o=.dmp) $(ASM_C_GENERATED:.o=.lyn.event)

CLEAN_FILES += $(ASM_C_GENERATED)


clean:
	@rm -f $(CLEAN_FILES)
	@echo c-generated in Wizardry all clean!
	
	
all:
	@$(MAKE) $(ASM_TARGET)
	@$(MAKE) $(LYN_TARGET)
	@rm -f $(OBJ_TARGET)	
	
lyn:
	@$(MAKE) $(LYN_TARGET)
	@rm -f $(OBJ_TARGET)	
	
	