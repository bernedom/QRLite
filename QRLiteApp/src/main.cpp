#include "CollageImageProvider.h"
#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QRLite/project.h>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  app.setApplicationName("QRLite");
  QQmlApplicationEngine qmlEngine;

  QRLite::Project project;
  project.addImage(QFile(":/images/images/checkerboard_64x64.jpg"));
  project.addImage(QFile(":/images/images/checkerboard_64x64.jpg"));
  qmlEngine.rootContext()->setContextProperty("project", &project);
  CollageImageProvider imageProvider(project);
  qmlEngine.addImageProvider("collage", &imageProvider);

  qmlEngine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}