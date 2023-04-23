#pragma once

#include "imageExport.h"
#include <QImage>

QImage ImageToQImage(Image& img);  // stanum enq struktura u darcnum QImage

Image QImageToImage(QImage& image); //stanum enq QImage darcnum enq Image
