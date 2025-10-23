#pragma once

#include <QtCore/QObject>
#include <QtGui/QImage>
namespace QRLite {

class CodeWriter : public QObject {
  Q_OBJECT
public:
  explicit CodeWriter(QObject *parent = nullptr) : QObject(parent) {}
  QImage writeCode(const QString &code);

  void saveCodeToFile(const QString &code, const QString &filePath);
};

} // namespace QRLite