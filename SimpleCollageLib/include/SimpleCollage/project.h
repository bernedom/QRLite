#pragma once

#include <QtGui/QImage>

class QFile;

namespace SimpleCollage {
class Project {
public:
  void addImage(const QFile &path);
  const QImage &getImage() const;

private:
  QImage _image;
};
} // namespace SimpleCollage