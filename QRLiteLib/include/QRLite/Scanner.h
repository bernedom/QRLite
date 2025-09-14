#pragma once

#include <QImage>
#include <QObject>
#include <QString>

#include <expected>

namespace QRLite {

struct ScannerError {
  QString message;
  ScannerError(const QString &msg) : message(msg) {}
};

class Scanner : public QObject {
  Q_OBJECT
public:
  explicit Scanner(QObject *parent = nullptr) : QObject(parent) {};
  ~Scanner() override {};

  std::expected<QString, ScannerError> scan(const QImage &image) const;
signals:
  void validCodeFound(const QString code);
};
} // namespace QRLite