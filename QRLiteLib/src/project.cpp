#include <QRLite/project.h>

#include <QFile>
#include <QImage>
#include <QPainter>

namespace QRLite {
void Project::addImage(const QFile &path) {

  if (!path.exists()) {
    throw std::invalid_argument("The image file does not exist.");
  }
  QImage image(path.fileName());
  if (image.isNull()) {
    throw std::invalid_argument("The file is not an image.");
  }

  _images.append(image);
  createCollage();
  emit imageChanged();
}

void Project::createCollage() {
  if (_images.empty()) {
    _collage = QImage();
  }

  // Calculate the size of the collage
  int collageWidth = 0;
  int collageHeight = 0;

  for (const auto &image : _images) {
    collageWidth += image.width();
    collageHeight = std::max(collageHeight, image.height());
  }
  QSize collageSize(collageWidth, collageHeight);
  _collage = QImage(collageSize, QImage::Format_RGB32);
  QPainter painter(&_collage);

  int currentX = 0;
  int currentY = 0;
  for (const auto &image : _images) {
    painter.drawImage(currentX, currentY, image);
    currentX += image.width();
  }
}

} // namespace QRLite