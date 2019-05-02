# Directories where program dependencies are located
# The following variables are set
#
#  BASE_DIR -- top install directory
#  BASE_DIR_LIB -- directory for library files ( this depends on BASE_DIR
#                                                and FEMDK_BUILD_TYPE )
#
IF (NOT DEFINED BASE_DIR)
SET( BASE_DIR "/space/install" CACHE PATH 
                           "Top istall dir for program dependencies")
ENDIF(NOT DEFINED BASE_DIR)

IF (    "${FEMDK_BUILD_TYPE}" MATCHES "Debug"
     OR "${FEMDK_BUILD_TYPE}" MATCHES "Instrument"
     OR "${FEMDK_BUILD_TYPE}" MATCHES "RelWithDebInfo"
   )
  SET(BASE_DIR_LIB ${BASE_DIR}/lib)
ELSE ("${FEMDK_BUILD_TYPE}" MATCHES "Debug"
     OR "${FEMDK_BUILD_TYPE}" MATCHES "Instrument"
     OR "${FEMDK_BUILD_TYPE}" MATCHES "RelWithDebInfo"
   )
  SET(BASE_DIR_LIB ${BASE_DIR}/lib)
ENDIF ("${FEMDK_BUILD_TYPE}" MATCHES "Debug"
     OR "${FEMDK_BUILD_TYPE}" MATCHES "Instrument"
     OR "${FEMDK_BUILD_TYPE}" MATCHES "RelWithDebInfo"
   )
