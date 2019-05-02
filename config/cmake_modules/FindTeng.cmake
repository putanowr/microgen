# - Try to find Teng library (header files and library)
# Once done this will define
#
#  TENG_FOUND - system has Teng
#  TENG_INCLUDE_DIRS - the Teng include directory
#  TENG_LIBRARIES - Link these to use Teng
#  TENG_DEFINITIONS - Compiler switches required for using Teng
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (TENG_LIBRARIES AND TENG_INCLUDE_DIRS)
  # in cache already
  set(TENG_FOUND TRUE)
else (TENG_LIBRARIES AND TENG_INCLUDE_DIRS)

  find_path(TENG_INCLUDE_DIR NAMES teng.h
    PATHS "${BASE_DIR}/include" NO_DEFAULT_PATH
  )
  find_path(TENG_INCLUDE_DIR NAMES teng.h
  )

  find_library(TENG_LIBRARY NAMES teng PATHS "${BASE_DIR_LIB}"
    NO_DEFAULT_PATH
  )
  find_library(TENG_LIBRARY NAMES teng 
  )

  set(TENG_INCLUDE_DIRS
    ${TENG_INCLUDE_DIR} CACHE PATH "Path to Teng headers"
  )

  set(TENG_LIBRARIES
      "${TENG_LIBRARY}" CACHE STRING "Directories to be linked to use Teng"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set TENG_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(Teng  DEFAULT_MSG
                                  TENG_LIBRARY TENG_INCLUDE_DIR)
  if (TENG_FOUND)
    message(STATUS "Teng header files: ${TENG_INCLUDE_DIR}")
    message(STATUS "Teng library: ${TENG_LIBRARY}")
  endif (TENG_FOUND)
  mark_as_advanced(TENG_INCLUDE_DIRS TENG_LIBRARIES)

endif (TENG_LIBRARIES AND TENG_INCLUDE_DIRS)
