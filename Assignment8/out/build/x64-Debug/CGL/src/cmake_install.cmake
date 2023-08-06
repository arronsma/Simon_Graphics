# Install script for directory: F:/games101/games101homework/Assignment8/CGL/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "F:/games101/games101homework/Assignment8/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/games101/games101homework/Assignment8/out/build/x64-Debug/CGL/src/CGL.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CGL" TYPE FILE FILES
    "F:/games101/games101homework/Assignment8/CGL/src/CGL.h"
    "F:/games101/games101homework/Assignment8/CGL/src/vector2D.h"
    "F:/games101/games101homework/Assignment8/CGL/src/vector3D.h"
    "F:/games101/games101homework/Assignment8/CGL/src/vector4D.h"
    "F:/games101/games101homework/Assignment8/CGL/src/matrix3x3.h"
    "F:/games101/games101homework/Assignment8/CGL/src/matrix4x4.h"
    "F:/games101/games101homework/Assignment8/CGL/src/quaternion.h"
    "F:/games101/games101homework/Assignment8/CGL/src/complex.h"
    "F:/games101/games101homework/Assignment8/CGL/src/color.h"
    "F:/games101/games101homework/Assignment8/CGL/src/osdtext.h"
    "F:/games101/games101homework/Assignment8/CGL/src/viewer.h"
    "F:/games101/games101homework/Assignment8/CGL/src/base64.h"
    "F:/games101/games101homework/Assignment8/CGL/src/tinyxml2.h"
    "F:/games101/games101homework/Assignment8/CGL/src/renderer.h"
    )
endif()

