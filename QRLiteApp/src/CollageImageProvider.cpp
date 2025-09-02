#include "CollageImageProvider.h"

#include <QPixmap>
#include <qpixmap.h>

CollageImageProvider::CollageImageProvider(
    const QRLite::Project &project)
    : QQuickImageProvider(QQuickImageProvider::Pixmap), project(project) {}

CollageImageProvider::~CollageImageProvider() {}

QPixmap CollageImageProvider::requestPixmap(const QString &id, QSize *size,
                                            const QSize &requestedSize) {

  QPixmap pixmap;
  if (id == "collage") {
    pixmap = QPixmap::fromImage(project.getImage());
  }
  return pixmap;
};