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
  // Todo implement efficiently
  QRLite::Scanner scanner;
  QImage image = frame.toImage();
  QString result = scanner.scan(image);
  qDebug() << "Scan result: " << result;
}
} // namespace QRLite