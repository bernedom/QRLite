#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QRLite/scanner.h>
int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  app.setApplicationName("QRLite");
  QQmlApplicationEngine qmlEngine;
  QRLite::Scanner scanner;
  qmlEngine.rootContext()->setContextProperty("scanner", &scanner);

  qmlEngine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}