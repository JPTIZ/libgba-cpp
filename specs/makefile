all: gba.specs
	@echo "Specs generated."

gba.specs:
	sed 's#___SPECS_DIR___#${SPECSDIR}#' "${SPECSDIR}/$@.in" > "${SPECSDIR}/$@"
