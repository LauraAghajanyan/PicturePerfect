#pragma once

#include "imageExport.h"
#include <opencv2/opencv.hpp>

cv::Mat ImageToMat(Image& img); // stanum enq struktura u darcnum Mat

Image MatToImage(cv::Mat& mat); //stanum enq Mat darcnum enq Image
