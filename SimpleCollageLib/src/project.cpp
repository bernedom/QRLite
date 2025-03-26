#include <SimpleCollage/project.h>

#include <QImage>

namespace SimpleCollage {
void Project::addImage(const std::string &path) {

  QImage image(QString::fromStdString(path));
  if (image.isNull()) {
    throw std::invalid_argument("The image file does not exist.");
  }
  _image = image;
}

const QImage &Project::getImage() const { return _image; }
} // namespace SimpleCollage