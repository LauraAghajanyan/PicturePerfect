#include "imageToQImage.h"

QImage ImageToQImage(Image& img)  // taking Image and converting it to QImage
{
    QImage::Format format;
        if (img.channels == 1) {
            format = QImage::Format_Grayscale8;
        } else {
            format = QImage::Format_RGB888;
        }

    QImage image(img.data, img.width, img.height, format);
    return image;
}

Image QImageToImage(QImage& image) // taking QImage and coverting it to Image
{
    Image img;
    img.width = image.width();
    img.height = image.height();
    img.channels = image.isGrayscale() ? 1 : 3;

    // Allocate memory for image data
    img.data = new unsigned char[img.width * img.height * img.channels];

    // Copy image data
        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width; ++x) {
                QColor color = QColor::fromRgb(image.pixel(x, y));
                int index = (y * img.width + x) * img.channels;
                img.data[index] = color.red();
                img.data[index + 1] = color.green();
                img.data[index + 2] = color.blue();
            }
        }
    return img;
}
