#include <QRLite/Scanner.h>

#include <ZXing/BarcodeFormat.h>
#include <ZXing/ImageView.h>
#include <ZXing/ReadBarcode.h>
#include <ZXing/ReaderOptions.h>

#include <QDebug>
#include <expected>
#include <qlogging.h>

namespace QRLite {

std::expected<QString, ScannerError> Scanner::scan(const QString &path) const {
  QImage image(path);
  if (image.isNull()) {
    return std::unexpected(ScannerError("Could not open image " + path));
  }
  return scan(image);
}

std::expected<QString, ScannerError> Scanner::scan(const QImage &image) const {

  if (image.isNull()) {
    return std::unexpected(ScannerError("Image is null"));
  }

  const auto rgbImage = image.convertToFormat(QImage::Format_RGB888);

  if (rgbImage.isNull()) {
    return std::unexpected(
        ScannerError("Failed to convert image to RGB format"));
  }

  const ZXing::ImageView imageView(rgbImage.bits(), rgbImage.width(),
                                   rgbImage.height(), ZXing::ImageFormat::RGB,
                                   rgbImage.bytesPerLine());

  ZXing::ReaderOptions decoderOptions;
  decoderOptions.setFormats(ZXing::BarcodeFormat::Any);

  const auto results = ZXing::ReadBarcodes(imageView, decoderOptions);

  if (results.empty()) {
    return std::unexpected(ScannerError("No QR code found"));
  }

  QStringList messages;
  for (const auto &result : results) {
    if (!result.isValid()) {
      messages << "Invalid QR code";
      continue;
    }
    messages << QString::fromStdString(result.text());
  }

  return messages.join(", ");
}

} // namespace QRLite