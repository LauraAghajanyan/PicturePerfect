#pragma once
#include "imageToMat.h"

void makeGray(cv::Mat& image);
void makeGray(Image& img);

void blurImage(cv::Mat& image);
void blurImage(Image& img);

void date_and_time(Image& img );
void date_and_time(cv::Mat& mat);

void five_filters(Image& img);
void five_filters(cv::Mat& mat);

void Grain(Image& img);
void Grain(cv::Mat& mat);

void _AdamHands(Image& img);
void _AdamHands(cv::Mat& mat);

void _add_rain(Image& img);
void _add_rain(cv::Mat& mat);

void _add_snow(Image& img);
void _add_snow(cv::Mat& mat);

void _add_sparkles(Image& img);
void _add_sparkles(cv::Mat& mat);

void clown(Image& img);

void detectFace(Image& img);
