#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include<iostream>
#include<string>
#include<math.h>
#include "Descriptor.h"
#include "IndexStorage.h"
#include<dirent.h>
#include<time.h>
int main(int argc,char** argv){
	clock_t start=clock();
	string path="./DatabaseFiles/";
	Descriptor descriptor;
	descriptor = descriptor.offLine();
	Index index(20,3,descriptor.getNumBits());
	index.generateHashes();
	double patchOverlap=0.5;
	int emptydesc=0;
	int non_emptydesc=0;
	int imageId=0;int countImg=0;
	vector<bool> desc;
	int patchStride = (int)(descriptor.patchSize*patchOverlap); 
	string imgName;
	DIR *dir;
	struct dirent *ent;
	string dirName = "./image/";
	dir = opendir(dirName.c_str());
	if (dir != NULL) {
		while ((ent = readdir(dir)) != NULL) {

			imgName= ent->d_name;
			if(imgName=="." || imgName == "..")
				continue;cout<<imgName<<" "<<countImg++<<endl;

			Mat img = imread(dirName+imgName);
			cvtColor(img,img,CV_BGR2GRAY);
			index.imageNames.push_back(imgName);

			descriptor.setImage(img);
			for(int y = 0; y <= img.rows-descriptor.patchSize; y += patchStride) {  //changed <= to <
				for(int x = 0; x <= img.cols-descriptor.patchSize; x += patchStride) {  //changed <= to <
					desc.clear();

					descriptor.calc(x,y,desc); 

					if(desc.size()>0) {


						index.fillEntry(desc, imageId, x, y);

						emptydesc++;
					} else 
						non_emptydesc++;
				}
			}
			imageId++;
		}
		closedir (dir);

		index.reverseIndex();
		IndexStorage IS;
		IS.write(imgName,index,path);
		clock_t end=clock();
		cout<<(double)(end-start)/CLOCKS_PER_SEC;
	} else {
		cout<<"could not find image directory"<<endl;
	}

}

