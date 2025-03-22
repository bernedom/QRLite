#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>


int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  app.setApplicationName("SimpleCollage");
  QQmlApplicationEngine qmlEngine;

  qmlEngine.load(QUrl("qrc:/main.qml"));

  // HardRock::Game game;

  // qmlEngine.rootObjects().first()->setProperty("game",
  //                                              QVariant::fromValue(&game));

  return app.exec();
}