cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(SimpleCollage)

target_sources(SimpleCollage PRIVATE src/main.cpp src/qml/qml.qrc)
target_link_libraries(SimpleCollage PRIVATE Qt6::Core Qt6::Gui Qt6::Quick SimpleCollageLib)
target_compile_features(SimpleCollage PRIVATE cxx_std_20)
