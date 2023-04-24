#include "eye_color.h"
//#include "eye.h"
#include "eye_coord.h"
#include <vector>
#include <iostream>

cv::Vec3b black(0,0,0);
cv::Vec3b white(255, 255, 255);
std::vector<int> green1{25, 150, 130};
std::vector<int> green2{20,100,100};
std::vector<int> brown{55, 40, 25};
std::vector<int> grey{129, 136, 143};
std::vector<int> red{0, 0, 255};

Iris::Iris(std::vector<cv::Point> tmp_eye1, std::vector<cv::Point> tmp_eye2, cv::Mat tmp_image):
_eye1(tmp_eye1), _eye2(tmp_eye2), _image(tmp_image)
{
    center1= _eye1[0];
    center2=_eye2[0];
    _radius_eye1 = radius(_eye1);
    _radius_eye2 = radius(_eye2);
}


Iris::Iris(std::vector<std::pair<double,double>> tmp_eye1, std::vector<std::pair<double,double>> tmp_eye2, cv::Mat tmp_image):
_image(tmp_image) 
{
    for(int i = 0; i < tmp_eye1.size(); i++){
        cv::Point tmp_point(tmp_eye1[i].first * _image.cols, tmp_eye1[i].second*_image.rows);
        _eye1.push_back(tmp_point);
        int k = tmp_eye2[i].first * _image.cols;
        int j = tmp_eye2[i].second*_image.rows;
        tmp_point = {k,j};
        _eye2.push_back(tmp_point);
    }

    center1 = _eye1[0],
    center2 =_eye2[0],
     _radius_eye1 = radius(_eye1);
     _radius_eye2 = radius(_eye2);
}



double Iris::distance(cv::Point p1, cv::Point p2){
    double a = (p1.x-p2.x)*(p1.x-p2.x);
    double b = (p1.y-p2.y)*(p1.y-p2.y);
    double distance = sqrt(a+b);
    return distance;
}

double Iris::radius(std::vector<cv::Point>& points){
    double _radius = INT_MIN;
    for(int i = 0; i < points.size(); i++){
        if(i == 0) continue;
        _radius = std::max(_radius, distance(points[0], points[i]));
    }
    return _radius;
}


bool approxiamtion(const cv::Vec3b& pixel1, const cv::Vec3b& pixel2){
    bool k = true;
    for(int i = 0; i < 3; i++){
        int mx = std::max(pixel1[i], pixel2[i]);
        int mn = std::min(pixel1[i], pixel2[i]);
        if(mx-mn>=10){
            k = false;
        }
    }
    return k;
}


bool Iris::in_ellipse(int x, int y, int a, int b, int center_x, int center_y){
    double first = (x - center_x)*(x - center_x);
    double a_pw = a*a;
    double b_pw = b*b;
    double second = (y - center_y)*(y - center_y);
    if(first/a_pw+second/b_pw > 1 || first/b_pw + second/a_pw >1) return false;
    return true;
}


double euclideanDist(cv::Point p, cv::Point q) {
    return std::sqrt((p.x - q.x)*(p.x - q.x) + (p.y-q.y)*(p.y-q.y));
}



bool isInsideElipse(cv::Point point, double a, double b, cv::Point center){
    if((std::pow(point.x - center.x ,2)/std::pow(a,2)) + (std::pow(point.y - center.y ,2)/std::pow(b,2)) <= 1){
        return true;
    }
    return false;
}


void changeEyeColor(cv::Mat& image, const std::vector<cv::Point>& points){
    std::cerr << points[0] << std::endl;
    std::cerr << points[1] << std::endl;
    std::cerr << points[2] << std::endl;
    std::cerr << points[3] << std::endl;
    std::cerr << points[4] << std::endl;
    cv::Point center = points[0];
    cv::Point left, right;
    if(points[1].x < points[3].x){
         left = points[1];
         right = points[3];
    }
    else{
         right = points[1];
         left = points[3];
    }
    cv::Point upper = points[2];
    cv::Point lower = points[4];
    double leftDistance = euclideanDist(left, center);
    double upperDistance = euclideanDist(upper, center);
    double rightDistance = euclideanDist(right, center);
    double lowerDistance = euclideanDist(lower, center);
    for(int i = upper.y; i < left.y; i++){
        for(int j = left.x; j < upper.x; j++){
            if(isInsideElipse(cv::Point(j,i), leftDistance, upperDistance, center) && (leftDistance/3 < euclideanDist(center, cv::Point(j,i)))){
                image.at<cv::Vec3b>(i, j)[0] /= 3;
                if(image.at<cv::Vec3b>(i, j)[1] + 30 > 255){
                    image.at<cv::Vec3b>(i, j)[1] = 255;
                }
                else image.at<cv::Vec3b>(i, j)[1] += 30;
            }
        }
    }
    for(int i = upper.y; i < right.y; i++){
        for(int j = upper.x; j <= right.x; j++){
            if(isInsideElipse(cv::Point(j,i), rightDistance, upperDistance, center) && (leftDistance/3 < euclideanDist(center, cv::Point(j,i)))){
                image.at<cv::Vec3b>(i, j)[0] /= 3;
                if(image.at<cv::Vec3b>(i, j)[1] + 30 > 255){
                    image.at<cv::Vec3b>(i, j)[1] = 255;
                }
                else image.at<cv::Vec3b>(i, j)[1] += 30;
            }
        }
    }
    for(int i = left.y; i <= lower.y; i++){
        for(int j = left.x; j < lower.x; j++){
            if(isInsideElipse(cv::Point(j,i), leftDistance, lowerDistance, center) && (leftDistance/3 < euclideanDist(center, cv::Point(j,i)))){
                image.at<cv::Vec3b>(i, j)[0] /= 3;
                if(image.at<cv::Vec3b>(i, j)[1] + 30 > 255){
                    image.at<cv::Vec3b>(i, j)[1] = 255;
                }
                else image.at<cv::Vec3b>(i, j)[1] += 30;
            }
        }
    }
    for(int i = right.y; i <= lower.y; i++){
        for(int j = lower.x; j <= right.x; j++){
            if(isInsideElipse(cv::Point(j,i), rightDistance, lowerDistance, center) && (leftDistance/3 < euclideanDist(center, cv::Point(j,i)))){
                image.at<cv::Vec3b>(i, j)[0] /= 3;
                if(image.at<cv::Vec3b>(i, j)[1] + 30 > 255){
                    image.at<cv::Vec3b>(i, j)[1] = 255;
                }
                else image.at<cv::Vec3b>(i, j)[1] += 30;
            }
        }
    }
}

void Iris::color(){
    changeEyeColor(_image, _eye2);
    changeEyeColor(_image, _eye1);
}


    // for(int i = 0; i < _image.cols; i++){
    //     for(int j = 0; j < _image.rows; j++){
    //         cv::Point p(i,j);
    //          int a1 = center1.y-_eye1[2].y;
    //         int b1 = center1.x-_eye1[1].x;
    //         int a2 = center2.y-_eye2[2].y;
    //         int b2 = center2.x-_eye2[1].x;
    //         if(in_ellipse(i, j, a1, b1, center1.x, center1.y) 
    //         || in_ellipse(i, j, a2, b2, center2.x, center2.y)){
    //             cv::Vec3b& pixel = _image.at<cv::Vec3b>(p);
    //             if(approxiamtion(pixel, white)|| approxiamtion(pixel, black) ) {
    //                 continue;
    //             }
    //             if(distance(p, center1)<=_radius_eye1/3 || distance(p, center2)<=_radius_eye2/3)continue;
    //             if(pixel[0]<50 ) pixel[0]+=50;
    //             if(pixel[1]<50 ) pixel[1]+=50;
    //             if(pixel[2]<50 ) pixel[2]+=50;
    //             pixel[0] = ((pixel[0]+green1[0])/2+pixel[0])/2 + green1[0]/20;
    //             pixel[1] = ((pixel[1]+green1[1])/2+pixel[1])/2 + green1[1]/20;
    //             pixel[2] = ((pixel[2]+green1[2])/2+pixel[2])/2 + green1[2]/20;
    //         }
            
    //     }
    // }


