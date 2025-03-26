#include "CollageImageProvider.h"
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <SimpleCollage/project.h>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  app.setApplicationName("SimpleCollage");
  QQmlApplicationEngine qmlEngine;

  qmlEngine.load(QUrl("qrc:/main.qml"));

  SimpleCollage::Project project;
  qmlEngine.rootContext()->setContextProperty("project", &project);
  CollageImageProvider imageProvider(project);
  qmlEngine.addImageProvider("collage", &imageProvider);

  return app.exec();
}