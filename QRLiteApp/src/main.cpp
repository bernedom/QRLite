
#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QtCore/QDirIterator>
#include <QtCore/QPermission>
#include <QtCore/QTimer>
#include <QtGui/QIcon>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QMediaDevices>

#include <QRLite/CodeReader.h>
#include <QRLite/Scanner.h>

#include "PermissionChecker.h"

int main(int argc, char **argv) {

  qRegisterMetaType<QRLite::CodeReader>("CodeReader");
  qRegisterMetaType<QRLite::PermissionChecker>("PermissionChecker");
  qmlRegisterType<QRLite::CodeReader>("QRLite", 1, 0, "CodeReader");
  qmlRegisterType<QRLite::PermissionChecker>("QRLite", 1, 0,
                                             "PermissionChecker");

  QGuiApplication app(argc, argv);
  app.setApplicationName("QRLite");
  app.setWindowIcon(QIcon(":/images/app_icon.png"));
  QQmlApplicationEngine qmlEngine;

  QRLite::PermissionChecker permissionChecker;
  qmlEngine.rootContext()->setContextProperty("permissionChecker",
                                              &permissionChecker);

  const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
  for (const QCameraDevice &cameraDevice : cameras) {
    qDebug() << "Camera found:" << cameraDevice.description();
  }

#ifdef __ANDROID__
  QCameraPermission cameraPermission;
  permissionChecker.setCameraCheckPending(true);
  app.requestPermission(
      cameraPermission, [&permissionChecker](const QPermission &permission) {
        if (permission.status() == Qt::PermissionStatus::Granted) {
          qDebug() << "Camera permission granted";
          permissionChecker.setCameraPermissionGranted(true);
        } else {
          qWarning() << "Camera permission denied";
          permissionChecker.setCameraPermissionGranted(false);
        }
      });
#else
  permissionChecker.setCameraPermissionGranted(true);
  permissionChecker.setCameraCheckPending(false);

#endif

  qmlEngine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}