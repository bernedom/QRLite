#pragma once

#include <QtCore/QObject>
#include <QtGui/QImage>

class QFile;

namespace SimpleCollage {
class Project : public QObject {
  Q_OBJECT
public:
  Q_PROPERTY(QImage image READ getImage NOTIFY imageChanged)

  void addImage(const QFile &path);
  const QImage &getImage() const { return _collage; };

signals:
  void imageChanged();

private:
  void createCollage();

private:
  QList<QImage> _images;
  QImage _collage;
};
} // namespace SimpleCollage