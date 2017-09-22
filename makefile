all:
	@echo Compiling libgba...
	make -C src -f makefile
	@echo Compiling tests...
	make -C tests -f makefile

docs:
	@echo Generating documentation...
	@echo
	@doxygen doc/doxy.conf
