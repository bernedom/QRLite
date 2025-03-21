cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(HardRock)

target_sources(HardRock PRIVATE src/main.cpp src/qml/qml.qrc src/game.cpp src/mountainSliceView.h)
target_link_libraries(HardRock PRIVATE Qt6::Core Qt6::Gui Qt6::Quick HardRockLib)
target_compile_features(HardRock PRIVATE cxx_std_20)
