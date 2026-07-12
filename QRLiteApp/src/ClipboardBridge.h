#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

namespace QRLite {

class ClipboardBridge : public QObject {
  Q_OBJECT

public:
  explicit ClipboardBridge(QObject *parent = nullptr);

  Q_INVOKABLE void setText(const QString &text);
};

} // namespace QRLite
