#pragma once
#include <iostream>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/face.hpp"
#include <vector>


void glasses(cv::Mat& image);
void monalisa(cv::Mat& image);
