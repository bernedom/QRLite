#pragma once

#include <QtCore/QObject>
#include <QtGui/QImage>
#include <qtmetamacros.h>
namespace QRLite {

class CodeWriter : public QObject {
  Q_OBJECT
public:
  explicit CodeWriter(QObject *parent = nullptr) : QObject(parent) {}
  QImage writeCode(const QString &code);

  Q_INVOKABLE void saveCodeToFile(const QString &code, const QString &filePath);
};

} // namespace QRLite