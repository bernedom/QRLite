#pragma once

#include <QImage>
#include <QObject>
#include <QString>

namespace QRLite {

class Scanner : public QObject {
  Q_OBJECT
public:
  explicit Scanner(QObject *parent = nullptr) : QObject(parent) {};
  ~Scanner() override {};
  Q_INVOKABLE QString scan(const QImage &image);
};
} // namespace QRLite