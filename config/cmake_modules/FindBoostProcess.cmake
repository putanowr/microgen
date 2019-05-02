# - Try to find Boost.Process
# Once done this will define:
#
#  BOOSTPROCESS_FOUND        - system has Boost.Process
#  BOOSTPROCESS_INCLUDE_DIR  - the Boost.Process include directory
#  BOOSTPROCESS_INCLUDE_DIRS - the Boost.Process include directory
#  BOOSTPROCESS_DEFINITIONS  - Compiler switches required for 
#                              using Boost.Process
#
#  Copyright (c) 2010-2015 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (BOOSTPROCESS_INCLUDE_DIRS)
  # in cache already
  set(BOOSTPROCESS_FOUND TRUE)
else (BOOSTPROCESS_INCLUDE_DIRS)
  find_path(BOOSTPROCESS_INCLUDE_DIR NAMES boost/process.hpp
      PATHS ENV CPLUS_INCLUDE_PATH
            "${BASE_DIR}/include" 
            "${BASE_DIR}/../install/include" NO_DEFAULT_PATH
  )
  find_path(BOOSTPROCESS_INCLUDE_DIR NAMES boost/process.hpp
  )

  set(BOOSTPROCESS_INCLUDE_DIRS
    ${BOOSTPROCESS_INCLUDE_DIR} CACHE PATH "Path to Boost.Process++ headers"
  )
  set(BOOSTPROCESS_INCLUDE_DIR
    ${BOOSTPROCESS_INCLUDE_DIR} CACHE PATH "Path to Boost.Process++ headers"
  )
  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set BOOSTPROCESS_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(BOOSTPROCESS  DEFAULT_MSG
                                   BOOSTPROCESS_INCLUDE_DIR)
  if (BOOSTPROCESS_FOUND)
    message(STATUS "Boost.Process header files: ${BOOSTPROCESS_INCLUDE_DIR}")
  endif (BOOSTPROCESS_FOUND)
  mark_as_advanced(BOOSTPROCESS_INCLUDE_DIRS)
endif (BOOSTPROCESS_INCLUDE_DIRS)
