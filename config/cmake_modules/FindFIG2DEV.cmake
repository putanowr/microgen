# - Find fig2dev 
# This module finds if fig2dev is installed and determines where the
# executables are. This code sets the following variables:
#  
#  FIG2DEV_CONVERTER:    path to the fig2dev converter

#=============================================================================
# Copyright 2011  Roman Putanowicz.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

IF (WIN32)
  MESSAGE(FATAL_ERROR "Do not know how to find fig2dev on Windows") 
ENDIF (WIN32)

FIND_PROGRAM(FIG2DEV_CONVERTER
  NAMES fig2dev
  PATHS  /usr/bin
         /usr/local/bin
)

MARK_AS_ADVANCED(
  FIG2DEV_CONVERTER
)
