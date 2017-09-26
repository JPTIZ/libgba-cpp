OUTPUT  := gba-engine
CPPSTD  := c++17
OPTLV   := 0
SOURCES := $(wildcard *.cpp)
OBJS    := $(notdir $(SOURCES:.cpp=.o))

BIN     := $(DEVKITARM)/bin
ARCH    := -mthumb -mthumb-interwork -fomit-frame-pointer -ffast-math -fno-exceptions -fno-rtti

%.o: %.cpp
	$(BIN)/arm-none-eabi-g++ -c $^ $(ARCH) -std=$(CPPSTD) -O$(OPTLV)

$(OUTPUT): $(OBJS)
	$(BIN)/arm-none-eabi-ar rvs $@.a $^

clean:
	rm -f *.o $(OUTPUT).a
