/*!
  \file DrawnSkeleton.h
  \brief This file contains data structure used to store user drawn skeleton joints ...
*/

#ifndef DRAWNSKELETON_H_
#define DRAWNSKELETON_H_
#include<vector>
#include "matvec.hpp"
#include "Point.h"
using namespace std;

class DrawnSkeleton{
public:
//! Store the number of joints of skeleton
int node_count;
//! Store whether update() function is called or not
bool update_flag;
//! Store the root joint coordinates
float base_x,base_y;
//! Store the coordinates of skeleton joints. 
vector<POINT> skeletonNodes;
//! Store the diff needed to generate next frame skeleton joints
vector<POINT> diff;
//! Store the inverse scale factor of all joints
vector<float> bone_inverse_scale;
//! Store Binding matrix for all joints
vector<util::math::mat33> Binding;
//! Store Transformation matrix for all joints
vector<util::math::mat33> Transform;
//! Store the new coordinates of old skeleton joints before applying scale factor
vector<POINT> oldSkeletonNodes;
 //! Constructor
DrawnSkeleton();
/*! Calculate skeleton joint with minimum distance to the curvepoint
     *  Curvepoint is passed to this function as argument. Its distance is calculated 
     *  from all the skeletonNodes and the index of the skeletonNode with minimum distance
     *  is returned
     */
int min_dist_skeletonNodes(POINT);
/*! Calculate Binding matrix for all skeleton joints
	* To bring the curvepoints to the same coordinate space as the bones of the skeleton
	* Binding matrix is calculated. Coordinate spcae of skeleton is such that y axis lies 
	* along the bone and x axis lies perpendicular to the bone. This method will first 
	* calculate the angle cos_t and sin_t that the currrent frame
	* bone is making with coordinate axis to create rotation part of the matrix. Binding matrix is combination 
	* of Rotation and Translation matrix, where Translation matrix shift the origin of curvepoints
	* to the skeleton bone parent joint
	* and Rotation matrix will rotate the original coordinate axes such that it matches with joint 
	* coordinate axes.
*/
void update_Binding_Matrix();
/*! Calculate Transformation matrix for all skeleton joints
	* Transformation matrix is calculated to apply the same transformation the the curvepoints as applied 
	* on skeleton joints. This method will first calculate the angle cos_t and sin_t that the next frame 
	* bone is making with coordinate axis to create rotation part of the matrix. And the translation part 
	* of the matrix is the parent joint coordinates. When this matrix is multiplied with Binding matrix, we
	* get the final Transformation matrix whose rotation part will rotate the curve along the new coordinate
	* axes i.e. along the new bone and 
	* translation part will translate it to new origin for the next frame.
	
*/
void update_Transform_Matrix();
/*! Return distance between two points
     */
float find_dist(POINT,POINT);
/*! Calculate new coordinates of skeleton joints after applying scale factor. This method will first store the original 
	* skeletonNodes in oldSkeletonNodes. Then it will bring the bone to origin, apply difference after multiplying it 
	* with inverse scale factor. Scale factor is multiplied as the difference was calculated in database skeleton scale. 
	* And then the new coordinates are shifted from origin to new parent position.
*/
void calculate_newP2();
/*! Will update skeletonNodes coordinate from screen space to skeleton space where root is the origin. Also, it will 
	* update base_x and base_y with root coordinates and node_count with total skeleton joints. update flag is made 1
*/
void update();
};
#endif
