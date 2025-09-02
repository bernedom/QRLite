#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  app.setApplicationName("QRLite");
  QQmlApplicationEngine qmlEngine;

  qmlEngine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}