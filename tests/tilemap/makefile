# Config
OUTPUT  := $(shell basename $(CURDIR))
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
