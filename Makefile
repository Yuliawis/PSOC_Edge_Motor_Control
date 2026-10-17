

################################################################################
# Basic Configuration
################################################################################

# Type of ModusToolbox Makefile Options include:
#
# COMBINED    -- Top Level Makefile usually for single standalone application
# APPLICATION -- Top Level Makefile usually for multi project application
# PROJECT     -- Project Makefile under Application
#
MTB_TYPE=APPLICATION

MTB_PROJECTS=proj_cm33_s proj_cm33_ns proj_cm55

################################################################################
# Paths
################################################################################

include common_app.mk

include $(CY_TOOLS_DIR)/make/application.mk
