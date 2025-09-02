cmake_minimum_required(VERSION 3.21)

project(
  QRLite
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(
  Qt6
  COMPONENTS Core Gui Quick
  REQUIRED)

if(NOT ANDROID)
  find_package(Catch2)
endif()

include(CTest)

add_subdirectory(QRLiteLib)
add_subdirectory(QRLiteApp)
