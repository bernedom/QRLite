#include <SimpleCollage/project.h>

#include <QFile>
#include <QImage>

namespace SimpleCollage {
void Project::addImage(const QFile &path) {

  if (!path.exists()) {
    throw std::invalid_argument("The image file does not exist.");
  }
  QImage image(path.fileName());
  if (image.isNull()) {
    throw std::invalid_argument("The file is not an image.");
  }

  _image = image;
}

const QImage &Project::getImage() const { return _image; }
} // namespace SimpleCollage