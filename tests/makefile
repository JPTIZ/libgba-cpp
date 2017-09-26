SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)

$(SUBDIRS):
	@echo
	@echo Compiling test: $@
	@echo
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
