#include "iris_tracking.hpp"
#include <iostream>

int main (){

    Iris i("mediapipe/graphs/iris_tracking/iris_tracking_cpu.pbtxt");

   while(true) {
        cv::Mat image = cv::imread("/home/karen/Downloads/Lenna.png");
       i.SetCurrentImage(image);
        while(!i.isProcessed()){
            sleep(1);
        }
       auto x = i.Get();
       for(auto l : x){
        std::cout<< "X " << l.first << "y "<< l.second<<std::endl;
       }
   }

}