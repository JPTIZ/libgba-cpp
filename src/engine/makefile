OUTPUT    := gba-engine
CPPSTD    := c++17
OPTLV     := 0

subdirs   := $(wildcard */)
sources   := $(wildcard *.cpp) $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects   := $(patsubst %.cpp,%.o,$(sources))

BIN       := $(DEVKITARM)/bin
CXX	  := $(BIN)/arm-none-eabi-g++

PROCFLAGS := -mthumb-interwork -fomit-frame-pointer -ffast-math -fno-exceptions -fno-rtti
	     #-mtune=arm7tdmi -march=armv4
THUMB     := -mthumb
ARM       := -marm #-mlong-calls
ARCH      := $(THUMB) $(PROCFLAG)

all: $(OUTPUT)

$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(CXX) -o $@ -c $^ $(ARCH) -std=$(CPPSTD) -O$(OPTLV)

$(OUTPUT): $(objects)
	@echo Generating $@
	$(BIN)/arm-none-eabi-ar rvs $@.a $^

clean:
	rm -f $(objects) $(OUTPUT).a
