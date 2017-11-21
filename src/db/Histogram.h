
/*!
  \file Histogram.h
  \brief This file store values of 3D histogram and functions to calculate and modify them.
*/

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include<iostream>
#include<math.h>
#include<vector>
using namespace std;
using namespace cv;
class Histogram{
	private:
	//! Store the 3D histogram values
	vector<vector<vector<double> > > values;
	
	int xbuck,ybuck,tbuck;
	double x_low,y_low,t_low,x_mult,y_mult,t_mult;
	public:
	//! Constructor
	Histogram(double,double,int,double,double,int,double,double,int);
	//! Will increment the histogram value on the basis of normalized magnitude of pixel
	/*! It will first calculate the bins in which the pixel location and orientation fall and then 
		*using bilinear interpolation it add values to all the bins nearest to the calculated bin
	*/
	void increment(double,double,double,double);
	//! Shows the histogram for a patch in all orientation in image form
	void show();
	//! Blur the histogram to provide robustness.
	void blur(int,int);
	//! Function will return interpolated value
	double interpolate(double, double, double);
	//! Will perform 3D interpolation using \ref Histogram:: interpolate(double,double,double) function
	double bFinalValue(double, double, double );
	//! Resample the histogram value to reduce its size. 
	/*! Instead of taking histogram values at all the bins, histogram values are taken
	    * at some sample bins. If the sample bins are at some intermediate values then
	    * using interpolatioin, values from neighboring bins are stored in the sample
	    * bin. 
	*/
	
	vector<double> resample(int ,int ,int );
};
