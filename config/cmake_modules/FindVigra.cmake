# - Try to find Vigra library (header files and library)
# Once done this will define
#
#  VIGRA_FOUND - system has Vigra
#  VIGRA_INCLUDE_DIRS - the Vigra include directory
#  VIGRA_LIBRARIES - Link these to use Vigra
#  VIGRA_DEFINITIONS - Compiler switches required for using Vigra
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (VIGRA_LIBRARIES AND VIGRA_INCLUDE_DIRS)
  # in cache already
  set(VIGRA_FOUND TRUE)
else (VIGRA_LIBRARIES AND VIGRA_INCLUDE_DIRS)

  find_path(VIGRA_INCLUDE_DIR NAMES vigra/impex.hxx 
    PATHS "${BASE_DIR}/include" NO_DEFAULT_PATH
  )
  find_path(VIGRA_INCLUDE_DIR NAMES vigra/impex.hxx 
  )

  find_library(VIGRA_LIBRARY NAMES vigraimpex PATHS "${BASE_DIR_LIB}"
    NO_DEFAULT_PATH
  )
  find_library(VIGRA_LIBRARY NAMES vigraimpex 
  )

  set(VIGRA_INCLUDE_DIRS
    ${VIGRA_INCLUDE_DIR} CACHE PATH "Path to Vigra headers"
  )

  set(VIGRA_LIBRARIES
      "${VIGRA_LIBRARY}" CACHE STRING "Directories to be linked to use Vigra"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set VIGRA_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(Vigra  DEFAULT_MSG
                                  VIGRA_LIBRARY VIGRA_INCLUDE_DIR)
  if (VIGRA_FOUND)
    message(STATUS "Vigra header files: ${VIGRA_INCLUDE_DIR}")
    message(STATUS "Vigra library: ${VIGRA_LIBRARY}")
  endif (VIGRA_FOUND)
  mark_as_advanced(VIGRA_INCLUDE_DIRS VIGRA_LIBRARIES)

endif (VIGRA_LIBRARIES AND VIGRA_INCLUDE_DIRS)
