#==============================================================================
# Directories
#------------------------------------------------------------------------------
export BINDIR     = $(CURDIR)/bin
export DOCDIR     = $(CURDIR)/docs
export SRCDIR     = $(CURDIR)/src
export INCLUDEDIR = $(SRCDIR)
export TESTDIR    = $(CURDIR)/tests

#------------------------------------------------------------------------------
# Compiler options
#------------------------------------------------------------------------------
export OPTIMLEVEL = 2
ifeq ($(DEBUG), 1)
	export OPTIMLEVEL = 0
endif

#------------------------------------------------------------------------------
# C++ configuration
#------------------------------------------------------------------------------
export CXXSTD     = c++17

#------------------------------------------------------------------------------
# Executables
#------------------------------------------------------------------------------
export TOOLCHAIN  = $(DEVKITARM)/bin

export CC         = $(TOOLCHAIN)/arm-none-eabi-gcc
export CXX	      = $(TOOLCHAIN)/arm-none-eabi-g++
export LD         = $(TOOLCHAIN)/arm-none-eabi-g++
export AR         = $(TOOLCHAIN)/arm-none-eabi-ar
export OBJCOPY	  = $(TOOLCHAIN)/arm-none-eabi-objcopy
export GBAFIX	  = $(TOOLCHAIN)/gbafix

#------------------------------------------------------------------------------
# Base compiler flags
#------------------------------------------------------------------------------
export THUMB	  = -mthumb

export ARM  	  = -marm

export ARCHFLAGS  = \
	                -mthumb-interwork\
	                -fomit-frame-pointer\
					-ffast-math\
					-fno-exceptions\
					-fno-rtti

export CFLAGS     = \
	                -I$(INCLUDEDIR)\
					-O$(OPTIMLEVEL)\
					-Wall\
					-Wextra\
					-Werror

export CXXFLAGS   = $(CFLAGS)\
					-std=$(CXXSTD)

export LDFLAGS    = $(CXXFLAGS)\
	                -specs=gba.specs

ifeq ($(DEBUG), 1)
	export CXXFLAGS += -g
endif

export MAKE       := $(MAKE) --no-print-directory

#==============================================================================
# Build rules
#------------------------------------------------------------------------------
.PHONY: libgba tests docs

all: libgba tests docs

libgba:
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mCompiling libgba...\e[0;32m"
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@mkdir -p $(BINDIR)
	@$(MAKE) -C $(SRCDIR) -f makefile
	@echo

tests:
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mCompiling tests...\e[0;32m"
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@$(MAKE) -C $(TESTDIR) -f makefile
	@echo
	@echo -e "\e[32m--------------------------------------------------------------------"
	@echo -e "\e[1mDone\e[0;32m"
	@echo -e "====================================================================\e[0m"

docs:
	@echo -e "\e[32m===================================================================="
	@echo -e "\e[1mGenerating documentation...\e[0;32m"
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@doxygen $(DOCDIR)/doxy.conf
	@echo
	@echo -e "\e[32m--------------------------------------------------------------------"
	@echo -e "\e[1mDone\e[0;32m"
	@echo -e "====================================================================\e[0m"

clean:
	rm -rf $(BINDIR)
	@$(MAKE) -C $(SRCDIR) -f makefile clean
	@$(MAKE) -C $(TESTDIR) -f makefile clean
