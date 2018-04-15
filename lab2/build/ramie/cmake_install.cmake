# Install script for directory: /media/pablo/linuks2/Ucze_sie/lab2/src/ramie

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/media/pablo/linuks2/Ucze_sie/lab2/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/media/pablo/linuks2/Ucze_sie/lab2/build/ramie/catkin_generated/installspace/ramie.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ramie/cmake" TYPE FILE FILES
    "/media/pablo/linuks2/Ucze_sie/lab2/build/ramie/catkin_generated/installspace/ramieConfig.cmake"
    "/media/pablo/linuks2/Ucze_sie/lab2/build/ramie/catkin_generated/installspace/ramieConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ramie" TYPE FILE FILES "/media/pablo/linuks2/Ucze_sie/lab2/src/ramie/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ramie" TYPE DIRECTORY FILES
    "/media/pablo/linuks2/Ucze_sie/lab2/src/ramie/images"
    "/media/pablo/linuks2/Ucze_sie/lab2/src/ramie/meshes"
    "/media/pablo/linuks2/Ucze_sie/lab2/src/ramie/launch"
    "/media/pablo/linuks2/Ucze_sie/lab2/src/ramie/rviz"
    "/media/pablo/linuks2/Ucze_sie/lab2/src/ramie/urdf"
    )
endif()

