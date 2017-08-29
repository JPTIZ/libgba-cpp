OUTPUT  := $(shell basename $(CURDIR))
LIBGBA  := ../../src/drivers/
CPPSTD  := c++17
OPTLV   := 0

subdirs := $(wildcard */)
sources := $(wildcard *.cpp) $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects := $(patsubst %.cpp,%.o,$(sources))

BIN     := $(DEVKITARM)/bin
ARCH    := -mthumb -mthumb-interwork -fomit-frame-pointer -ffast-math -fno-exceptions -fno-rtti

all: $(OUTPUT)


$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(BIN)/arm-none-eabi-g++ -o $@ -c $^ $(ARCH) -std=$(CPPSTD) -O$(OPTLV) -I$(LIBGBA)

$(OUTPUT): $(objects)
	@echo Generating $@
	$(BIN)/arm-none-eabi-ar rvs $@.a $^ -lgba -L $(LIBGBA)/libgba.a

clean:
	rm -f *.o **/*.o $(OUTPUT).a
