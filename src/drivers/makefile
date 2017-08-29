OUTPUT  := libgba
CPPSTD  := c++17
OPTLV   := 0
#SOURCES := $(wildcard *.cpp) $(wildcard display/&
#OBJS    := $(SOURCES:.cpp=.o)

subdirs := $(wildcard */)
sources := $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects := $(patsubst %.cpp,%.o,$(sources))

BIN     := $(DEVKITARM)/bin
ARCH    := -mthumb -mthumb-interwork -fomit-frame-pointer -ffast-math -fno-exceptions -fno-rtti

all: $(OUTPUT)


$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(BIN)/arm-none-eabi-g++ -o $@ -c $^ $(ARCH) -std=$(CPPSTD) -O$(OPTLV)
#%.o: %.cpp

$(OUTPUT): $(objects)
	@echo Generating $@
	$(BIN)/arm-none-eabi-ar rvs $@.a $^

clean:
	rm -f *.o **/*.o $(OUTPUT).a
