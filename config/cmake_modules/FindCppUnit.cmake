# - Try to find CppUnit library (header files and library)
# Once done this will define
#
#  CPPUNIT_FOUND - system has CppUnit
#  CPPUNIT_INCLUDE_DIRS - the CppUnit include directory
#  CPPUNIT_LIBRARIES - Link these to use CppUnit
#  CPPUNIT_DEFINITIONS - Compiler switches required for using CppUnit
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (CPPUNIT_LIBRARIES AND CPPUNIT_INCLUDE_DIRS)
  # in cache already
  set(CPPUNIT_FOUND TRUE)
else (CPPUNIT_LIBRARIES AND CPPUNIT_INCLUDE_DIRS)

  FIND_PROGRAM(CPPUNIT_CONFIG NAMES cppunit-config)

  find_path(CPPUNIT_INCLUDE_DIR NAMES cppunit/TestCase.h
    PATHS "${BASE_DIR}/include" NO_DEFAULT_PATH
  )
  find_path(CPPUNIT_INCLUDE_DIR NAMES cppunit/TestCase.h
  )

  find_library(CPPUNIT_LIBRARY NAMES cppunit dl PATHS "${BASE_DIR_LIB}"
    NO_DEFAULT_PATH
  )
  find_library(CPPUNIT_LIBRARY NAMES cppunit dl
  )

  set(CPPUNIT_INCLUDE_DIRS
    ${CPPUNIT_INCLUDE_DIR} CACHE PATH "Path to CppUnit headers"
  )

  set(CPPUNIT_LIBRARIES
      "${CPPUNIT_LIBRARY}" CACHE STRING "Directories to be linked to use CppUnit"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set CPPUNIT_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(CppUnit  DEFAULT_MSG
                                  CPPUNIT_LIBRARY CPPUNIT_INCLUDE_DIR)
  if (CPPUNIT_FOUND)
    message(STATUS "CppUnit header files: ${CPPUNIT_INCLUDE_DIR}")
    message(STATUS "CppUnit library: ${CPPUNIT_LIBRARY}")
  endif (CPPUNIT_FOUND)
  mark_as_advanced(CPPUNIT_INCLUDE_DIRS CPPUNIT_LIBRARIES)

endif (CPPUNIT_LIBRARIES AND CPPUNIT_INCLUDE_DIRS)
