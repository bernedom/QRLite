cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(QRLite)

target_link_libraries(QRLite PRIVATE Qt6::Core Qt6::Gui Qt6::Multimedia Qt6::Qml Qt6::Quick QRLiteLib)
target_sources(QRLite PRIVATE src/main.cpp src/qml/qml.qrc)
target_compile_features(QRLite PRIVATE cxx_std_20)

set_target_properties(QRLite PROPERTIES
  QT_ANDROID_PACKAGE_NAME "ch.softwarecraft.qrlite"
  QT_ANDROID_APP_ICON "src/qml/images/icon.png"
  QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
)

#todo set QT_ANDROID_APP_ICON "path to icon"
# see here for foll properties: https://doc.qt.io/qt-6/cmake-property-reference.html