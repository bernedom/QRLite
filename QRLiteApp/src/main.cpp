#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QtCore/QPermission>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QMediaDevices>

#include <QRLite/Scanner.h>
int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  app.setApplicationName("QRLite");
  QQmlApplicationEngine qmlEngine;
  QRLite::Scanner scanner;
  qmlEngine.rootContext()->setContextProperty("scanner", &scanner);

  const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
  for (const QCameraDevice &cameraDevice : cameras) {
    qDebug() << "Camera found:" << cameraDevice.description();
  }

#ifdef __ANDROID__
  QCameraPermission cameraPermission;
  app.requestPermission(cameraPermission, [](const QPermission &permission) {
    if (permission.status() == Qt::PermissionStatus::Granted) {
      qDebug() << "Camera permission granted";
    } else {
      qWarning() << "Camera permission denied";
    }
  });
#endif

  qmlEngine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}