#pragma once 

#include <QtGui/QImage>

namespace SimpleCollage
{
    class Project
    {
    public:
        void addImage(const std::string& path);
        const QImage& getImage() const;

    private:
        QImage _image;

        
    };
}