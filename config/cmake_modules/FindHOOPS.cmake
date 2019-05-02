# - Try to find HOOPS
# Once done this will define
#
#  HOOPS_FOUND - system has HOOPS
#  HOOPS_INCLUDE_DIRS - the HOOPS include directory
#  HOOPS_LIBRARIES - Link these to use HOOPS
#  HOOPS_DEFINITIONS - Compiler switches required for using HOOPS
#  HOOPS_MAJOR_VERSION
#  HOOPS_MINOR_VERSION
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if (HOOPS_LIBRARIES AND HOOPS_INCLUDE_DIRS)
  # in cache already
  set(HOOPS_FOUND TRUE)
else (HOOPS_LIBRARIES AND HOOPS_INCLUDE_DIRS)
 IF(HOOPS_FIND_VERSION AND NOT "${HOOPS_FIND_VERSION}" STREQUAL "0")
    SET(HOOPS_MAJOR_VERSION "${HOOPS_FIND_VERSION_MAJOR}")
    SET(HOOPS_MINOR_VERSION "${HOOPS_FIND_VERSION_MINOR}")
 ELSE(HOOPS_FIND_VERSION AND NOT "${HOOPS_FIND_VERSION}" STREQUAL "0")
    SET(HOOPS_MAJOR_VERSION 18)
    SET(HOOPS_MINOR_VERSION 10)
 ENDIF(HOOPS_FIND_VERSION AND NOT "${HOOPS_FIND_VERSION}" STREQUAL "0")
 MATH(EXPR _HOOPS_VNUM "${HOOPS_MAJOR_VERSION}*100 + ${HOOPS_MINOR_VERSION}")

 MESSAGE( STATUS "${_HOOPS_VNUM}")
  find_path(HOOPS_INCLUDE_DIR NAMES hoops.h
      PATHS "${BASE_DIR}/include/HOOPS-${_HOOPS_VNUM}" 
            "${BASE_DIR}/../install/include/HOOPS-${_HOOPS_VNUM}"
             NO_DEFAULT_PATH
  )
  find_path(HOOPS_INCLUDE_DIR NAMES hoops.h
  )

  find_library(HOOPS_LIBRARY NAMES hoops${_HOOPS_VNUM}  
                      lhoops_utils
                      base_stream
              PATHS "${BASE_DIR_LIB}/HOOPS-${_HOOPS_VNUM}"
                    "${BASE_DIR_LIB}/../../install/lib/HOOPS-${_HOOPS_VNUM}"
     NO_DEFAULT_PATH
  )
  find_library(HOOPS_MVO_LIBRARY NAMES hoops_mvo
              PATHS "${BASE_DIR_LIB}/HOOPS-${_HOOPS_VNUM}"
                    "${BASE_DIR_LIB}/../../install/lib/HOOPS-${_HOOPS_VNUM}"
     NO_DEFAULT_PATH
  )
  find_library(HOOPS_MVO_MGK_LIBRARY NAMES hoops_mvo_mgk
              PATHS "${BASE_DIR_LIB}/HOOPS-${_HOOPS_VNUM}"
                    "${BASE_DIR_LIB}/../../install/lib/HOOPS-${_HOOPS_VNUM}"
     NO_DEFAULT_PATH
  )
  find_library(HOOPS_STREAM_LIBRARY NAMES hoops_stream
              PATHS "${BASE_DIR_LIB}/HOOPS-${_HOOPS_VNUM}"
                    "${BASE_DIR_LIB}/../../install/lib/HOOPS-${_HOOPS_VNUM}"
     NO_DEFAULT_PATH
  )
  find_library(HOOPS_UTILS_LIBRARY NAMES hoops_utils
              PATHS "${BASE_DIR_LIB}/HOOPS-${_HOOPS_VNUM}"
                    "${BASE_DIR_LIB}/../../install/lib/HOOPS-${_HOOPS_VNUM}"
     NO_DEFAULT_PATH
  )
  find_library(HOOPS_LIBRARY NAMES hoops${_HOOPS_VNUM} 
                      hoops_mvo
                      lhoops_utils
                      base_stream
  )

  set(HOOPS_INCLUDE_DIRS
    ${HOOPS_INCLUDE_DIR} CACHE PATH "Path to HOOPS headers"
  )

  set(HOOPS_LIBRARIES
      ${HOOPS_MVO_LIBRARY} 
      ${HOOPS_MVO_MGK_LIBRARY}
      ${HOOPS_STREAM_LIBRARY} 
      ${HOOPS_UTILS_LIBRARY}
      ${HOOPS_LIBRARY} CACHE STRING "Directories to be linked to use HOOPS"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set HOOPS_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(HOOPS  DEFAULT_MSG
                                  HOOPS_LIBRARY HOOPS_INCLUDE_DIR)
  if (HOOPS_FOUND)
    message(STATUS "HOOPS header files: ${HOOPS_INCLUDE_DIR}")
    message(STATUS "HOOPS library: ${HOOPS_LIBRARIES}")
    message(STATUS "HOOPS MVO library: ${HOOPS_MVO_LIBRARY}")
    message(STATUS "HOOPS MVO_MGK library: ${HOOPS_MVO_MGK_LIBRARY}")
    message(STATUS "HOOPS STREAM library: ${HOOPS_STREAM_LIBRARY}")
  endif (HOOPS_FOUND)
  mark_as_advanced(HOOPS_INCLUDE_DIRS HOOPS_LIBRARIES)
endif (HOOPS_LIBRARIES AND HOOPS_INCLUDE_DIRS)

