cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(QRLite)

target_link_libraries(QRLite PRIVATE Qt6::Core Qt6::Gui Qt6::Multimedia
                                     Qt6::Qml Qt6::Quick QRLiteLib)
target_sources(
  QRLite PRIVATE src/main.cpp src/PermissionChecker.h src/PermissionChecker.cpp
                 src/ClipboardBridge.h src/ClipboardBridge.cpp src/qml/qml.qrc)
target_compile_features(QRLite PRIVATE cxx_std_20)

# TODO: find a way to bump the version code automatically for releases, or at
# least make it a variable that can be set from the command line

set_target_properties(
  QRLite
  PROPERTIES QT_ANDROID_PACKAGE_NAME "ch.softwarecraft.qrlite"
             QT_ANDROID_APP_ICON "src/qml/images/icon.png"
             QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
             QT_ANDROID_TARGET_SDK_VERSION 36
             QT_ANDROID_VERSION_CODE 4)

# https://doc.qt.io/qt-6/cmake-property-reference.html see here for foll
# properties: https://doc.qt.io/qt-6/cmake-property-reference.html
