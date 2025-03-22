#include <SimpleCollage/project.h>

#include <QImage>

namespace SimpleCollage
{
    void Project::addImage(const std::string& path)
    {

      QImage image(QString::fromStdString(path));
      _image = image;
    }

    const QImage& Project::getImage() const
    {
        return _image;
    }
}