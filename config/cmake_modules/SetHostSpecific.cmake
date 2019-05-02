# Settings that are based on host name 
# The following variables are set
#  HOST_NAME -- name of the host computer. 
#
IF (NOT DEFINED HOST_NAME)
SITE_NAME(HOST_NAME)
ENDIF(NOT DEFINED HOST_NAME)

IF ("${HOST_NAME}" MATCHES "alex"
   )
  SET(SWIG_EXECUTABLE /home/femdk/install/bin/swig)
  SET(Boost_ADDITIONAL_VERSIONS  "1.46" "1.46.1")
  SET(BOOST_ROOT /home/femdk/install)
  SET(Boost_USE_MULTITHREADED OFF)
  SET(FEMDK_USE_HOOPS ON)
  SET(HOOPS_VERSION 18.16)
ELSEIF ("${HOST_NAME}" MATCHES "cae"
       )
  SET(FEMDK_USE_HOOPS ON)
  SET(Boost_ADDITIONAL_VERSIONS  "1.47" "1.47.0")
  SET(BOOST_ROOT /home/prac/putanowr/install)
  SET(Boost_USE_MULTITHREADED OFF)
  SET(SWIG_EXECUTABLE /home/prac/putanowr/install/bin/swig)
  SET(HOOPS_VERSION 19.10)
ELSEIF ("${HOST_NAME}" MATCHES "jinx"
       )
  SET(FEMDK_USE_HOOPS ON)
  SET(Boost_ADDITIONAL_VERSIONS  "1.47" "1.47.0")
  SET(BOOST_ROOT /home/femdk/install)
  SET(Boost_USE_MULTITHREADED OFF)
  SET(SWIG_EXECUTABLE /home/femdk/install/bin/swig)
  SET(HOOPS_VERSION 19.10)
ELSEIF ("${HOST_NAME}" MATCHES "tomi"
       )
  SET(SWIG_EXECUTABLE /space/install/bin/swig2)
  SET(Boost_ADDITIONAL_VERSIONS  "1.46" "1.46.1")
  SET(BOOST_ROOT /space/install)
  SET(Boost_USE_MULTITHREADED OFF)
  SET(FEMDK_USE_HOOPS ON)
  SET(HOOPS_VERSION 19.10)
  SET(GMSH_INSTALL_DIR /space/install/gmsh-2.5)
ELSEIF ("${HOST_NAME}" MATCHES "madrok"
       )
  SET(SWIG_EXECUTABLE /home/putanowr/install/femdk/bin/swig2)
  SET(Boost_ADDITIONAL_VERSIONS  "1.47" "1.47.0")
  SET(BOOST_ROOT /home/putanowr/install/femdk)
  SET(Boost_USE_MULTITHREADED OFF)
  SET(HOOPS_VERSION 18.10)

ELSEIF("${HOST_NAME}" MATCHES "foo"
      )
  SET(FEMDK_USE_HOOPS OFF)
  SET(Boost_ADDITIONAL_VERSIONS  "1.47" "1.47.0")
  SET(BOOST_ROOT /mnt/space/putanowr/install/femdk)
  SET(Boost_USE_MULTITHREADED OFF)
ENDIF ("${HOST_NAME}" MATCHES "alex"
   )
MESSAGE(STATUS ${SWIG_EXECUTABLE} )
