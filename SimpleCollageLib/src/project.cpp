#include <SimpleCollage/project.h>

#include <QImage>

namespace SimpleCollage
{
    void Project::addImage(const std::string& path)
    {
       
    }

    const QImage& Project::getImage() const
    {
        return _image;
    }
}