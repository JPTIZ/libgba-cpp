all:
	@echo ====================================================================
	@echo Compiling libgba...
	@echo ====================================================================
	@echo
	make -C src -f makefile
	@echo ====================================================================
	@echo Compiling tests...
	@echo ====================================================================
	@echo
	make -C tests -f makefile

docs:
	@echo Generating documentation...
	@echo
	@doxygen doc/doxy.conf
