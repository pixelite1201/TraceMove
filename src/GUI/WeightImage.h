/*!
  \file WeightImage.h
  \brief This file contains the Weight Matrix
*/
#include "Correlation.h"
class WeightImage{
	public:
		//! Most matching image from the database
		vector<Mat> matchingImg;
		//! User drawn image
		Mat _testImg;
		//! Different oriented image for _testImg
		OrientedImage testImg;
		//! Final Weight matrix for all matching images
		vector<Mat> W;
		//! Spatially varying matrix for all matching images
		vector<Mat> V;
		//! Global matching term for all matching images
		vector<double> v;
		//! Constructor1
		WeightImage();
		//! Constructor2
		WeightImage(int,Mat);
		//! fill the matchingImg vector
		void fillImg(int,Mat);
		//! Calculate final Weight matrix using v,V and hscore
		void calculate();
};
