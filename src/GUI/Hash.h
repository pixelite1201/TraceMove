/*!
  \file Hash.h
  \brief This file describe data structure for hash function
*/
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<vector>
using namespace std;
class Hash {
public:
//! Store Random integer values
/*! It will store random integer values within the 
	*range of 0 to max descriptor size to permute 
	*the index of binary descriptor. Second index
	*consist of hash function. First index denotes
	*total number of hash function needed to generate sketch.
*/
  vector<vector<int> > indices; 
//! \ref Index::bitsPerHash
  int bph;
//! Constructor1
/*! Used when generated from code*/
Hash(int x=0,int y=0,int z=0);
//! Constructor2
/*! Used when already stored hash values are read from file*/
Hash(vector<vector<int> > &);
//! Display hash values
void showHash();
//! Calculate Sketch for a given descriptor
/*! Will apply hash function to descriptor provided as input i.e. 
	* permute the binary descriptor using indices[i] and search for 
	* the lowest index containing 1. This is done for all hash functions stored in
	* /ref Hash::indices and concatenated together to generate final sketch.
*/
int calcSketch(vector<bool>& descriptor);
};
