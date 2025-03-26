#pragma once

#include <QtQuick/QQuickImageProvider>
#include <SimpleCollage/project.h>

class CollageImageProvider : public QQuickImageProvider {
public:
  CollageImageProvider(const SimpleCollage::Project &project);
  ~CollageImageProvider();

  QPixmap requestPixmap(const QString &id, QSize *size,
                        const QSize &requestedSize) override;

private:
  const SimpleCollage::Project &project;
};