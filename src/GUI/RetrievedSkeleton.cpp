#include "RetrievedSkeleton.h"

RetrievedSkeleton::RetrievedSkeleton(){
frameNo=-1;
total_skeleton=-1;
}
void RetrievedSkeleton::read(){
	ifstream fp;
	fp.open("walk.3d");
	if (!fp.is_open())
	{
		cout<<"walk.3d not Open"<<endl;
		exit(1);
	}
	string temp;
	float discard_z;
	int k=0;
	while(getline(fp,temp)){
		stringstream ss(temp);
		position.push_back(vector<POINT>());
		position[k].resize(node_count);
		for(int j=0;j<node_count;j++){
			ss>>position[k][j].x>>position[k][j].y>>discard_z;
			position[k][j].y=-position[k][j].y; //because y axis for screen coordinates is opposite

		}
		k++;
	}
	total_skeleton=k;
	fp.close();
}
void RetrievedSkeleton::compare(DrawnSkeleton* dS){
	float minval=INT_MAX;
	float sum=0;	
	float final_sum=0;
	//float* gaussian=ComputeGaussianKernel(5,1.0);
	for(int i=0;i<total_skeleton-1;i++){  //@@recheck total_skeleton-1 && node_count value
		for(int j=0;j<node_count;j++){
			float tempv=(position[i][j].x-dS->oldSkeletonNodes[j].x);
			sum+=tempv*tempv;
			float tempv2=(position[i][j].y-dS->oldSkeletonNodes[j].y);
			sum+=tempv2*tempv2;
			final_sum+=sum;
			sum=0;
		}
		if(final_sum<minval){
			minval=final_sum;
			this->frameNo=i;
		}
		final_sum=0;

	}
}
void RetrievedSkeleton::find_diff(DrawnSkeleton* dS,int F){
	vector<POINT> newP2= position[frameNo];
	vector<POINT> newP3;
	if(F==1)
	newP3 = position[frameNo+1];
	else if(F==0)
	newP3= position[frameNo-1];
	dS->diff.resize(node_count);
	for(int i=0;i<5;i++){
		dS->diff[i+1].x=(newP3[i+1].x-newP3[i].x)-(newP2[i+1].x-newP2[i].x);
		dS->diff[i+1].y=(newP3[i+1].y-newP3[i].y)-(newP2[i+1].y-newP2[i].y);
	}
	
	for(int i=6;i<10;i++){
		dS->diff[i+1].x=(newP3[i+1].x-newP3[i].x)-(newP2[i+1].x-newP2[i].x);
		dS->diff[i+1].y=(newP3[i+1].y-newP3[i].y)-(newP2[i+1].y-newP2[i].y);
	}
	
	for(int i=11;i<15;i++){
		dS->diff[i+1].x=(newP3[i+1].x-newP3[i].x)-(newP2[i+1].x-newP2[i].x);
		dS->diff[i+1].y=(newP3[i+1].y-newP3[i].y)-(newP2[i+1].y-newP2[i].y);
	}
	for(int i=16;i<20;i++){
		dS->diff[i+1].x=(newP3[i+1].x-newP3[i].x)-(newP2[i+1].x-newP2[i].x);
		dS->diff[i+1].y=(newP3[i+1].y-newP3[i].y)-(newP2[i+1].y-newP2[i].y);
	}
	for(int i=21;i<25;i++){
		dS->diff[i+1].x=(newP3[i+1].x-newP3[i].x)-(newP2[i+1].x-newP2[i].x);
		dS->diff[i+1].y=(newP3[i+1].y-newP3[i].y)-(newP2[i+1].y-newP2[i].y);
	}
}

