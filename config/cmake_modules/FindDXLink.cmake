# - Try to find DXLink library -- OpenDX connection library
# Once done this will define
#
#  DXLINK_FOUND - system has DXLink
#  DXLINK_INCLUDE_DIRS - the DXLink include directory
#  DXLINK_LIBRARIES - Link these to use DXLink
#  DXLINK_DEFINITIONS - Compiler switches required for using DXLink
#
#  Copyright (c) 2011 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

SET(BASE_DIR_LIB ${BASE_DIR}/lib)

if (DXLINK_LIBRARIES AND DXLINK_INCLUDE_DIRS)
  # in cache already
  set(DXLINK_FOUND TRUE)
else (DXLINK_LIBRARIES AND DXLINK_INCLUDE_DIRS)
  find_path(DXLINK_INCLUDE_DIR NAMES dxl.h
      PATHS "${BASE_DIR}/include" 
            "${BASE_DIR}/../install/include"
             NO_DEFAULT_PATH
  )
  find_path(DXLINK_INCLUDE_DIR NAMES dxl.h
  )

  find_library(DXLINK_LIBRARY NAMES DXL PATHS "${BASE_DIR_LIB}"
                                         "${BASE_DIR_LIB}/../../install/lib"
     NO_DEFAULT_PATH
  )
  find_library(DXLINK_LIBRARY NAMES DXL 
  )
  set(DXLINK_INCLUDE_DIRS
    ${DXLINK_INCLUDE_DIR} CACHE PATH "Path to DXLink headers"
  )

  set(DXLINK_LIBRARIES
      ${DXLINK_LIBRARY} CACHE STRING "Directories to be linked to use DXLink"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set DXLINK_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(DXLink  DEFAULT_MSG
                                  DXLINK_LIBRARY DXLINK_INCLUDE_DIR)
  if (DXLINK_FOUND)
    message(STATUS "DXLink header files: ${DXLINK_INCLUDE_DIR}")
    message(STATUS "DXLink library: ${DXLINK_LIBRARY}")
  endif (DXLINK_FOUND)
  mark_as_advanced(DXLINK_INCLUDE_DIRS DXLINK_LIBRARIES)
endif (DXLINK_LIBRARIES AND DXLINK_INCLUDE_DIRS)

