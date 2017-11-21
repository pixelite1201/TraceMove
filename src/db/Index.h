/*!
  \file Index.h
  \brief This file describe data structure for descriptor entries stored in database
*/
#include<iostream>
#include<math.h>
#include<vector>
#include "Table.h"
using namespace std;

class Index {
public:
	//! Total no. of sketch per patch
	int total_sketch;
	//! Total min hash functions used to generate sketch 
	int total_hashf;
	//! Number of bits required to denote the maximum index in binary descriptor
	/*! \ref Index::total_hashf  are used to calculate the min hash value which is 
		* the smallest index containing 1 after permuting the binary descriptor. 
		* These min hash values bits are concatenated together to find the final sketch.
		* To concatenate them bits its required to get the maximum number of bits 
		* required to denote the hash value. And max hash value can be the last 
		* index of the descriptor, hence its log_2 of size of descriptor
	*/
	int bitsPerHash;
	//! Number of bits per hash value
	/*! Since histogram is converted to binary hash, size of histogram is equivalent to
		* bitsPerHash.
	*/
	int Descriptorbits;
	//! Its consist of image names of all the images in database.
	/*! This will be used later to retrieve the image from database.
	*/
	vector<string> imageNames;
	//! Data struture to hold all the hash function generated using \ref Index:: generateHashesh() function
	vector<Table> tables;
	//! Constructor
	Index(int=0,int=0,int=0);
	/*! Generate \ref Index::total_sketch number of different \ref Index::total_hashf set of 
		* min hash function. These hash functions are stored in \ref Table
	*/
	void generateHashes();
	//! Call \Table:: reverseIndex() function to generate all the sketches for a descriptor
	void reverseIndex();
	//! Call \Table:: fillEntry() function to generate all the sketches for a descriptor
	void fillEntry(vector<bool>&,int,int,int);
	/*! Take descriptor and will generate all the entries that will be produced for given descriptor 
		* by applying different hash function stored in different \ref Table::table */
	ResultSet* findAllEntries(vector<bool> &) ;
	ResultSet* findEntries(vector<bool>&, int);
};
