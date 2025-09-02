cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(QRLite)

target_sources(QRLite PRIVATE src/main.cpp src/qml/qml.qrc)
target_link_libraries(QRLite PRIVATE Qt6::Core Qt6::Gui Qt6::Quick QRLiteLib)
target_compile_features(QRLite PRIVATE cxx_std_20)
