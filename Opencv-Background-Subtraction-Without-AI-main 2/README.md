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