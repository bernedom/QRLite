#pragma once

#include <QtGui/QImage>

class QFile;

namespace SimpleCollage {
class Project {
public:
  void addImage(const QFile &path);
  const QImage &getImage() const { return _collage; };

private:
  void createCollage();

private:
  QList<QImage> _images;
  QImage _collage;
};
} // namespace SimpleCollage