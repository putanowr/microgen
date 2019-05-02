# - Try to find Gmsh library
# Once done this will define
#
#  GMSH_FOUND - system has GMSH
#  GMSH_INCLUDE_DIRS - the GMSH include directory
#  GMSH_LIBRARIES - Link these to use GMSH
#  GMSH_DEFINITIONS - Compiler switches required for using GMSH
#
#  Copyright (c) 2012 Anna Perduta <aperduta@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if (GMSH_LIBRARIES AND GMSH_INCLUDE_DIRS)
  # in cache already
  set(GMSH_FOUND TRUE)
else (GMSH_LIBRARIES AND GMSH_INCLUDE_DIRS)
  find_path(GMSH_INCLUDE_DIR NAMES gmsh/Gmsh.h
      PATHS "${BASE_DIR}/include" 
            "${BASE_DIR}/../install/include"
            "${GMSH_INSTALL_DIR}/include"
             NO_DEFAULT_PATH
  )
  find_path(GMSH_INCLUDE_DIR NAMES gmsh/Gmsh.h
  )

  find_library(GMSH_LIBRARY NAMES Gmsh PATHS "${BASE_DIR_LIB}"
                                             "${BASE_DIR_LIB}/../../install/lib"
                                             "${GMSH_INSTALL_DIR}/lib"
     NO_DEFAULT_PATH
  )
  find_library(GMSH_LIBRARY NAMES Gmsh 
  )
  set(GMSH_INCLUDE_DIRS
    ${GMSH_INCLUDE_DIR} CACHE PATH "Path to GMSH headers"
  )

  set(GMSH_LIBRARIES
      ${GMSH_LIBRARY} CACHE STRING "Directories to be linked to use GMSH"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set GMSH_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(GMSH DEFAULT_MSG
                                  GMSH_LIBRARIES GMSH_INCLUDE_DIRS)
  if (GMSH_FOUND)
    message(STATUS "GMSH header files: ${GMSH_INCLUDE_DIRS}")
    message(STATUS "GMSH library: ${GMSH_LIBRARIES}")
  endif (GMSH_FOUND)
  mark_as_advanced(GMSH_INCLUDE_DIRS GMSH_LIBRARIES)
endif (GMSH_LIBRARIES AND GMSH_INCLUDE_DIRS)

