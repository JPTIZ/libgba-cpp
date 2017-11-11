OUTPUT    := libgba

subdirs   := $(wildcard */)
sources   := $(wildcard *.cpp) $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects   := $(patsubst %.cpp,%.o,$(sources))

OUTPUT    := $(BINDIR)/$(OUTPUT).a

all: $(OUTPUT)

$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(CXX) -o $@ -c $^ $(ARCH) -std=$(CXXSTD) -O$(OPTLV) -I$(INCLUDEDIR)

cpu/interrupts.o : cpu/interrupts.cpp
	@echo Special compiling: $^
	$(CXX) -o $@ -c $^ $(ARM) $(PROCFLAGS) -std=$(CXXSTD) -O$(OPTLV) -I$(INCLUDEDIR)

$(OUTPUT): cpu/interrupts.o $(objects)
	@echo Generating $@
	$(AR) rvs $@ $^

clean:
	rm -f $(objects) $(OUTPUT)
