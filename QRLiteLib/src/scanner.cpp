#include <QRLite/scanner.h>

#include <ZXing/BarcodeFormat.h>
#include <ZXing/ImageView.h>
#include <ZXing/ReadBarcode.h>
#include <ZXing/ReaderOptions.h>

namespace QRLite {

QString Scanner::scan(const QImage &image) {

  if (image.isNull()) {
    return QString();
  }

  const auto rgbImage = image.convertToFormat(QImage::Format_RGB888);

  if (rgbImage.isNull()) {
    return QString("Failed to convert image to RGB format");
  }

  const ZXing::ImageView imageView(rgbImage.bits(), rgbImage.width(),
                                   rgbImage.height(), ZXing::ImageFormat::RGB);

  ZXing::ReaderOptions decoderOptions;
  decoderOptions.setTryHarder(true);
  decoderOptions.setTryRotate(true);

  decoderOptions.setFormats(ZXing::BarcodeFormat::MatrixCodes);

  const auto result = ZXing::ReadBarcodes(imageView, decoderOptions);

  if (result.size() == 0) {
    return QString("No valid codes found");
  }

  return QString::fromStdString("QRLite");
}

} // namespace QRLite