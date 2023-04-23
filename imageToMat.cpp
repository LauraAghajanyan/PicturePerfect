#include "imageToMat.h"

cv::Mat ImageToMat(Image& img) // taking Image and coverting to cv::Mat
{
    int type;
    if (img.channels == 1) 
    {
        type = CV_8UC1;
    } 
    else 
    {
        type = CV_8UC3;
    }
    cv::Mat mat(img.height,img.width,type,img.data);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    return mat;
}

Image MatToImage(cv::Mat& mat) // taking cv::Mat and converting to Image
{
    Image img;
    img.width = mat.cols;
    img.height = mat.rows;
    img.channels = mat.channels();

    // Allocate memory for image data
    img.data = new unsigned char[img.width * img.height * img.channels];

    // Copy image data
    int index = 0;
    for (int i = 0; i < img.height; ++i) {
        for (int j = 0; j < img.width; ++j) {
            if (img.channels == 1) 
            {
                img.data[index] = mat.at<uchar>(i, j);
            } 
            else 
            {
                const cv::Vec3b& color = mat.at<cv::Vec3b>(i, j);
                img.data[index] = color[2];
                img.data[index + 1] = color[1];
                img.data[index + 2] = color[0];
            }
            index += img.channels; 
        }
    }
    return img;
}

