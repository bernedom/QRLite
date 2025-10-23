#include "QRLite/CodeWriter.h"

#include <ZXing/BarcodeFormat.h>
#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>
#include <qtypes.h>

namespace QRLite {

QImage CodeWriter::writeCode(const QString &code) {
  // Placeholder implementation
  if (code.isEmpty()) {
    return QImage(); // Return an empty image
  }

  ZXing::BarcodeFormat format = ZXing::BarcodeFormat::QRCode;
  ZXing::MultiFormatWriter writer(format);

  const auto bitMatrix = writer.encode(code.toStdString(), 0, 0);
  const auto matrix8Bit = ZXing::ToMatrix<uint8_t>(bitMatrix);

  QImage image(matrix8Bit.data(), matrix8Bit.width(), matrix8Bit.height(),
               matrix8Bit.width(), QImage::Format_Grayscale8);

  return image;
}

void CodeWriter::saveCodeToFile(const QString &code, const QString &filePath) {
  QImage image = writeCode(code);
  if (!image.isNull()) {
    image.save(filePath);
  }
}
} // namespace QRLite