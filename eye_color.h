#pragma once

#include <iostream>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>



enum Color{
    color1 = 25,
    color2 = 55,
    color3 = 85
};

class Iris{
public:
    Iris(std::vector<cv::Point>, std::vector<cv::Point>, cv::Mat);
    Iris(std::vector<std::pair<double,double>>, std::vector<std::pair<double,double>>, cv::Mat);
    void color();
    
    void show(){
        //print();
        imshow("image", _image);
        cv::waitKey(0);
    }
private:
    void print(){
        std::cout <<  _radius_eye1 << " "<<_radius_eye2 <<std::endl;
        std::cout << center1 << " " << center2 << std::endl;
    }
    double radius(std::vector<cv::Point>&);
    double distance(cv::Point, cv::Point);
    bool in_ellipse(int x, int y, int a, int b, int, int);
private:
    double _radius_eye1, _radius_eye2;
    cv::Point center1, center2;
    cv::Mat _image;
    std::vector<cv::Point> _eye1;
    std::vector<cv::Point> _eye2;
};