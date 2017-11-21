#include "Index.h"
#include<limits>

Index::Index(int total_sketch_,int total_hashf_, int Descriptorbits_) {
	total_sketch = total_sketch_;
	total_hashf = total_hashf_;
	bitsPerHash = (int)ceil(log(Descriptorbits_)/log(2));
	Descriptorbits = Descriptorbits_;
	tables.resize(total_sketch);
	
}

void Index::generateHashes() {
	for(int i = 0; i < tables.size(); i++) {
		tables[i]=(Table(Hash(total_hashf, bitsPerHash, Descriptorbits)));
	}
}void Index::fillEntry(vector<bool>& descriptor, int imgId, int x, int y) {

	for(int i = 0; i < tables.size(); i++) {
		tables[i].fillEntry(descriptor, imgId, x, y);
	}
}

void Index:: reverseIndex() {
	for(int i = 0; i < tables.size(); i++) {
		tables[i].reverseIndex();
	}
}


ResultSet* Index:: findAllEntries(vector<bool> &descriptor) {
	ResultSet *found =new ResultSet(tables.size());
	for(int i = 0; i < tables.size(); i++) {
		tables[i].find(descriptor, found, numeric_limits<int>::max());
		
	}
	found->sort();
	return found;
}

ResultSet* Index::findEntries(vector<bool> &descriptor, int max) {
	ResultSet* found = new ResultSet(tables.size());
	for(int i = 0; i < tables.size(); i++) {
		tables[i].find(descriptor, found, max);
	}
	found->sort();
	return found;
}


