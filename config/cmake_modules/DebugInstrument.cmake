# This module adds Instrument build type.
SET( CMAKE_CXX_FLAGS_INSTRUMENT "-Wall -Wabi -g -O0 -finstrument-functions" CACHE STRING
    "Flags used by the C++ compiler during maintainer builds."
    FORCE )
SET( CMAKE_C_FLAGS_INSTRUMENT "-Wall -pedantic -g -O0 -finstrument-functions" CACHE STRING
    "Flags used by the C compiler during maintainer builds."
    FORCE )
SET( CMAKE_EXE_LINKER_FLAGS_INSTRUMENT
    "-Wl,--warn-unresolved-symbols,--warn-once" CACHE STRING
    "Flags used for linking binaries during maintainer builds."
    FORCE )
SET( CMAKE_SHARED_LINKER_FLAGS_INSTRUMENT
    "-Wl,--warn-unresolved-symbols,--warn-once" CACHE STRING
    "Flags used by the shared libraries linker during maintainer builds."
    FORCE )
MARK_AS_ADVANCED(
    CMAKE_CXX_FLAGS_INSTRUMENT
    CMAKE_C_FLAGS_INSTRUMENT
    CMAKE_EXE_LINKER_FLAGS_INSTRUMENT
    CMAKE_SHARED_LINKER_FLAGS_INSTRUMENT )

