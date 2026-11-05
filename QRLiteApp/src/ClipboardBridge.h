/*
 * SPDX-FileCopyrightText: 2026 Dominik Berner
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

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
