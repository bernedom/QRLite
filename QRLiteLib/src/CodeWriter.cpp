#include "QRLite/CodeWriter.h"

namespace QRLite {

QImage CodeWriter::writeCode(const QString &code) {
  // Placeholder implementation
  if (code.isEmpty()) {
    return QImage(); // Return an empty image
  }
  QImage image(100, 100, QImage::Format_ARGB32);
  image.fill(Qt::white);
  return image;
}
} // namespace QRLite