all:
	@echo -e "\e[32m--------------------------------------------------------------------"
	@echo Compiling Architecture Implementation...
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@make -C arch -f makefile
	@echo
	@echo -e "\e[32m--------------------------------------------------------------------"
	@echo Compiling Engine...
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@make -C engine -f makefile
	@echo

clean:
	@$(MAKE) -C arch -f makefile clean
	@$(MAKE) -C engine -f makefile clean
