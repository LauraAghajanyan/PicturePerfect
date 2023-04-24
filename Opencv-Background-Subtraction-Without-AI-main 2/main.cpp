/*
 * Algorithm
 *
 * Save the initial reference frame from the video (in grayscale and saturation scale).
 *
 * Grayscale and hsv channels should be added to any additional frames that are arriving.
 *
 * Each new frame's saturation and grayscale should be compared to the reference frame.
 *
 * Mark the pixel and store it in a new Mat file if the absolute value differences are greater than 25.
 *
 *  then erode + dilate (2 times) to this frame.
 *
 *  In the gray channel domain, look for non-zero pixels and mark them for the output image.
 *
 *  Remaining zero pixels were marked in the output image during Step 6's saturation domain check.
 *
 *  If there are still zero pixels present, indicating that they are backdrop, you can replace them with the chosen background.
 *
 * NOTE!
 *
 * 1- You shouldn't be in front of the camera at first because the camera should take a reference frame.
 * 2-Camera should be stationary.
 *
*/


#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;
using namespace std;


// The code defines a function named "subtractionOfImages" that takes two arguments, which are images of type
// "Mat" and returns an image of the same type as the inputs. The purpose of the function is to subtract the
// second image from the first one, and the resulting image contains only the differences between the two images.


//The function starts by applying a median blur to both images to remove noise. Then, it loops through the
// rows and columns of the first image, processing the image by blocks of 5x5 pixels. For each block, the
// function calculates the sum of the pixel values in the block for both the first and second image. It then
// calculates the average of these sums and checks if the difference between the two averages is greater than 25.
// If the difference is greater than 25, it sets the pixel values in the resulting image for the corresponding block
// to zero, indicating that there is a difference between the two images in that block.

Mat subtractionOfImages(Mat firstImg, Mat secondImg);

Mat subtractedImg = Mat::zeros(Size(1280,720),CV_8UC3);
Mat frameGlobal;
int main()
{

    Mat background = imread("/ur/backGroundImage/dir/bg.jpg");

    VideoCapture cap(0);

    namedWindow("Source",WINDOW_NORMAL);
    namedWindow("Result",WINDOW_NORMAL);
    namedWindow("WithBackground",WINDOW_NORMAL);


    int frameCounter = 0;
    Mat frame,hsv,hsvPrev,framePrev,subtractedImgGray;

    while (1)
    {
        cap >> frame;
        if(frame.data)
        {
            frameGlobal = frame;
            cvtColor(frame, hsv, COLOR_BGR2HSV);
            cvtColor(frame, frame, COLOR_BGR2GRAY);
            vector<Mat>hsvChannels;
            split(hsv,hsvChannels);
            hsv = hsvChannels[1];

            if(frameCounter == 0 || frameCounter == 1) {
                framePrev = frame;
                hsvPrev = hsv;
            }
            else {
                Mat resultSourceImg = subtractionOfImages(frame,framePrev);
                Mat resultSourceImg2 = subtractionOfImages(hsv,hsvPrev);
                Mat resultSourceImg3 = resultSourceImg.clone();
                Mat element = getStructuringElement( MORPH_ELLIPSE,
                                                        Size( 2*3 + 1, 2*3+1 ),
                                                        Point( 5, 5 ) );
                Mat element2 = getStructuringElement( MORPH_ELLIPSE,
                                                        Size( 2*3 + 1, 2*3+1 ),
                                                        Point( 5, 5 ) );

                erode(resultSourceImg,resultSourceImg,element);
                dilate(resultSourceImg,resultSourceImg,element2);
                erode(resultSourceImg2,resultSourceImg2,element);
                dilate(resultSourceImg2,resultSourceImg2,element2);
                for(int m=0; m<frameGlobal.rows; m++) {
                    for(int n=0; n<frameGlobal.cols; n++) {
                        if((int)resultSourceImg.at<Vec3b>(Point(n,m))[1] != 0) {
                            resultSourceImg.at<Vec3b>(Point(n,m))[0] = frameGlobal.at<Vec3b>(Point(n,m))[0];
                            resultSourceImg.at<Vec3b>(Point(n,m))[1] = frameGlobal.at<Vec3b>(Point(n,m))[1];
                            resultSourceImg.at<Vec3b>(Point(n,m))[2] = frameGlobal.at<Vec3b>(Point(n,m))[2];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[0] = frameGlobal.at<Vec3b>(Point(n,m))[0];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[1] = frameGlobal.at<Vec3b>(Point(n,m))[1];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[2] = frameGlobal.at<Vec3b>(Point(n,m))[2];
                        }

                        else if((int)resultSourceImg2.at<Vec3b>(Point(n,m))[1] != 0) {
                            resultSourceImg.at<Vec3b>(Point(n,m))[0] = frameGlobal.at<Vec3b>(Point(n,m))[0];
                            resultSourceImg.at<Vec3b>(Point(n,m))[1] = frameGlobal.at<Vec3b>(Point(n,m))[1];
                            resultSourceImg.at<Vec3b>(Point(n,m))[2] = frameGlobal.at<Vec3b>(Point(n,m))[2];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[0] = frameGlobal.at<Vec3b>(Point(n,m))[0];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[1] = frameGlobal.at<Vec3b>(Point(n,m))[1];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[2] = frameGlobal.at<Vec3b>(Point(n,m))[2];

                        }
                        else {
                            resultSourceImg3.at<Vec3b>(Point(n,m))[0] = background.at<Vec3b>(Point(n,m))[0];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[1] = background.at<Vec3b>(Point(n,m))[1];
                            resultSourceImg3.at<Vec3b>(Point(n,m))[2] = background.at<Vec3b>(Point(n,m))[2];
                        }
                    }
                }

                imshow("Result",resultSourceImg);
                imshow("WithBackground",resultSourceImg3);
                imshow("Source",frameGlobal);
                subtractedImg = Mat::zeros(Size(1280,720),CV_8UC3);
            }
            frameCounter++;
            int c = waitKey(1);
            if((char)c == 'c')
                break;
        }
    }

    destroyAllWindows();

    return 0;
}



Mat subtractionOfImages(Mat firstImg, Mat secondImg)
{

    medianBlur(firstImg,firstImg,3);
    medianBlur(secondImg,secondImg,3);
    for(int i=0; i<firstImg.rows;i+=5)
    {
        for(int j=0; j<firstImg.cols;j+=5)
        {
            int sumFirst = 0, sumSecond = 0;
            if(j+5<firstImg.cols && i+5<firstImg.rows)
            {
                sumFirst += (int)firstImg.at<uchar>(Point(j,i)) + (int)firstImg.at<uchar>(Point(j+1,i)) + (int)firstImg.at<uchar>(Point(j+2,i)) + (int)firstImg.at<uchar>(Point(j+3,i))
                        + (int)firstImg.at<uchar>(Point(j+4,i)) + (int)firstImg.at<uchar>(Point(j,i+1)) + (int)firstImg.at<uchar>(Point(j+1,i+1))
                        + (int)firstImg.at<uchar>(Point(j+2,i+1)) + (int)firstImg.at<uchar>(Point(j+3,i+1)) + (int)firstImg.at<uchar>(Point(j+4,i+1)) + (int)firstImg.at<uchar>(Point(j,i+2))
                        + (int)firstImg.at<uchar>(Point(j+1,i+2)) + (int)firstImg.at<uchar>(Point(j+2,i+2)) + (int)firstImg.at<uchar>(Point(j+3,i+2)) + (int)firstImg.at<uchar>(Point(j+4,i+2))
                        + (int)firstImg.at<uchar>(Point(j,i+3)) + (int)firstImg.at<uchar>(Point(j+1,i+3)) + (int)firstImg.at<uchar>(Point(j+2,i+3)) + (int)firstImg.at<uchar>(Point(j+3,i+3))
                        + (int)firstImg.at<uchar>(Point(j+4,i+3)) + (int)firstImg.at<uchar>(Point(j,i+4)) + (int)firstImg.at<uchar>(Point(j+1,i+4)) + (int)firstImg.at<uchar>(Point(j+2,i+4))
                        +(int)firstImg.at<uchar>(Point(j+3,i+4)) + (int)firstImg.at<uchar>(Point(j+4,i+4));

                sumSecond += (int)secondImg.at<uchar>(Point(j,i)) + (int)secondImg.at<uchar>(Point(j+1,i)) + (int)secondImg.at<uchar>(Point(j+2,i)) + (int)secondImg.at<uchar>(Point(j+3,i))
                        + (int)secondImg.at<uchar>(Point(j+4,i)) + (int)secondImg.at<uchar>(Point(j,i+1)) + (int)secondImg.at<uchar>(Point(j+1,i+1))
                        + (int)secondImg.at<uchar>(Point(j+2,i+1)) + (int)secondImg.at<uchar>(Point(j+3,i+1)) + (int)secondImg.at<uchar>(Point(j+4,i+1)) + (int)secondImg.at<uchar>(Point(j,i+2))
                        + (int)secondImg.at<uchar>(Point(j+1,i+2)) + (int)secondImg.at<uchar>(Point(j+2,i+2)) + (int)secondImg.at<uchar>(Point(j+3,i+2)) + (int)secondImg.at<uchar>(Point(j+4,i+2))
                        + (int)secondImg.at<uchar>(Point(j,i+3)) + (int)secondImg.at<uchar>(Point(j+1,i+3)) + (int)secondImg.at<uchar>(Point(j+2,i+3)) + (int)secondImg.at<uchar>(Point(j+3,i+3))
                        + (int)secondImg.at<uchar>(Point(j+4,i+3)) + (int)secondImg.at<uchar>(Point(j,i+4)) + (int)secondImg.at<uchar>(Point(j+1,i+4)) + (int)secondImg.at<uchar>(Point(j+2,i+4))
                        +(int)secondImg.at<uchar>(Point(j+3,i+4)) + (int)secondImg.at<uchar>(Point(j+4,i+4));

                int avgFirst = sumFirst / 25;
                int avgSecond = sumSecond / 25;

                if(abs(avgFirst-avgSecond)>25)
                {
                    subtractedImg.at<Vec3b>(Point(j,i))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+1,i))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+2,i))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+3,i))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+4,i))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j,i+1))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+1,i+1))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+2,i+1))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+3,i+1))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+4,i+1))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j,i+2))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+1,i+2))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+2,i+2))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+3,i+2))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+4,i+2))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j,i+3))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+1,i+3))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+2,i+3))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+3,i+3))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+4,i+3))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j,i+4))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+1,i+4))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+2,i+4))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+3,i+4))[0] = 0;
                    subtractedImg.at<Vec3b>(Point(j+4,i+4))[0] = 0;

                    subtractedImg.at<Vec3b>(Point(j,i))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+1))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+1))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+1))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+1))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+1))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+2))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+2))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+2))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+2))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+2))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+3))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+3))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+3))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+3))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+3))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+4))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+4))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+4))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+4))[1] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+4))[1] = 255;

                    subtractedImg.at<Vec3b>(Point(j,i))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+1))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+1))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+1))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+1))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+1))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+2))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+2))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+2))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+2))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+2))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+3))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+3))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+3))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+3))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+3))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j,i+4))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+1,i+4))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+2,i+4))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+3,i+4))[2] = 255;
                    subtractedImg.at<Vec3b>(Point(j+4,i+4))[2] = 255;

                }
            }
        }
    }
    return subtractedImg;
}

