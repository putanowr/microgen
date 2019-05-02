# - Try to find GetFEM
# Once done this will define
#
#  GETFEM_FOUND - system has GetFEM
#  GETFEM_INCLUDE_DIRS - the GetFEM include directory
#  GETFEM_LIBRARIES - Link these to use GetFEM
#  GETFEM_DEFINITIONS - Compiler switches required for using GetFEM
#
#  Copyright (c) 2010 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if (GETFEM_LIBRARIES AND GETFEM_INCLUDE_DIRS)
  # in cache already
  set(GETFEM_FOUND TRUE)
else (GETFEM_LIBRARIES AND GETFEM_INCLUDE_DIRS)
  find_path(GETFEM_INCLUDE_DIR NAMES getfem/getfem_mesh.h
      PATHS "${BASE_DIR}/include" 
            "${BASE_DIR}/../install/include"
             NO_DEFAULT_PATH
  )
  find_path(GETFEM_INCLUDE_DIR NAMES getfem/getfem_mesh.h
  )

  find_library(GETFEM_LIBRARY NAMES getfem PATHS "${BASE_DIR_LIB}"
                                                 "${BASE_DIR_LIB}/../../install/lib"
     NO_DEFAULT_PATH
  )
  find_library(GETFEM_LIBRARY NAMES getfem 
  )
  set(GETFEM_INCLUDE_DIRS
    ${GETFEM_INCLUDE_DIR} CACHE PATH "Path to GetFEM++ headers"
  )

  set(GETFEM_LIBRARIES
      ${GETFEM_LIBRARY} CACHE STRING "Directories to be linked to use GetFEM++"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set GETFEM_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(GetFEM  DEFAULT_MSG
                                  GETFEM_LIBRARY GETFEM_INCLUDE_DIR)
  if (GETFEM_FOUND)
    message(STATUS "GetFEM header files: ${GETFEM_INCLUDE_DIR}")
    message(STATUS "GetFEM library: ${GETFEM_LIBRARY}")
  endif (GETFEM_FOUND)
  mark_as_advanced(GETFEM_INCLUDE_DIRS GETFEM_LIBRARIES)
endif (GETFEM_LIBRARIES AND GETFEM_INCLUDE_DIRS)

