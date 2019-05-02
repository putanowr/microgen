# - Try to find Arabica
# Once done this will define
#
#  ARABICA_FOUND - system has Arabica
#  ARABICA_INCLUDE_DIRS - the Arabica include directory
#  ARABICA_LIBRARIES - Link these to use Arabica
#  ARABICA_DEFINITIONS - Compiler switches required for using Arabica
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

SET(BASE_DIR_LIB ${BASE_DIR}/lib)

if (ARABICA_LIBRARIES AND ARABICA_INCLUDE_DIRS)
  # in cache already
  set(ARABICA_FOUND TRUE)
else (ARABICA_LIBRARIES AND ARABICA_INCLUDE_DIRS)
  find_path(ARABICA_INCLUDE_DIR NAMES arabica/SAX/ArabicaConfig.hpp
      PATHS "${BASE_DIR}/include" 
            "${BASE_DIR}/../../install/include"
             NO_DEFAULT_PATH
  )
  find_path(ARABICA_INCLUDE_DIR NAMES arabica/SAX/ArabicaCoinfig.hpp
  )
  set(ARABICA_INCLUDE_DIR ${ARABICA_INCLUDE_DIR}/arabica)

  find_library(ARABICA_LIBRARY NAMES arabica PATHS "${BASE_DIR_LIB}"
                                         "${BASE_DIR_LIB}/../../install/lib"
     NO_DEFAULT_PATH
  )
  find_library(ARABICA_LIBRARY NAMES arabica 
  )
  set(ARABICA_INCLUDE_DIRS
    ${ARABICA_INCLUDE_DIR} CACHE PATH "Path to Arabica headers"
  )

  set(ARABICA_LIBRARIES
      ${ARABICA_LIBRARY} CACHE STRING "Directories to be linked to use Arabica"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set ARABICA_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(Arabica  DEFAULT_MSG
                                  ARABICA_LIBRARY ARABICA_INCLUDE_DIR)
  if (ARABICA_FOUND)
    message(STATUS "Arabica header files: ${ARABICA_INCLUDE_DIR}")
    message(STATUS "Arabica library: ${ARABICA_LIBRARY}")
  endif (ARABICA_FOUND)
  mark_as_advanced(ARABICA_INCLUDE_DIRS ARABICA_LIBRARIES)
endif (ARABICA_LIBRARIES AND ARABICA_INCLUDE_DIRS)

