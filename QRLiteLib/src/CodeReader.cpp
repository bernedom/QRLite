#include <QRLite/CodeReader.h>

#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QVideoSink>

namespace QRLite {

void CodeReader::setVideoSink(QVideoSink *sink) {
  if (sink == _sink)
    return;

  if (_sink) {
    disconnect(_sink, &QVideoSink::videoFrameChanged, this,
               &CodeReader::onVideoFrameChanged);
  }
  _sink = sink;
  connect(_sink, &QVideoSink::videoFrameChanged, this,
          &CodeReader::onVideoFrameChanged);
};

void CodeReader::onVideoFrameChanged(const QVideoFrame &frame) {
  // Todo implement
}
} // namespace QRLite