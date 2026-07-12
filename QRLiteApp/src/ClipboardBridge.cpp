#include "ClipboardBridge.h"

#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>

namespace QRLite {

ClipboardBridge::ClipboardBridge(QObject *parent) : QObject(parent) {}

void ClipboardBridge::setText(const QString &text) {
  if (QClipboard *clipboard = QGuiApplication::clipboard()) {
    clipboard->setText(text);
  }
}

} // namespace QRLite
