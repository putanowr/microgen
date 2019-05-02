# Various CMake utilities and shortcuts
MACRO(GENERATE_CONF_HEADER confname)  
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/${confname}_config.h.in"
  "${PROJECT_BINARY_DIR}/${confname}_config.h"
)
ENDMACRO(GENERATE_CONF_HEADER)
