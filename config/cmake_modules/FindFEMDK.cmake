# - Try to find FEMDK
# Once done this will define
#
#  FEMDK_FOUND - system has FEMDK
#  FEMDK_INCLUDE_DIRS - the FEMDK include directory
#  FEMDK_INCLUDE_DIR - the FEMDK include directory
#  FEMDK_LIBRARIES - Link these to use FEMDK
#  FEMDK_CORE_LIBRARY -- FEMDK core module library
#  FEMDK_GEOMETRY_LIBRARY -- FEMDK geometry module library
#  FEMDK_GETFEM_LIBRARY -- FEMDK GetFEM++ support module library
#  FEMDK_MESHES_LIBRARY -- FEMDK mesh module library
#  FEMDK_REPORTERS_LIBRARY -- FEMDK reportes module library
#  FEMDK_SOLVERS_LIBRARY -- FEMDK solvers module library
#  FEMDK_LIBRARY_DIR - path to FEMDK library directory
#  FEMDK_DEFINITIONS - Compiler switches required for using FEMDK
#  FEMDK_OPTS_DIR -- the FEMDK options definitions directory
#
#  Copyright (c) 2012 Roman Putanowicz <putanowr@l5.pk.edu.pl>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (FEMDK_LIBRARIES AND FEMDK_INCLUDE_DIRS)
  # in cache already
  set(FEMDK_FOUND TRUE)
else (FEMDK_LIBRARIES AND FEMDK_INCLUDE_DIRS)
  find_path(FEMDK_INCLUDE_DIR NAMES femdk/femdk_config.hxx
      PATHS ENV CPLUS_INCLUDE_PATH
            "${BASE_DIR}/include" 
             NO_DEFAULT_PATH
  )
  find_path(FEMDK_INCLUDE_DIR NAMES femdk/femdk_config.hxx
  )

  find_library(FEMDK_CORE_LIBRARY NAMES femdkCore PATHS ENV LD_LIBRARY_PATH
               "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_CORE_LIBRARY NAMES femdkCore
  )
  find_library(FEMDK_BGD_LIBRARY NAMES femdkBGD PATHS ENV LD_LIBRARY_PATH
               "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_BGD_LIBRARY NAMES femdkBGD 
  )
  find_library(FEMDK_BOARD_LIBRARY NAMES femdkBoard PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_BOARD_LIBRARY NAMES femdkBoard
  )
  find_library(FEMDK_FEBIO_LIBRARY NAMES femdkFEBio PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_FEBIO_LIBRARY NAMES femdkFEBio 
  )

  find_library(FEMDK_GEOMETRY_LIBRARY NAMES femdkGeometry PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_GEOMETRY_LIBRARY NAMES femdkGeometry)


  find_library(FEMDK_GETFEM_LIBRARY NAMES femdkGetFEM PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_GETFEM_LIBRARY NAMES femdkGetFEM)

  find_library(FEMDK_MESHES_LIBRARY NAMES femdkMeshes PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
find_library(FEMDK_MESHES_LIBRARY NAMES femdkMeshes)

  find_library(FEMDK_REPORTERS_LIBRARY NAMES femdkReporters PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_REPORTERS_LIBRARY NAMES femdkReporters)

  find_library(FEMDK_SOLVERS_LIBRARY NAMES femdkSolvers PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_SOLVERS_LIBRARY NAMES femdkSolvers)

  find_library(FEMDK_VIEWERS_LIBRARY NAMES femdkViewers PATHS ENV LD_LIBRARY_PATH
                "${BASE_DIR_LIB}"
     NO_DEFAULT_PATH
  )
  find_library(FEMDK_VIEWERS_LIBRARY NAMES femdkViewers 
  )

  set(FEMDK_INCLUDE_DIRS
    ${FEMDK_INCLUDE_DIR} CACHE PATH "Path to FEMDK headers"
  )
  set(FEMDK_INCLUDE_DIR
    ${FEMDK_INCLUDE_DIR} CACHE PATH "Path to FEMDK headers"
  )

  set(FEMDK_LIBRARIES
     ${FEMDK_CORE_LIBRARY} 
     ${FEMDK_BGD_LIBRARY}
     ${FEMDK_GEOMETRY_LIBRARY}
     ${FEMDK_FEBIO_LIBRARY}
     ${FEMDK_BOARD_LIBRARY}
     ${FEMDK_VIEWERS_LIBRARY}
     CACHE STRING "Directories to be linked to use FEMDK"
  )
  find_path(FEMDK_OPTS_DIR names logger_options.def
      PATHS ENV FEMDK_OPTIONS_DEF_DIR
            "${BASE_DIR}/share/femdk/options_def" 
  )
  set(FEMDK_OPTS_DIR
    ${FEMDK_OPTS_DIR} CACHE PATH "Path to FEMDK options"
  )

  get_filename_component(FEMDK_LIB_DIR ${FEMDK_CORE_LIBRARY} PATH CACHE)

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set FEMDK_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(FEMDK  DEFAULT_MSG
                                  FEMDK_CORE_LIBRARY FEMDK_INCLUDE_DIR)
  if (FEMDK_FOUND)
    message(STATUS "FEMDK header files: ${FEMDK_INCLUDE_DIR}")
    message(STATUS "FEMDK library: ${FEMDK_CORE_LIBRARY}")
    message(STATUS "FEMDK library path: ${FEMDK_LIB_DIR}")
  endif (FEMDK_FOUND)
  mark_as_advanced(FEMDK_INCLUDE_DIRS FEMDK_LIBRARIES)
endif (FEMDK_LIBRARIES AND FEMDK_INCLUDE_DIRS)

