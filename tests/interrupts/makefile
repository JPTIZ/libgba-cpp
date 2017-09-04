# Config
OUTPUT  := $(shell basename $(CURDIR))

CPPSTD  := c++17
OPTIMLV := 2
INCLUDE :=

# Libraries
LIBGBA  := ../../src/drivers/

# Architecture
ARCH    := -mthumb -mthumb-interwork -fomit-frame-pointer -ffast-math -fno-exceptions -fno-rtti

# Toolchain
BIN     := $(DEVKITARM)/bin
SPECS   := $(DEVKITARM)/arm-none-eabi/lib/gba.specs

CC      := $(BIN)/arm-none-eabi-gcc
CXX     := $(BIN)/arm-none-eabi-g++
OBJCOPY := $(BIN)/arm-none-eabi-objcopy
GBAFIX  := $(BIN)/gbafix

subdirs := $(wildcard */)
sources := $(wildcard *.cpp) $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects := $(patsubst %.cpp,%.o,$(sources))

all: $(OUTPUT)


# Source Rules

$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(CXX) -o $@ -c $^ $(ARCH) -std=$(CPPSTD) -O$(OPTIMLV) -I$(LIBGBA) -specs=$(SPECS)

$(OUTPUT): $(objects) $(LIBGBA)/libgba.a
	@echo Generating $@.elf
	$(CXX) -o $@.elf $^ -I$(LIBGBA) -specs=$(SPECS)
	@echo Generating $@.gba
	$(OBJCOPY) -O binary $@.elf $@.gba
	@echo Fixing ROM
	$(GBAFIX) $@.gba

clean:
	rm -f $(objects) $(OUTPUT).a
