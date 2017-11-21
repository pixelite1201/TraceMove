#include "ImageVotes.h"
#include<iostream>
using namespace std;
ImageVotes :: ImageVotes(int _imgId, Grid _grid):imgId(_imgId),grid(_grid){
	
	maxVotes=0;maxbinX=-1;maxbinY=-1;
	offsetSize=grid.cellOffset/4;
	offsets.resize(offsetSize);
		for(int i=0;i<offsets.size();i++)
			offsets[i].resize(offsetSize);
}
int ImageVotes:: alterVotes(int dx,int dy,int diff){

	int binX=(int)(1+dx/(double)grid.cellOffset);
	int binY=(int)(1+dy/(double)grid.cellOffset);
	if(binX >=0 && binX < 2 && binY >=0 && binY < 2){
	//int binX=(int)(offsetSize/2+dx/(double)grid.cellOffset);
	//int binY=(int)(offsetSize/2+dy/(double)grid.cellOffset);
	//if(binX >=0 && binX < offsetSize && binY >=0 && binY < offsetSize){
		offsets[binX][binY]+=diff;
		if(offsets[binX][binY]>maxVotes){
			
			maxVotes=offsets[binX][binY];
			maxbinX=binX;
			maxbinY=binY;
		}
		return offsets[binX][binY];
	}
	return 0;
}

