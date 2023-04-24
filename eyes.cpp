#include "glasses.h"
#include "filters.h"

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eye_cascade;
using namespace cv;




/**
 * Function to detect human face and the eyes from an image.
 *
 * @param  im    The source image
 * @param  tpl   Will be filled with the eye template, if detection success.
 * @param  rect  Will be filled with the bounding box of the eye
 * @return zero=failed, nonzero=success
 */
int detectEye(cv::Mat& im, cv::Mat& tpl, cv::Rect& rect1, cv::Rect& rect2)
{
	std::vector<cv::Rect> faces, eyes;
	face_cascade.detectMultiScale(im, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, cv::Size(30,30));

	for (int i = 0; i < faces.size(); i++)
	{
		cv::Mat face = im(faces[i]);
		eye_cascade.detectMultiScale(face, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE, cv::Size(20,20));


		if (eyes.size() >= 2)
		{
			rect1 = ((eyes[0].x<eyes[1].x)?eyes[0]:eyes[1]) + cv::Point(faces[i].x, faces[i].y);
            rect2 = ((eyes[0].x>eyes[1].x)?eyes[0]:eyes[1]) + cv::Point(faces[i].x, faces[i].y);
			tpl  = im(rect1);
		}else if(eyes.size()){
            rect1 = eyes[0] + cv::Point(faces[i].x, faces[i].y);
            tpl  = im(rect1);
        }
	}

	return eyes.size();
}

int eye_dist(const cv::Rect& r1, const cv::Rect& r2){
    int x1 = r1.x > r2.x ? r2.x: r1.x;
    int x2 = (x1 == r2.x)? r1.x+r1.width: r2.x+r2.width;
    return x2 - x1; 
}
/**
 * Perform template matching to search the user's eye in the given image.
 *
 * @param   im    The source image
 * @param   tpl   The eye template
 * @param   rect  The eye bounding box, will be updated with the new location of the eye
 */
void trackEye(cv::Mat& im, cv::Mat& tpl, cv::Rect& rect1)
{
	cv::Size size(rect1.width * 2, rect1.height * 2);
   // cv::Size size(rect2.width * 2, rect2.height * 2);
	cv::Rect window(rect1 + size - cv::Point(size.width/2, size.height/2));
	
	window &= cv::Rect(0, 0, im.cols, im.rows);

	cv::Mat dst(window.width - tpl.rows + 1, window.height - tpl.cols + 1, CV_32FC1);
	cv::matchTemplate(im(window), tpl, dst, CV_TM_SQDIFF_NORMED);

	double minval, maxval;
	cv::Point minloc, maxloc;
	cv::minMaxLoc(dst, &minval, &maxval, &minloc, &maxloc);

	if (minval <= 0.2)
	{
		rect1.x = window.x + minloc.x;
		rect1.y = window.y + minloc.y;
	}
	else
		rect1.x = rect1.y = rect1.width = rect1.height = 0;
}


void size(Paintings p,cv::Mat& art, int eye_distance, int eye_width){
    if(eye_distance==0) return;
    if(p==MonaLisa){
        cv::resize(art, art, cv::Size(eye_width*7, eye_width));
        return;
    }
    cv::resize(art, art, cv::Size(eye_width*5, eye_width*2));
}

int euclid(cv::Point p1, cv::Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}



cv::Rect _dest(int rows, int cols, cv::Point center1, cv::Point center2, int eye_width){
    cv::Rect dest;
    cv::Point first, second; 
    first.x = std::min(center1.x,center2.x);
    first.y = (first.x == center1.x)? center1.y: center2.y;
    second = first == center1? center2: center1;
    int eye_dist = euclid(center1, center2);
    int mid = first.x+eye_dist/2;
    dest.x = mid - cols/2;
    dest.y = first.y+eye_width/5;
    dest.height = rows;
    dest.width = cols;
    return dest;
}
bool check(cv::Vec3b pixel, Paintings p)
{
   if(pixel == cv::Vec3b(255, 255, 255) || pixel == cv::Vec3b(0, 255, 0)) return true;
   return false;
}


void print_on_image(cv::Mat& _image, const cv::Mat& art, cv::Rect r, Paintings p){
    for(int i=0;i<r.width;i++){
        if(i+r.x > _image.cols ) continue;
        for(int j=0;j<r.height;j++){
            if(j+r.y>_image.rows)continue;
            if(check(art.at<cv::Vec3b>(j, i), p))
            {
                continue;
            }
            _image.at<cv::Vec3b>(j+r.y,i+r.x) = art.at<cv::Vec3b>(j, i);
        }
    }
}

void _SunGlasses(cv::Mat& image,int _eye_dist, cv::Rect& eye1){
    cv::Point center1, center2;
    int eye_width;
    center1 = {eye1.x, eye1.y};
    center2 = {eye1.x+_eye_dist, eye1.y};
    eye_width = eye1.width;
    std::string _path = "/Users/NellyVardanyan/ACA/filter3/art/glasses_blue.png";
    cv::Mat _art = imread(_path);
    int eye_distance = _eye_dist;
    size(BlackGlasses, _art, eye_distance, eye_width);
    cv::Rect r;
    r = _dest(_art.rows, _art.cols, center1, center2, eye_width);
    cv::Mat destRoi;
    try {
        destRoi = image(r);
    }  catch (...) {
        return;
    }
    print_on_image(image,_art, r, BlackGlasses);
}

void _MonaLisa(cv::Mat& image,int _eye_dist, cv::Rect& eye1){
    cv::Point center1, center2;
    int eye_width;
    center1 = {eye1.x, eye1.y};
    center2 = {eye1.x+_eye_dist, eye1.y};
    eye_width = eye1.width;
    std::string _path = "/Users/NellyVardanyan/ACA/filter3/art/Screenshot 2023-04-13 at 15.48.50.png";
    cv::Mat _art = imread(_path);
    int eye_distance = _eye_dist;
    size(MonaLisa, _art, eye_distance, eye_width);
    cv::Rect r;
    r = _dest(_art.rows, _art.cols, center1, center2, eye_width);
    cv::Mat destRoi;
    try {
        destRoi = image(r);
    }  catch (...) {
        return;
    }
    print_on_image(image,_art, r, BlackGlasses);
}

void glasses(cv::Mat& frame){
    face_cascade.load("/Users/NellyVardanyan/ACA/filter3/haarcascade_frontalface_alt2.xml");
eye_cascade.load("/Users/NellyVardanyan/ACA/filter3/haarcascade_eye_tree_eyeglasses.xml");

if (face_cascade.empty() || eye_cascade.empty())
 		return;

    cv::Mat eye_tpl;
	cv::Rect eye_bb1, eye_bb2;
    int eye_distance;
    cv::Mat gray;
		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (eye_bb1.width == 0 && eye_bb1.height == 0)
		{
			// Detection stage
			// Try to detect the face and the eye of the user
			detectEye(gray, eye_tpl, eye_bb1, eye_bb2);
            eye_distance = eye_dist(eye_bb1, eye_bb2);
            if(eye_distance){
                _SunGlasses(frame, eye_distance, eye_bb1);
            }
		}
		else
		{
			// Tracking stage with template matching
			trackEye(gray, eye_tpl, eye_bb1);
            detectEye(gray, eye_tpl, eye_bb1, eye_bb2);
            eye_distance = eye_dist(eye_bb1, eye_bb2);
            if(eye_distance){
                _SunGlasses(frame, eye_distance, eye_bb1);
            }
		}
}
void monalisa(cv::Mat& frame){
    face_cascade.load("/Users/NellyVardanyan/ACA/filter3/haarcascade_frontalface_alt2.xml");
eye_cascade.load("/Users/NellyVardanyan/ACA/filter3/haarcascade_eye_tree_eyeglasses.xml");

if (face_cascade.empty() || eye_cascade.empty())
 		return;

    cv::Mat eye_tpl;
	cv::Rect eye_bb1, eye_bb2;
    int eye_distance;
    cv::Mat gray;
		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (eye_bb1.width == 0 && eye_bb1.height == 0)
		{
			// Detection stage
			// Try to detect the face and the eye of the user
			detectEye(gray, eye_tpl, eye_bb1, eye_bb2);
            eye_distance = eye_dist(eye_bb1, eye_bb2);
            if(eye_distance){
                _MonaLisa(frame, eye_distance, eye_bb1);
            }
		}
		else
		{
			// Tracking stage with template matching
			trackEye(gray, eye_tpl, eye_bb1);
            detectEye(gray, eye_tpl, eye_bb1, eye_bb2);
            eye_distance = eye_dist(eye_bb1, eye_bb2);
            if(eye_distance){
                _MonaLisa(frame, eye_distance, eye_bb1);
            }
		}
}