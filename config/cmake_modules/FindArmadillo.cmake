# - Try to find Armadillo library (header files and library)
# Once done this will define
#
#  ARMADILLO_FOUND - system has Armadillo
#  ARMADILLO_INCLUDE_DIRS - the Armadillo include directory
#  ARMADILLO_LIBRARIES - Link these to use Armadillo
#  ARMADILLO_DEFINITIONS - Compiler switches required for using Armadillo
#
#  Copyright (c) 2012 Anna Perduta <aperduta@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (ARMADILLO_LIBRARIES AND ARMADILLO_INCLUDE_DIRS)
  # in cache already
  set(ARMADILLO_FOUND TRUE)
else (ARMADILLO_LIBRARIES AND ARMADILLO_INCLUDE_DIRS)
  find_path(ARMADILLO_INCLUDE_DIR NAMES armadillo
    PATHS "${BASE_DIR}/include" NO_DEFAULT_PATH
  )
  find_path(ARMADILLO_INCLUDE_DIR NAMES armadillo
  )

  find_library(ARMADILLO_LIBRARY NAMES armadillo PATHS "${BASE_DIR_LIB}"
    NO_DEFAULT_PATH
  )
  find_library(ARMADILLO_LIBRARY NAMES armadillo
  )

  set(ARMADILLO_INCLUDE_DIRS
    ${ARMADILLO_INCLUDE_DIR} CACHE PATH "Path to Armadillo headers"
  )

  set(ARMADILLO_LIBRARIES
      "${ARMADILLO_LIBRARY}" CACHE STRING "Directories to be linked to use Armadillo"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set ARMADILLO_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(Armadillo  DEFAULT_MSG
                                  ARMADILLO_LIBRARY ARMADILLO_INCLUDE_DIR)
  if (ARMADILLO_FOUND)
    message(STATUS "Armadillo header files: ${ARMADILLO_INCLUDE_DIR}")
    message(STATUS "Armadillo library: ${ARMADILLO_LIBRARY}")
  endif (ARMADILLO_FOUND)
  mark_as_advanced(ARMADILLO_INCLUDE_DIRS ARMADILLO_LIBRARIES)

endif (ARMADILLO_LIBRARIES AND ARMADILLO_INCLUDE_DIRS)
