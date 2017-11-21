/*!
  \file ImageVotes.h
  \brief This file find the maximum votes per image
*/
#include "Grid.h"
#include<vector>
class ImageVotes{
	public:
		//! Max location offset difference allowed between drawn patch and database patch
		int offsetSize;
		//! imgId for which votes are stored
		int imgId;
		//! Store the patch location for drawn image
		Grid grid;
		//! This is used to find the maximum displacement of the matching image
		/*! Since user drawn image may be slightly shifted from the database image, we need to find 
			* this displacement and align the matching image to drawn image. For this, instead of 
			* storing votes for the image, we will divide the votes in different bins where each 
			* bin correspond to displacement of the matching patch and the drawn image patch. The 
			* offset value of the bin with maximum votes is the final displacement of the matching 
			* image.
		*/
		vector<vector<int> > offsets;
		//! maxVotes for the image
		int maxVotes;
		//! bin in X direction with maximum votes
		int maxbinX;
		//! bin in Y direction with maximum votes
		int maxbinY;
		//! Constructor
		ImageVotes(int imgId,Grid grid);
		//! Will alter votes in offsets on the basis of value provided by new descriptor.
		/*! dx and dy are the displacement of the matching patch to user drawn patch in x 
			* and y direction. This will be used to increment the votes in corresponding bin.
			* and l is the maximum number of sketches of drawn image patch
			* that matches to database image patch.*/
		int alterVotes(int dx,int dy,int l);
};


