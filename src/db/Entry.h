/*!
  \file Entry.h
  \brief This file describe data structure for descriptor entries stored in database
*/
class Entry {
 public:
	//! sketch value generated for the patch is stored
	int sketch;
	//! imgId to which the patch belong
	int imgId;
	//! location of lower left hand corner of image patch in entire image
	int x;
	//! location of lower left hand corner of image patch in entire image
	int y;
	//! Constructor
Entry(int,int,int,int);
// bool operator==(const Entry& a) const ;
//bool operator<(const Entry&);
};
