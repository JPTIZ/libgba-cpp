all:
	@echo -e "\e[32m--------------------------------------------------------------------"
	@echo Compiling Drivers...
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@make -C drivers -f makefile
	@echo
	@echo -e "\e[32m--------------------------------------------------------------------"
	@echo Compiling engine...
	@echo -e "--------------------------------------------------------------------\e[0m"
	@echo
	@make -C engine -f makefile
	@echo

clean:
	@$(MAKE) -C drivers -f makefile clean
	@$(MAKE) -C engine -f makefile clean
