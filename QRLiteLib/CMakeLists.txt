cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(QRLiteLib STATIC)
add_library(QRLite::QRLiteLib ALIAS QRLiteLib)
target_include_directories(QRLiteLib PUBLIC include)
target_sources(QRLiteLib PRIVATE src/Scanner.cpp include/QRLite/Scanner.h src/CodeReader.cpp include/QRLite/CodeReader.h)
target_link_libraries(QRLiteLib PUBLIC Qt6::Gui Qt6::Core Qt6::Multimedia ZXing::ZXing)

if(Catch2_FOUND AND BUILD_TESTING)
  add_subdirectory(test)
endif()
