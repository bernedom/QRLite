#include <QRLite/scanner.h>

#include <ZXing/BarcodeFormat.h>
#include <ZXing/ImageView.h>
#include <ZXing/ReadBarcode.h>
#include <ZXing/ReaderOptions.h>

#include <QDebug>
#include <qlogging.h>

namespace QRLite {

QString Scanner::scan(const QString &imagePath) const {
  QImage image;
  if (!image.load(imagePath)) {
    return QString("Failed to load image: %1").arg(imagePath);
  }
  return scan(image);
}

QString Scanner::scan(const QImage &image) const {

  if (image.isNull()) {
    return QString();
  }

  const auto rgbImage = image.convertToFormat(QImage::Format_RGB888);

  if (rgbImage.isNull()) {
    return QString("Failed to convert image to RGB format");
  }

  const ZXing::ImageView imageView(rgbImage.bits(), rgbImage.width(),
                                   rgbImage.height(), ZXing::ImageFormat::RGB,
                                   rgbImage.bytesPerLine());

  ZXing::ReaderOptions decoderOptions;
  decoderOptions.setFormats(ZXing::BarcodeFormat::Any);

  const auto results = ZXing::ReadBarcodes(imageView, decoderOptions);

  if (results.empty()) {
    return QString("No QR code found");
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