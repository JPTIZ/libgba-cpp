OUTPUT    := gba-engine

subdirs   := $(wildcard */)
sources   := $(wildcard *.cpp) $(wildcard $(addsuffix *.cpp,$(subdirs)))
objects   := $(patsubst %.cpp,%.o,$(sources))

OUTPUT    := $(BINDIR)/$(OUTPUT).a

all: $(OUTPUT)

$(objects) : %.o : %.cpp
	@echo Compiling $^
	$(CXX) -o $@ -c $^ $(ARCHFLAGS) $(CXXFLAGS)

$(OUTPUT): $(objects)
	@echo Generating $@
	$(AR) rvs $@ $^

clean:
	rm -f $(objects) $(OUTPUT)
