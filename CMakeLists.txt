cmake_minimum_required(VERSION 3.21)

project(
  QRLite
  VERSION 1.0.0
  LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

find_package(
  Qt6
  COMPONENTS Core Gui Multimedia Qml Quick              
  REQUIRED)

find_package(ZXing REQUIRED)

if(NOT ANDROID)
  find_package(Catch2)
endif()

include(CTest)

add_subdirectory(QRLiteLib)
add_subdirectory(QRLiteApp)
