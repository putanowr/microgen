# - Try to find TochnogLib
# Once done this will define
#
#  TOCHNOGLIB_FOUND - system has TochnogLib
#  TOCHNOGLIB_INCLUDE_DIRS - the TochnogLib include directory
#  TOCHNOGLIB_LIBRARIES - Link these to use TochnogLib
#  TOCHNOGLIB_DEFINITIONS - Compiler switches required for using TochnogLib
#
#  Copyright (c) 2014 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

SET(BASE_DIR_LIB ${BASE_DIR}/lib)

if (TOCHNOGLIB_LIBRARIES AND TOCHNOGLIB_INCLUDE_DIRS)
  # in cache already
  set(TOCHNOGLIB_FOUND TRUE)
else (TOCHNOGLIB_LIBRARIES AND TOCHNOGLIB_INCLUDE_DIRS)
  find_path(TOCHNOGLIB_INCLUDE_DIR NAMES tochnog/TochnogManager.hxx
      PATHS "${BASE_DIR}/include" 
            "${BASE_DIR}/../install/include"
             NO_DEFAULT_PATH
  )
  find_path(TOCHNOGLIB_INCLUDE_DIR NAMES tochnog/TochnogManager.hxx
  )
  set(TOCHNOGLIB_INCLUDE_DIR ${TOCHNOGLIB_INCLUDE_DIR}/tochnog)

  find_library(TOCHNOGLIB_LIBRARY NAMES tochnoglib PATHS "${BASE_DIR_LIB}"
                                         "${BASE_DIR_LIB}/../../install/lib"
     NO_DEFAULT_PATH
  )
  find_library(TOCHNOGLIB_LIBRARY NAMES tochnoglib 
  )
  set(TOCHNOGLIB_INCLUDE_DIRS
    ${TOCHNOGLIB_INCLUDE_DIR} CACHE PATH "Path to TochnogLib headers"
  )

  set(TOCHNOGLIB_LIBRARIES
      ${TOCHNOGLIB_LIBRARY} CACHE STRING "Directories to be linked to use TochnogLib"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set TOCHNOGLIB_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(TochnogLib  DEFAULT_MSG
                                  TOCHNOGLIB_LIBRARY TOCHNOGLIB_INCLUDE_DIR)
  if (TOCHNOGLIB_FOUND)
    message(STATUS "TochnogLib header files: ${TOCHNOGLIB_INCLUDE_DIR}")
    message(STATUS "TochnogLib library: ${TOCHNOGLIB_LIBRARY}")
  endif (TOCHNOGLIB_FOUND)
  mark_as_advanced(TOCHNOGLIB_INCLUDE_DIRS TOCHNOGLIB_LIBRARIES)
endif (TOCHNOGLIB_LIBRARIES AND TOCHNOGLIB_INCLUDE_DIRS)

