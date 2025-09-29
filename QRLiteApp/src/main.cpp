
#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QtCore/QDirIterator>
#include <QtCore/QPermission>
#include <QtGui/QIcon>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QMediaDevices>

#include <QRLite/CodeReader.h>
#include <QRLite/Scanner.h>

int main(int argc, char **argv) {

  qRegisterMetaType<QRLite::CodeReader>("CodeReader");
  qmlRegisterType<QRLite::CodeReader>("QRLite", 1, 0, "CodeReader");

  QGuiApplication app(argc, argv);
  app.setApplicationName("QRLite");
  app.setWindowIcon(QIcon(":/images/app_icon.png"));
  QQmlApplicationEngine qmlEngine;
  QRLite::Scanner scanner;
  qmlEngine.rootContext()->setContextProperty("scanner", &scanner);

  const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
  for (const QCameraDevice &cameraDevice : cameras) {
    qDebug() << "Camera found:" << cameraDevice.description();
  }

#ifdef __ANDROID__
  QCameraPermission cameraPermission;
  app.requestPermission(
      cameraPermission, [&qmlEngine](const QPermission &permission) {
        if (permission.status() == Qt::PermissionStatus::Granted) {
          qDebug() << "Camera permission granted";
          qmlEngine.rootContext()->setContextProperty("cameraPermissionGranted",
                                                      true);
        } else {
          qWarning() << "Camera permission denied";
          qmlEngine.rootContext()->setContextProperty("cameraPermissionGranted",
                                                      false);
        }
      });
#else
  qmlEngine.rootContext()->setContextProperty("cameraPermissionGranted", true);
#endif

  qmlEngine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}