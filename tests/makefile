SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)

$(SUBDIRS):
	@echo Compiling test: $@
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
