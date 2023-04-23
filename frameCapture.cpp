#include "frameCapture.h"

void Camera::startCamera()
{
    m_cap.open(0); 
}

void Camera::endCamera()
{
    m_cap.release();
}

Image Camera::captureImage(int filterNumber)
{
    m_cap >> frame;
    cv::flip(frame, frame, 1);
    switch(filterNumber)
    {
        case 1:
            Grain(frame);
            break;
        case 2:
            makeGray(frame);
            break;
        case 3:
            _add_rain(frame);
            break;
        case 4:
            _AdamHands(frame);
            break;
        case 5:
            date_and_time(frame);
            break;
         case 6:
            blurImage(frame);
            break;
         case 7:
            five_filters(frame);
            break;
         case 8:
            _add_snow(frame);
            break;
         case 9:
            _add_sparkles(frame);
            break;
    }
    return MatToImage(frame);
}

Image Camera::captureOriginalImage()
{
    cv::Mat original;
    m_cap>>original;
    cv::flip(original, original, 1);
    return MatToImage(original);
}