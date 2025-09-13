#pragma once

#include <QtCore/QObject>
#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QVideoSink>
#include <QtMultimedia/qvideosink.h>
#include <qvariant.h>

namespace QRLite {
class CodeReader : public QObject {
  Q_OBJECT

public:
  explicit CodeReader(QObject *parent = nullptr) : QObject(parent) {};
  ~CodeReader() override {};

  void onVideoFrameChanged(const QVideoFrame &frame);

  void setVideoSink(QVideoSink *sink);

  Q_PROPERTY(QVideoSink *videoSink MEMBER _sink WRITE setVideoSink)

private:
  QVideoSink *_sink = nullptr;
};
} // namespace QRLite