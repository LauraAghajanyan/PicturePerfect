#include <iostream>
#include "functionFilter.h"

using namespace cv;
using namespace std;

void blurImage(cv::Mat& image)
{
    cv::GaussianBlur(image, image, cv::Size(11, 11), 0);
}
void blurImage(Image& img)
{
    cv::Mat image=ImageToMat(img);
    cv::GaussianBlur(image, image, cv::Size(11, 11), 0);
    img=MatToImage(image);
}

void makeGray(cv::Mat& image){
    cv::cvtColor(image, image, 6);
}

void makeGray(Image& img){
    cv::Mat image=ImageToMat(img);
    cv::cvtColor(image, image, 6);
    img=MatToImage(image);
}

void date_and_time(Image& img ){
    cv::Mat mat=ImageToMat(img);
    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }
    time_t now = time(0);
    struct tm tstruct;
    char text[80];
    tstruct = *localtime(&now);
    strftime(text, sizeof(text), "%d.%m.%Y %X", &tstruct);
    string date_time = text;
    Scalar brightness = mean(mat);
    int font = FONT_HERSHEY_SIMPLEX; //tareri dzev
    double font_scale = 0.9; //tarachap
    Scalar font_color;
    if (brightness[0] < 127) {
        font_color = Scalar(255, 255, 255);
    } else {
        font_color = Scalar(0, 0, 0);
    }
    int font_thickness = 2;
    Size text_size = getTextSize(date_time, font, font_scale, font_thickness, nullptr);
    Point text_pos(mat.cols - text_size.width - 10, mat.rows - text_size.height - 10);
    putText(mat, date_time, text_pos, font, font_scale, font_color, font_thickness);
    img=MatToImage(mat);
} 

void date_and_time(cv::Mat& mat ){
    
    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }
    time_t now = time(0);
    struct tm tstruct;
    char text[80];
    tstruct = *localtime(&now);
    strftime(text, sizeof(text), "%d.%m.%Y %X", &tstruct);
    string date_time = text;
    Scalar brightness = mean(mat);
    int font = FONT_HERSHEY_SIMPLEX; //tareri dzev
    double font_scale =0.9; //tarachap
    Scalar font_color;
    if (brightness[0] < 127) {
        font_color = Scalar(255, 255, 255);
    } else {
        font_color = Scalar(0, 0, 0);
    }
    int font_thickness = 2;
    Size text_size = getTextSize(date_time, font, font_scale, font_thickness, nullptr);
    Point text_pos(mat.cols - text_size.width - 10, mat.rows - text_size.height - 10);
    putText(mat, date_time, text_pos, font, font_scale, font_color, font_thickness);
   
} 

void applyFilter(Mat& image, Scalar color)
{
    Mat filter(image.size(), image.type(), color);
    addWeighted(image, 0.5, filter, 0.5, 0, image);
}
void five_filters(Image& img) {
    cv::Mat mat = ImageToMat(img);
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    int width = mat.cols / 5;
    vector<Scalar> filter_colors = {
        Scalar(255, 0, 0),   // blue filter
        Scalar(0, 255, 0),   // green filter
        Scalar(0, 0, 255),   // red filter
        Scalar(0, 255, 255), // yellow filter
        Scalar(255, 0, 255)  // purple filter
    };
    Mat combined(mat.rows, mat.cols, mat.type(), Scalar(0, 0, 0));
    for (int i = 0; i < 5; i++) {
        vector<Point> pts(4);
        pts[0] = Point(i * width, 0);
        pts[1] = Point((i + 1) * width, 0);
        pts[2] = Point((i + 1) * width, mat.rows);
        pts[3] = Point(i * width, mat.rows);
        Mat mask(mat.size(), CV_8UC1, Scalar(0));
        fillConvexPoly(mask, pts, Scalar(255));
        Mat roi(mat.size(), mat.type(), filter_colors[i]);
        mat.copyTo(roi, mask);
        applyFilter(roi, filter_colors[i]);
        roi.copyTo(combined, mask);
    }
    img = MatToImage(combined);
}
void five_filters(cv::Mat& mat) {
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    int width = mat.cols / 5;
    vector<Scalar> filter_colors = {
        Scalar(255, 0, 0),   // blue filter
        Scalar(0, 255, 0),   // green filter
        Scalar(0, 0, 255),   // red filter
        Scalar(0, 255, 255), // yellow filter
        Scalar(255, 0, 255)  // purple filter
    };
    Mat combined(mat.rows, mat.cols, mat.type(), Scalar(0, 0, 0));
    for (int i = 0; i < 5; i++) {
        vector<Point> pts(4);
        pts[0] = Point(i * width, 0);
        pts[1] = Point((i + 1) * width, 0);
        pts[2] = Point((i + 1) * width, mat.rows);
        pts[3] = Point(i * width, mat.rows);
        Mat mask(mat.size(), CV_8UC1, Scalar(0));
        fillConvexPoly(mask, pts, Scalar(255));
        Mat roi(mat.size(), mat.type(), filter_colors[i]);
        mat.copyTo(roi, mask);
        applyFilter(roi, filter_colors[i]);
        roi.copyTo(combined, mask);
    }
      mat=combined;
}

void Grain(cv::Mat& mat){
    if (mat.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noise = cv::Mat::zeros(mat.size(), mat.type());
    randn(noise, cv::Scalar::all(0), cv::Scalar::all(30)); // mean=0, SD=50
    mat+=noise;
}

void Grain(Image& img){
    cv::Mat mat = ImageToMat(img);
    if (mat.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noise = cv::Mat::zeros(mat.size(), mat.type());
    randn(noise, cv::Scalar::all(0), cv::Scalar::all(30)); // mean=0, SD=50
    mat+=noise;
    img = MatToImage(mat);

}

void regulate_size(cv::Mat& image1,cv::Mat& image2){
    cv::Size imageSize=image2.size();
    cv::resize(image1,image1,imageSize);
}


void _AdamHands(cv::Mat& mat){
   std::string  _path = "Images/Screenshot 2023-04-14 at 22.07.08.png"; 
    cv::Mat _art =  cv::imread(_path);       
    makeGray(_art);
    makeGray(mat);
    regulate_size(_art, mat);
    cv::addWeighted(mat, 0.7, _art, 0.5, 0.0, mat);
    return;
}

void _AdamHands(Image& img){
    cv::Mat mat = ImageToMat(img);
    std::string  _path = "Images/Screenshot 2023-04-14 at 22.07.08.png"; 
    cv::Mat _art =  cv::imread(_path);       
    makeGray(_art);
    makeGray(mat);
    regulate_size(_art, mat);
    cv::addWeighted(mat, 0.7, _art, 0.5, 0.0, mat);
    img = MatToImage(mat);
    return;
}

void _add_rain(cv::Mat& mat){
    std::string rain_path = "Images/rain-texture-on-black-background-vector-31712235.jpg";
    cv::Mat rain = cv::imread(rain_path);
    regulate_size(rain, mat);
    cv:: addWeighted(mat, 0.9, rain, 0.7, 0.0, mat);
}

void _add_rain(Image& img){
    cv::Mat mat = ImageToMat(img);
    std::string rain_path = "Images/rain-texture-on-black-background-vector-31712235.jpg";
    cv::Mat rain = cv::imread(rain_path);
    regulate_size(rain, mat);
    cv:: addWeighted(mat, 0.9, rain, 0.7, 0.0, mat);
    img = MatToImage(mat);
}

void _add_snow(cv::Mat& mat){
    std::string snow_path = "Images/Image Preview rain.jpg";
    cv::Mat snow = cv::imread(snow_path);
    regulate_size(snow,mat);
    cv:: addWeighted(mat, 0.9, snow, 0.7, 0.0, mat);
}

void _add_snow(Image& img){
     cv::Mat mat = ImageToMat(img);
    std::string snow_path = "Images/Image Preview rain.jpg";
    cv::Mat snow = cv::imread(snow_path);
    regulate_size(snow,mat);
    cv:: addWeighted(mat, 0.9, snow, 0.7, 0.0, mat);
     img = MatToImage(mat);
}

void _add_sparkles(cv::Mat& mat){
    std::string sparkles_path = "Images/skynews-star-sky-night-somerset_4641946.jpg";
    cv::Mat sparkles = cv::imread(sparkles_path);
    regulate_size(sparkles,mat);
    cv:: addWeighted(mat, 0.9, sparkles, 0.7, 0.0, mat);
}

void _add_sparkles(Image& img){
    cv::Mat mat = ImageToMat(img);
    std::string sparkles_path = "Images/skynews-star-sky-night-somerset_4641946.jpg";
    cv::Mat sparkles = cv::imread(sparkles_path);
    regulate_size(sparkles,mat);
    cv:: addWeighted(mat, 0.9, sparkles, 0.7, 0.0, mat);
    img = MatToImage(mat);
}


void clown(Image& img){
    cv::Mat mat = ImageToMat(img);
    cv::CascadeClassifier noseDetection;
    if(!noseDetection.load("XML files/haarcascade_nose.xml")){
        std::cout << "XML file not loaded" << std::endl;
        std::exit(0);
    }
    std::vector<Rect> noses;
    noseDetection.detectMultiScale(mat, noses); //detecting faces
    if(noses.size()==0){
        return;
    }
    cv::Mat ball;
    ball = cv::imread("Images/red-ball-removebg-preview.png");
    cv::resize(ball, ball, Size(noses[0].width, noses[0].height), INTER_LINEAR);
    mat.at<cv::Vec3b>(0, 0) = ball.at<cv::Vec3b>(0, 0);
    for(int i = noses[0].x; i < noses[0].x + noses[0].width; i++){
        for(int j = noses[0].y; j < noses[0].y + noses[0].height; j++){
            if(!(ball.at<cv::Vec3b>(j - noses[0].y, i - noses[0].x)[0] == 0 && ball.at<cv::Vec3b>(j - noses[0].y, i - noses[0].x)[1] == 0
             && ball.at<cv::Vec3b>(j - noses[0].y, i - noses[0].x)[2] == 0)){
                mat.at<cv::Vec3b>(j, i) = ball.at<cv::Vec3b>(j - noses[0].y, i - noses[0].x);
            }
        }
    }
    img = MatToImage(mat);
}

void detectFace(Image& img){
    cv::Mat image = ImageToMat(img);
    cv::CascadeClassifier faceDetection;
    if(!faceDetection.load("XML files/haarcascade_face.xml")){
        std::cout << "XML file not loaded" << std::endl;
        std::exit(0);
    }
    std::vector<Rect> faces;
    faceDetection.detectMultiScale(image, faces); //detecting faces
    if(faces.size()==0){
        return;
    }
        cv::Point p1(faces[0].x, faces[0].y);
        cv::Point p2((faces[0].x + faces[0].height), (faces[0].y + faces[0].width));
        cv::rectangle(image, p1, p2, cv::Scalar(0, 0, 255), 2, 8, 0);
    img = MatToImage(image);
}