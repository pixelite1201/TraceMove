#include "Hash.h"
Hash::Hash(int total_hashf=0,int bitsPerHash=0,int Descriptorbits=0) {
  bph = bitsPerHash;//cout<<bitsPerHash<<endl;
    int numBitsToCheck = pow(2,bitsPerHash); //why its required? can't be use directly from numDescriptorBits
    indices.resize(total_hashf);
for(int i=0;i<total_hashf;i++)
indices[i].resize(numBitsToCheck);
    for(int i = 0; i < total_hashf; i++) {
      for(int j = 0; j < numBitsToCheck; j++) {
        indices[i][j] = rand()%Descriptorbits; //  make this avoid duplicates??
 

		}
	}
}
void Hash :: showHash(){
	for(int i = 0; i < indices.size(); i++) {
		for(int j = 0; j < indices[i].size(); j++) {
			cout<<indices[i][j]<<" " ;
		}
	}cout<<endl;
}
Hash::Hash(vector<vector<int> > &indices){
	this->indices=indices;
	int c = indices[0].size();
	
	bph = (int) (log(c)/log(2));
}
int Hash:: calcSketch(vector<bool>& descriptor) {
	int numMins = indices.size(), numBitsToCheck = indices[0].size()-1;
	int sig = 0;
	for(int i = 0; i < numMins; i++) { 
		sig <<= bph; 
		for(int j = 0; j < numBitsToCheck; j++) {
			if(descriptor[indices[i][j]]) {

				sig |= j;
				break;
			}
		}
	}
	return sig;
}


