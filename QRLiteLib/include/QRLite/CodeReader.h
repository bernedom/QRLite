/*
 * SPDX-FileCopyrightText: 2026 Dominik Berner
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QThreadPool>
#include <QtCore/QUrl>
#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QVideoSink>
namespace QRLite {
class CodeReader : public QObject {
  Q_OBJECT

public:
  explicit CodeReader(QObject *parent = nullptr) : QObject(parent) {};
  ~CodeReader() override {};

  void onVideoFrameChanged(const QVideoFrame &frame);

  void setVideoSink(QVideoSink *sink);

  Q_INVOKABLE void scanImage(const QUrl &fileUrl);

  Q_PROPERTY(QVideoSink *videoSink MEMBER _sink WRITE setVideoSink)

signals:
  void validCodeDetected(const QString code);
  void imageScanFailed(const QString message);

private:
  QVideoSink *_sink = nullptr;
  QThreadPool _threadPool;
};
} // namespace QRLite