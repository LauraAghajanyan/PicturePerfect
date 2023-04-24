#ifndef IRIS_TRACKING_H
#define IRIS_TRACKING_H
#pragma once

class Iris{
  private:
    cv::Mat _currentImage;
    bool _isDirty;
    bool _isProcessed;
    std::vector<std::pair<double, double>> landmark_list_vec;
    std::string _graphFileLocation;

    absl::Status RunMPPGraph();
  public:

    Iris(std::string graphFileLocation);
    void SetCurrentImage(cv::Mat imgData);
    bool isProcessed(){return _isProcessed;}
    std::vector<std::pair<double, double>> Get();
};
#endif