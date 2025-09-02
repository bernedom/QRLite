#pragma once

#include <QtQuick/QQuickImageProvider>
#include <QRLite/project.h>

class CollageImageProvider : public QQuickImageProvider {
public:
  CollageImageProvider(const QRLite::Project &project);
  ~CollageImageProvider();

  QPixmap requestPixmap(const QString &id, QSize *size,
                        const QSize &requestedSize) override;

private:
  const QRLite::Project &project;
};