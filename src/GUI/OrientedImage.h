/*!
  \file OrientedImage.h
  \brief This file contains the data structure used to store curvePoints
*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include<iostream>
#include<math.h>
#include "Steerable.h"
using namespace std;
using namespace cv;
class OrientedImage{
	public:
		Mat img;
		//! Eight different orientation images
		vector<Mat> direction;
		//! Consist of orientation at all pixels of image
		Mat orientation;
		//! Consist of magnitude at all pixels of image
		Mat mag; // just because its required by steerable class(you can overload the method in steerable class)
		//! Constructor1
		OrientedImage(Mat&);
		//! Constructor2
		OrientedImage();
		//! Calculate and divide the image into eight different oriented images
		void calculateOrient();
		//! Blur the oriented images to provide slight invariance in position
		void blur();
};
