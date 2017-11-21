/*!
  \file CurvePoints.h
  \brief This file contains the data structure used to store curvePoints
*/
#include "DrawnSkeleton.h"
#include "Point.h"
#include<iostream>
#include<limits.h>
#include<math.h>
#include<set>
#include<sstream>
#include<fstream>
class CurvePoints{
public:
//!  This will store the subjoint of each skeleton joint
vector<vector<POINT> > skeleton_midPt;
//! This will store the original curvepoints drawn by user
vector<vector<POINT> > curvePoints;
//! This will store the bezier curvepoints fitted on the curvepoints drawn by user and stored in curvePoints
vector<vector<POINT> > curvePoints2;
//! This will store the curvepoints on the basis of their distance to the skeleton subjoints stored in skeleton_midPt.
/*! Each of the subjoint  
	* has a representative joint and the curvepoints will get associated to that representative joint.
	* If they are associated with subjoint of joint 0, then 
	* they will be stored in rigPoints[0] and so on.
     */
vector<vector<POINT> > rigPoints;
//! This will store the curvepoints that are nearest to original skeleton joints instead of sub joints. 
/*! They are stored separately as they are associated with two bones joining the joint.
     */
vector<vector<POINT> > rigPoints_dualWt;
//! This will store the curvepoints after finally dividing them into separate curves using threshold value.
/*! A boolean value is store with every curve that told whether the curve is associated with single bone 
	* or two bones. 
*/
vector<vector<pair<vector<POINT>,bool> > > final_rigPoints;
//!Constructor
CurvePoints();
//! Erase the curve after rigging is done
/*! It will take the point clicked by the user, search the nearest curve to it and remove it from
	* final_rigPoints
*/
POINT erase_curve2(POINT);
/*!It will take the user clicked point as input and return the index of the curve
	* nearest to this clicked point from final_rigPoints */
POINT min_dist_curvePoints(POINT);
//! Helper function to assign_skeleton_midPt function
void midPt_helper(int ,int ,DrawnSkeleton&);
//! Divide the skeleton joints into subjoints
/*! With the help of midPt_helper function, it will take two end points of bones
	* stored in SkeletonNodes and generate four more subjoints at equal distance */
void assign_skeleton_midPt(DrawnSkeleton);
/*! It will take the curve as input and attached the curvepoints to the nearest skeleton joint
	* and store them in rigPoints and rigPoints_dualWt depending on the nearest skeleton joint
*/
void riggingPerCurve(vector <POINT>);
/*! It will be used during manual rigging. Input is the curve and the vector of user clicked skeleton joint 
	* along with two more joints linked to skeleton joint. The function will search for the nearest 
	* distance skeleton joint in the vector of joints passed in iniput.
	* It will associate curvepoints to the skeleton joints using rigPoints and rigPoints_dualWt.
*/
void riggingPerCurve(vector<POINT>,vector<int>);
/*! The function will take curve and skeleton joint as input. To reassociate curvepoints to the skeleton joint
	*selected by user, it will create a vector of skeleton joint along with 2 more skeleton joint linked 
	* with user selected skeleton joint and pass the curve and the  to the function riggingPerCurve to do
	* the rigging
	*/
void manualRigging(vector<POINT>,int);
//! Call riggingPerCurve function to rig different curves
void rigging();
//! Divide the rigPoints into final_rigPoints using threshold value.
/*!  It will take the curve store in rigPoints and rigPoints_dualWt and further divide
	* them into different curves if the distance between neighboring points is greater
	* than threshold. Thus we will get 3D vector, with first index showing the skeleton
	* joint with which its associated, second index is the number of different curves
	* associated to that skeleton joint and third index is a pair of vector and boolean value
	* such that vector consist of all curvepoint and boolean value denote whether the 
	* curve is associated with single or double bone.
*/
void divideCurve();
//! Find distance between two points
float find_dist(POINT,POINT);
//! Erase the curve after rigging is not done
/*! It will take the point clicked by the user, search the nearest curve to it and remove it from
	* curvePoints.
*/
int erase_curve(POINT);
};
