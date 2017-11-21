/*!
  \file Descriptor.h
  \brief This file contains values of descriptor and functions used to calculate and modify them
*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include<iostream>
#include<math.h>
#include<vector>
#include "Histogram.h"
#define FUN(M,i,j,type) M.at<type>(i,j)
using namespace std;
using namespace cv;
class Descriptor{
public:		
//! Patch size
	/*! Since the image is divided into small patches
		* patch size define the size of these patches
	*/
	int patchSize;
	//! blurInitial define the amout of gaussian blur applied on image initially
	double blurInitial;
	//! Standard deviation for Gaussian blur of image
	double sigma ;
	//! To prevent division from zero in normalized magnitude calculation small value is used in denominator
	double epsilon;
	//! Range of 3D histogram
	int xbuck;int ybuck;int tbuck;
	//! Range of 3D histogram for resampling
	int xbuck2;int ybuck2;int tbuck2;
	//! threshold value is used to convert descriptor into binary descriptor
		/*! When the value at any point in histogram is greater than threshold its 
		*set to 1 and when its less than threshold its set to 0
	*/
	double threshold;
	//! Used to define whether the patch is considered blank or not
	double minimumEdge;
	//! Used to define whether the pixel value can be considered as edge or not
	/*! Initialized to 0.02. If gradient at any pixel is less than this then its 
		* not considered as edge pixel and its value is not added in histogram
	*/
	double minPixVal;
	//! Range of histogram
	double histogramRange;
	double increment;
	//! Standard deviation for Gaussian blur of histogram
	int sigma1,sigma2;
	//! Store the orientation at all pixels of image
	Mat orientation;
	//! Store normalized magnitude at all pixels of image
	Mat norMagnitude;
	//! Constructor
	Descriptor();
	//!Initialize Descriptor values for offline processing
	/*! Since some of the descriptor values for online and offline 
		*processing are different. Hence, offline values are
		* initialized using this function 
	*/ 
	Descriptor offLine();
	Descriptor Query();
	/*! Return Number of bits in 3D histogram after converting float values to binary on 
		* basis of \ref Descriptor:: threshold value
	*/
	int getNumBits();
	//! Calculate normalized magnitude and orientation at every pixel
	/*! First the image is blurred so that slight difference in two image patches
		* won't treat them as different. Next, gradient and orientation at 
		* at every pixel is calculated. The gradient is normalized by 
		* dividing it with Gaussian blurred window
	*/
	void setImage(Mat&);
	void calc(int,int,vector<bool> &desc);
	
};

