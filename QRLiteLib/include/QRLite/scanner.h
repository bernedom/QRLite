#pragma once 

#include <QImage>
#include <QString>

namespace QRLite{

    class Scanner {
    public:
      
        QString scan(const QImage& image);
    };
}