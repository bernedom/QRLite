/*
 * SPDX-FileCopyrightText: 2026 Dominik Berner
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

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

  std::expected<QString, ScannerError> scan(const QString& path) const;
  std::expected<QString, ScannerError> scan(const QImage &image) const;
signals:
  void validCodeFound(const QString code);
};
} // namespace QRLite