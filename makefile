# Directories
export TESTDIR
export BINDIR     = $(CURDIR)/bin
export INCLUDEDIR = $(CURDIR)/include
export DOCDIR     = $(CURDIR)/doc

# Compiler options
export OPTIMLEVEL = 2

# C++ configuration
export CXXSTD     = c++17

# Executables
export TOOLCHAIN  = $(DEVKITARM)/bin

export CC         = $(TOOLCHAIN)/arm-none-eabi-gcc
export CXX	      = $(TOOLCHAIN)/arm-none-eabi-g++
export LD         = $(TOOLCHAIN)/arm-none-eabi-ld
export AR         = $(TOOLCHAIN)/arm-none-eabi-ar

# Base compiler flags
export CFLAGS   = -I$(INCLUDEDIR)\
					-O$(OPTIMLEVEL)\
					-Wall\
					-Wextra\
					-Werror

export CXXFLAGS = $(CFLAGS)\
					-std=$(CXXSTD)\

ifeq ($(DEBUG), 1)
	export CXXFLAGS += -g
endif

# Build rules
all: libgba tests docs

libgba:
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mCompiling libgba...\e[0;32m"
	@echo -e "====================================================================\e[0m"
	@echo
	@mkdir -p $(BINDIR)
	@$(MAKE) -C src -f makefile
	@echo

tests:
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mCompiling tests...\e[0;32m"
	@echo -e "====================================================================\e[0m"
	@echo
	@$(MAKE) -C tests -f makefile
	@echo
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mDone\e[0;32m"
	@echo -e "====================================================================\e[0m"

docs:
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mGenerating documentation...\e[0;32m"
	@echo -e "====================================================================\e[0m"
	@echo
	@doxygen doc/doxy.conf
	@echo
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mDone\e[0;32m"
	@echo -e "====================================================================\e[0m"
