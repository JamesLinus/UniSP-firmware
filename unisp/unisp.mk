#=============================================================================#
# project configuration
#=============================================================================#
PROJECT_DEFS +=

# include directories (absolute or relative paths to additional folders with
# headers, current folder is always included)
INC_DIRS += $(UNISP_DIR)/inc/cmsis

# library directories (absolute or relative paths to additional folders with
# libraries)
LIB_DIRS +=

# libraries (additional libraries for linking, e.g. "-lm -lsome_name" to link
# math library libm.a and libsome_name.a)
LIBS +=

# additional directories with source files (absolute or relative paths to
# folders with source files, current folder is always included)
SRCS_DIRS += $(UNISP_DIR) $(UNISP_DIR)/src $(UNISP_DIR)/src/hal $(UNISP_DIR)/src/ui_slave $(UNISP_DIR)/src/smps
