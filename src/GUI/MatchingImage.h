/*!
  \file MatchingImage.h
  \brief This file find the most matching images from database corresponding to user drawing and blend them together to 
	* generate shadow image
*/
#include "Descriptor.h"
#include "IndexStorage.h"
#include "ImageVotes.h"
#include "WeightImage.h"
#include "shift.h"
class MatchingImage{
	public:
		//! It will store imgId as index and \ref ImageVotes as value
		unordered_map<int,ImageVotes> votes;
		//! Descriptor object
		Descriptor descriptor;
		//! WeightImage object
		WeightImage Weight;
		//! Maximum number of matching images to be found
		int maxNumber;
		//! Index object
		Index index;   
		//! User drawn image
		Mat img;
		//! path to database files
		string path;
		//! Grid object
		Grid grid;
		//! Constructor
		MatchingImage();
		//! Constructor 2
		MatchingImage(int,string);
		//! Will add votes to different images in the database
		/*! For all the patches of drawn image, it will calculate descriptor, convert it to sketch,
			* calculate 20 such sketch using different \ref Hash function, 
			* match them to database image patch's corresponding sketch and add votes
			* to the database image to which the patch belong using \ref MatchingImage::addVotes function*/
		void castVotes(Mat&);
		//! Helper function to castVotes
		/*! It will add votes to the bins of the image to which the drawn patch matches using \ref ImageVotes::alterVotes 	
			* function. */
		void addVotes(Cell,Entry,int);
		//! Find the images with maximum votes
		void findMaxima();
		//! Further align the matching image to user drawn image
		void fineAlignment(Mat,Mat,int&,int&);
};
