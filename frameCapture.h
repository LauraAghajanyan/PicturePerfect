#pragma once
#include "functionFilter.h"
#include "imageToMat.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class Camera
{
public:
    void startCamera();

    void endCamera();

    Image captureImage(int filterNumber);

    Image captureOriginalImage();
private:
    cv::Mat frame;
    cv::VideoCapture m_cap;
};

