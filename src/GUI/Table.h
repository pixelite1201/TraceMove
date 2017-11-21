/*!
  \file Table.h
  \brief This file contain all the entries generated for different patches of all the images in database
*/
#include<iostream>
#include<math.h>
#include<vector>
#include<unordered_map>
#include "Hash.h"
#include "ResultSet.h"
using namespace std;
using namespace __gnu_cxx;
class Table{
	public:
		//! All the entries (\ref Entry) generated for different patches of all the images in database using single hash function is stored here.
		vector<Entry> entries;
		//! Store hash functions needed to generate the final sketch from binary descriptor
		Hash hash;
		//! Hashmap is generated for direct access of imgId and location of patch using sketch as index value
		unordered_map <int, int> hashmap;
		//! Constructor1
		Table();
		//! Constructor2
		Table(Hash);
		//!Sort the entries on the basis of sketch, then build \ref Table::hashmap using \ref Table::buildMap()
		void reverseIndex();
		//! Generate \ref Table::hashmap
		/*! Note that there can be many patches with same sketch value S, hence hashmap will just point to the 
			* first entry in the database having sketch S. Since the entries are sorted on the basis of sketch
			* they can be access by travelling linearly*/
		void buildMap();
		//! Will fill the \ref Table::entries with the entry calculated for all the patches of different images using \ref Table::hash defined here
		void fillEntry(vector<bool>&,int,int,int);
		//! It will find all the descriptor in database matching the descriptor of user drawn image
		/*! It will take binary descriptor as input, calculate sketch for it by applying \ref Table::hash function on it.
			* It will then search all the entries i.e. imgId and patch location
			* having same sketch from \ref Table::hashmap. It will add these entries in \ref ResultSet::results
		*/
		void find(vector<bool>&, ResultSet*, int );
		//! It will show all the entries stored in \ref Table::entries
		void show();
};

