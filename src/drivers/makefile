OUTPUT    := libgba
CPPSTD    := c++17
OPTLV     := 0

subdirs   := $(wildcard */)
sources   := $(wildcard *.cpp) $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects   := $(patsubst %.cpp,%.o,$(sources))

all: $(OUTPUT)

$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(CXX) -o $@ -c $^ $(ARCH) -std=$(CPPSTD) -O$(OPTLV) -I$(INCLUDEDIR)

cpu/interrupts.o : cpu/interrupts.cpp
	@echo Special compiling: $^
	$(CXX) -o $@ -c $^ $(ARM) $(PROCFLAGS) -std=$(CPPSTD) -O$(OPTLV) -I$(INCLUDEDIR)

$(OUTPUT): cpu/interrupts.o $(objects)
	@echo Generating $@
	$(AR) rvs $@.a $^

clean:
	rm -f $(objects) $(OUTPUT).a
