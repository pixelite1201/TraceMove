/*!
  \file FailSafe.h
  \brief This file will write all the data values that are constant after the first frame is done. They are 
	* needed if we close the interface and then reopen the animation frames later.
*/
#include "scribblearea.h"
class FailSafe{
public:
//! write datavalue to file FS
/*! It will take ScribbleArea class and path to store the file as input. Following values are written to the file.
	*<ul>
	*	<li> nodecount,base_x,base_y.
	*	<li> bone_scale, inverse_bone_scale.
	*	<li> BVH file data values as position and subjoints of skeleton in skeleton_midPt
	*</ul>
*/
void write(ScribbleArea* S,string path);
//! read datavalue from file FS
/*! It will take ScribbleArea class and path where the file is stored as input. Following values are read from the file 
	* and stored.
	*<ul>
	*	<li> nodecount,base_x,base_y.
	*	<li> bone_scale, inverse_bone_scale.
	*	<li> BVH file data values in position and subjoints of skeleton in skeleton_midPt
	*</ul>
*/
void read(ScribbleArea* S,string path);
};
