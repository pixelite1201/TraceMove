#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
class Steerable{
	public:
		Mat C1,C2,C3;
		double g2f1_[7],g2f2_[7],g2f3_[7],h2f1_[7],h2f2_[7],h2f3_[7],h2f4_[7];
		Mat g2f1x,g2f2x,g2f3x,h2f1x,h2f2x,h2f3x,h2f4x;
		Mat g2f1y,g2f2y,g2f3y,h2f1y,h2f2y,h2f3y,h2f4y;
		Mat G2a,G2b,G2c,H2a,H2b,H2c,H2d;
		Mat img;
		Steerable();
		Steerable(Mat& img);
		void applyFilter();
		void saveOrientedImages();
		void calculate(Mat&,Mat&,int);
};
