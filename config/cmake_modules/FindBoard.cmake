# - Try to find Board
# Once done this will define
#
#  BOARD_FOUND - system has Board
#  BOARD_INCLUDE_DIRS - the Board include directory
#  BOARD_LIBRARIES - Link these to use Board
#  BOARD_DEFINITIONS - Compiler switches required for using Board
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if (BOARD_LIBRARIES AND BOARD_INCLUDE_DIRS)
  # in cache already
  set(BOARD_FOUND TRUE)
else (BOARD_LIBRARIES AND BOARD_INCLUDE_DIRS)
  find_path(BOARD_INCLUDE_DIR NAMES Board.h PATHS "${BASE_DIR}/include"
      NO_DEFAULT_PATH
  )
  find_path(BOARD_INCLUDE_DIR NAMES Board.h
  )

  find_library(BOARD_LIBRARY NAMES board PATHS "${BASE_DIR_LIB}"
  )
  find_library(BOARD_LIBRARY NAMES board
  )

  set(BOARD_INCLUDE_DIRS
    ${BOARD_INCLUDE_DIR} CACHE PATH "Path to Board headers"
  )

  set(BOARD_LIBRARIES
      ${BOARD_LIBRARY} CACHE STRING "Directories to be linked to use Board"
  )


  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set BOARD_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(Board  DEFAULT_MSG
                                  BOARD_LIBRARY BOARD_INCLUDE_DIR)
  if (BOARD_FOUND)
    message(STATUS "Board header files: ${BOARD_INCLUDE_DIR}")
    message(STATUS "Board library: ${BOARD_LIBRARY}")
  endif (BOARD_FOUND)
  mark_as_advanced(BOARD_INCLUDE_DIRS BOARD_LIBRARIES)
endif (BOARD_LIBRARIES AND BOARD_INCLUDE_DIRS)

