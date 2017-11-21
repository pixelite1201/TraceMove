/*!
  \file ResultSet.h
  \brief This file consist of matching result patches found for user drawn image
*/
#include<iostream>
#include "Entry.h"
#include<unordered_map>
#include<iterator>
#include<vector>
using namespace std;
class Hasher
{
public:
	//! Helper class for \ref ResutSet::m
  size_t operator() (Entry const& key) const
  {
     
         return ((hash<int>()(key.imgId)
               ^ (hash<int>()(key.x) << 1)) >> 1)
               ^ (hash<int>()(key.y) << 1);
  
  }
};

class EqualFn
{
public:
  bool operator() (Entry const& t1, Entry const& t2) const
  {
   return t1.imgId==t2.imgId && t1.x==t2.x && t1.y==t2.y;
  }
};

class ResultSet {
public:
//! Store all the result matching entries from database for the corresponding user drawn patches
/*! Its 2dimensional with first dimension denoting total number of matches for different hash function out of 20 
	*and second dimension cosist of 
	* entries from database having those many matches. For e.g. result[3][] will consist of all those entries in 
	* database such that on applying 20 different hash function and generating sketches 3 of the sketch match*/
vector<vector<Entry> > results; 
/*! Consist of map with entry as index and total number of matching of different sketch values on applying different hash function on the 
	*same patch*/
  unordered_map<Entry,int,Hasher,EqualFn> m;
  ResultSet(int);
//! Function to add matching entry to unorderer_map \ref ResultSet::m
	/*! It will first find whether the entry is already present in the map. Note that same entry means imgId and patch location
		* are same but sketch may be different. The value of map is increased if more entries matches. This is done because for 		*every descriptor we have calculate \ref Index::total_sketch
		* number of different sketch by applying different hash function. If most of the sketch matches the entry stored in map then 			* it means thats the corresponding entry is highly matched descriptor. While if only some of them match than its not a good 
		* match. 
	*/
  void add(Entry);
/*! Sort the entries stored in \ref ResultSet::m with entries having most no. of matches at top and least no. of matches at bottom and store 		*them in \ref ResultSet::results */
  void sort();
  
};
  
