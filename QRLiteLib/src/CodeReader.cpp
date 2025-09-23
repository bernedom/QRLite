#include <QRLite/CodeReader.h>

#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QVideoSink>

#include <QtCore/QDebug>

#include "CodeParser.h"
#include <QRLite/Scanner.h>

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

  static int frameCount = 0;
  frameCount++;
  if (frameCount == 100) {
    emit validCodeDetected(
        "A VERY LONG TEXT with \n LINEBREAKKS AND SPECIAL "
        "CHARACTERS !@#$%^&*()_+ \n and more text to make it long \n and more "
        "text to make it long \n and more text to make"
        "it long \n and                            \n <"
        "a href =\"https://example.com\">https://example.com</a>");
  }

  // Todo refactor for more efficiency, merge with scanner
  _threadPool.start([frame, this]() {
    QRLite::Scanner scanner;
    QImage image = frame.toImage();
    const auto result = scanner.scan(image);

    if (result.has_value()) {
      const auto parsedResult = CodeParser::parse(result.value());
      if (parsedResult.has_value()) {
        emit validCodeDetected(parsedResult.value());
      } else {
        // emit errorDetected(parsedResult.error());
      }
    }
  });
}
} // namespace QRLite