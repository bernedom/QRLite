#include <QRLite/CodeReader.h>

#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QVideoSink>

#include <QtCore/QDebug>

#include <QRLite/Scanner.h>
#include <qdebug.h>
#include <qimage.h>

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

  // skip frame if all threads are busy
  if (_threadPool.activeThreadCount() >= _threadPool.maxThreadCount()) {
    return;
  }

  // Todo refactor for more efficiency, merge with scanner
  _threadPool.start([frame, this]() {
    QRLite::Scanner scanner;
    QImage image = frame.toImage();
    const auto result = scanner.scan(image);

    if (result.has_value()) {
      emit validCodeDetected(result.value());
    } else {
      qDebug() << "No code detected:" << result.error().message;
    }
  });
}
} // namespace QRLite