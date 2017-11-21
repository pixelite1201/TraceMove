/*!
  \file RetrievedSkeleton.h
  \brief This file will store the datavalues read from converted bvh file.
*/
#include "DrawnSkeleton.h"
#include<vector>
#include<limits.h>
#include<fstream>
#include<iostream>
#include<sstream> 
#include<math.h>
using namespace std;
class RetrievedSkeleton{
public:
//! Will store the datavalues read from converted bvh file.
/*! 2D vector with index 1 denoting the frame and index 2 denoting the skeleton joints coordinates
*/
vector<vector<POINT> > position;
//! Contain the frameNo from database matching the user drawn skeleton and will keep on incrementing as new frames are generated
int frameNo;
//! Contain total join count of skeleton
int node_count;
//! Contain total frames in db
int total_skeleton;
//! Constructor
RetrievedSkeleton();
//! Read the data values from the file
void read();
//! Find the frameNo with most matching skeleton to user drawn skeleton
/*! Will find the sum of distance of all the coordinates of user drawn skeleton to db skeleton for all the frames.
	* One with minimum distance is the most matching skeleton.
*/
void compare(DrawnSkeleton*);
//! Find difference between two consecutive frame's joints
/*! Will take drawn skeleton coordinates as input and a boolean value denoting whether the difference should be calculated with
	* previous frame or with next frame. 
*/
void find_diff(DrawnSkeleton*,int);

};
