/*!
  \file Correlation.h
  \brief This file calculate the positive and negative correlation between test image and matching image
*/
#include "OrientedImage.h"
class Correlation{
public:
//! Different oriented image of matching image from database
OrientedImage matchImg;
//! Different oriented image of test image from database
OrientedImage testImg;
//! Positive correlation
Mat positiveC;
//! Negativa correlation
Mat negativeC;
//! hScore calculated using positive and negative correlation
double hScore;
//! Constructor
Correlation(OrientedImage&, OrientedImage&);
//! Calculate different oriented image and update the correlation and hscore
void calcOrientedImage();
};
