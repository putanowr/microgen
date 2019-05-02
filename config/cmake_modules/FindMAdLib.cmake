# - Try to find MAdLib library.
# Once done this will define
#
#  MADLIB_FOUND - system has MADLIB
#  MADLIB_INCLUDE_DIRS - the MADLIB include directory
#  MADLIB_LIBRARIES - Link these to use MADLIB
#  MADLIB_DEFINITIONS - Compiler switches required for using MADLIB
#
#  Copyright (c) 2012 Anna Perduta <aperduta@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

SET(BASE_DIR_LIB ${BASE_DIR}/lib)

if (MADLIB_LIBRARIES AND MADLIB_INCLUDE_DIRS)
  # in cache already
  set(MADLIB_FOUND TRUE)
else (MADLIB_LIBRARIES AND MADLIB_INCLUDE_DIRS)
  find_path(MADLIB_INCLUDE_DIR NAMES MAdLib/MAdLib.h
      PATHS "${BASE_DIR}/include" 
            "${BASE_DIR}/../install/include"
             NO_DEFAULT_PATH
  )

  find_library(MADLIB_LIBRARY NAMES MAdLib PATHS "${BASE_DIR_LIB}"
                                                 "${BASE_DIR_LIB}/../../install/lib"
     NO_DEFAULT_PATH
  )

  set(MADLIB_INCLUDE_DIRS
    ${MADLIB_INCLUDE_DIR} CACHE PATH "Path to MAdLib headers"
  )

  set(MADLIB_LIBRARIES
      ${MADLIB_LIBRARY} CACHE STRING "Directories to be linked to use MAdLib"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set MADLIB_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(MAdLib DEFAULT_MSG
                                  MADLIB_LIBRARY MADLIB_INCLUDE_DIR)
  if (MADLIB_FOUND)
    message(STATUS "MAdLib header files: ${MADLIB_INCLUDE_DIR}")
    message(STATUS "MAdLib library: ${MADLIB_LIBRARY}")
  endif (MADLIB_FOUND)
  mark_as_advanced(MADLIB_INCLUDE_DIRS MADLIB_LIBRARIES)
endif (MADLIB_LIBRARIES AND MADLIB_INCLUDE_DIRS)

