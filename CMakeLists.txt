CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

PROJECT( MICROGEN )

# Set path for CMake dependencies
IF(NOT DEFINED CMAKE_MODULE_PATH)
  # This block is executed only if this project is configuread as stand alone
  # that is not as a subproject of 'femdk' project
  SET(CMAKE_MODULE_PATH 
      "${CMAKE_SOURCE_DIR}/config/cmake_modules/" 
      ${BASE_DIR}/share/femdk/cmake_modules
      CACHE PATH "Path to FEMDK configuration directory")
ENDIF(NOT DEFINED CMAKE_MODULE_PATH)

# The version number.
set (FEMDK_VERSION_MAJOR      1)
set (FEMDK_VERSION_MINOR      5)
set (FEMDK_VERSION_REV        1)
set (FEMDK_VERSION  "${FEMDK_VERSION_MAJOR}.${FEMDK_VERSION_MINOR}.${FEMDK_VERSION_REV}")

INCLUDE(SetBaseDir)
INCLUDE(SetHostSpecific)
INCLUDE(UtilsFEMDK)

# Uncomment and specify package name used by program if any
FIND_PACKAGE(AutoOpts)
FIND_PACKAGE(CppUnit)
FIND_PACKAGE(Log4Cpp)
FIND_PACKAGE(Boost COMPONENTS system filesystem REQUIRED)
FIND_PACKAGE(BoostProcess REQUIRED)
FIND_PACKAGE(Vigra)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

if (LOG4CPP_FOUND)
  SET(FEMDK_HAVE_LOG4CPP TRUE CACHE BOOL "Compiled with support for Log4Cpp")
endif (LOG4CPP_FOUND)

if (BOOSTPROCESS_FOUND)
  SET(FEMDK_HAVE_BOOSTPROCESS TRUE CACHE BOOL "Compiled with support for
Boost.Process")
endif (BOOSTPROCESS_FOUND)

# Add any specific directores required by a program to compile
INCLUDE_DIRECTORIES( 
     ${CMAKE_SOURCE_DIR}
     ${PROJECT_SOURCE_DIR}
     ${PROJECT_BINARY_DIR}
     ${AUTOOPTS_INCLUDE_DIRS}
     ${LOG4CPP_INCLUDE_DIRS}
     ${CPPUNIT_INCLUDE_DIRS}
     ${BOOSTPROCESS_INCLUDE_DIRS}
     ${BOOST_INCLUDE_DIRS}
     ${VIGRA_INCLUDE_DIRS}
)

ADD_DEFINITIONS(${AUTOOPTS_CFLAGS}
                ${LOG4CPP_FLAGS}
               )

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}
                )

GENERATE_CONF_HEADER(microgen)
GENERATE_CONF_HEADER(femdk)
GENERATE_OPTSOURCE(microgen output micro logger misc)
ADD_EXECUTABLE(microgen microgen.cxx 
                        microgen_options.c 
                        microgen_options.h
                        microgen_algebra3.hxx 
                        microgen_algebra3.cxx
                        microgen_exceptions.cxx
                        microgen_exceptions.hxx
                        microgen_params.hxx
                        microgen_params.cxx
                        microgen_parsing.hxx
                        microgen_parsing.cxx
                        microgen_testing.cxx
                        microgen_testing.hxx
                        microgen_types.cxx
                        microgen_types.hxx
femdk_common.hxx
femdk_ConfigData.cxx
femdk_ConfigData.hxx
femdk_except.cxx
femdk_init.cxx
femdk_logger.cxx
femdk_logger.hxx
femdk_params.cxx
femdk_params.hxx
femdk_types.cxx
femdk_types.hxx
                        MicroGenerator.cxx
                        MicroGenerator.hxx
                        tests/dummy_test.cxx
                        tests/parsing_test.cxx
                        tests/algebra3_test.cxx
              )
TARGET_LINK_LIBRARIES(microgen ${AUTOOPTS_LIBRARIES}
                               ${LOG4CPP_LIBRARIES}
                               ${CPPUNIT_LIBRARIES}
                               ${Boost_LIBRARIES}
                               ${VIGRA_LIBRARIES}
                               ${VTK_LIBRARIES}
                               -lfftw3
                      )

SET_TARGET_PROPERTIES(microgen PROPERTIES COMPILE_FLAGS "-std=gnu++0x")


#SET_TARGET_PROPERTIES(microgen
#                      PROPERTIES EXCLUDE_FROM_ALL TRUE)

# INSTALL( PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/microgen DESTINATION bin )
# INSTALL( PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/(${EXEC_NAME} DESTINATION bin )
