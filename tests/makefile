SUBDIRS := $(wildcard */.)

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@echo
	@echo Compiling test: $@
	@echo
	$(MAKE) -C $@ -f ../test_makefile

clean:
	@$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) -f ../test_makefile clean;)
