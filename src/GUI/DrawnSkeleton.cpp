#include "DrawnSkeleton.h"
#include<limits.h>
#include<math.h>
#include<iostream>
using namespace std;
DrawnSkeleton::DrawnSkeleton(){
	base_x=0;
	base_y=0;
}
float DrawnSkeleton::find_dist(POINT skeletonNodes,POINT curvePoint){
	float x_d=(skeletonNodes.x-curvePoint.x);
	float y_d=(skeletonNodes.y-curvePoint.y);
	return sqrt(x_d*x_d+y_d*y_d);
}
void DrawnSkeleton::calculate_newP2(){
	//cout<<" prev "<<skeletonNodes[4].x<<" "<<skeletonNodes[4].y<<endl;	
for(int i=0;i<node_count;i++){
oldSkeletonNodes[i].x=skeletonNodes[i].x;
oldSkeletonNodes[i].y=skeletonNodes[i].y;
}
	for(int i=0;i<5;i++){
		skeletonNodes[i+1].x=oldSkeletonNodes[i+1].x-oldSkeletonNodes[i].x+bone_inverse_scale[i+1]*diff[i+1].x+skeletonNodes[i].x;
		skeletonNodes[i+1].y=oldSkeletonNodes[i+1].y-oldSkeletonNodes[i].y+bone_inverse_scale[i+1]*diff[i+1].y+skeletonNodes[i].y;
	}
	//cout<<" now "<<skeletonNodes[4].x<<" "<<skeletonNodes[4].y<<endl;
	skeletonNodes[6].x=skeletonNodes[3].x;//change 6 to i
	skeletonNodes[6].y=skeletonNodes[3].y;
	for(int i=6;i<10;i++){
		skeletonNodes[i+1].x=oldSkeletonNodes[i+1].x-oldSkeletonNodes[i].x+bone_inverse_scale[i+1]*diff[i+1].x+skeletonNodes[i].x;
		skeletonNodes[i+1].y=oldSkeletonNodes[i+1].y-oldSkeletonNodes[i].y+bone_inverse_scale[i+1]*diff[i+1].y+skeletonNodes[i].y;
	}
	skeletonNodes[11].x=skeletonNodes[3].x;//change 6 to i
	skeletonNodes[11].y=skeletonNodes[3].y;
	for(int i=11;i<15;i++){
		skeletonNodes[i+1].x=oldSkeletonNodes[i+1].x-oldSkeletonNodes[i].x+bone_inverse_scale[i+1]*diff[i+1].x+skeletonNodes[i].x;
		skeletonNodes[i+1].y=oldSkeletonNodes[i+1].y-oldSkeletonNodes[i].y+bone_inverse_scale[i+1]*diff[i+1].y+skeletonNodes[i].y;
	}
	for(int i=16;i<20;i++){
		skeletonNodes[i+1].x=oldSkeletonNodes[i+1].x-oldSkeletonNodes[i].x+bone_inverse_scale[i+1]*diff[i+1].x+skeletonNodes[i].x;
		skeletonNodes[i+1].y=oldSkeletonNodes[i+1].y-oldSkeletonNodes[i].y+bone_inverse_scale[i+1]*diff[i+1].y+skeletonNodes[i].y;
	}
	for(int i=21;i<25;i++){
		skeletonNodes[i+1].x=oldSkeletonNodes[i+1].x-oldSkeletonNodes[i].x+bone_inverse_scale[i+1]*diff[i+1].x+skeletonNodes[i].x;
		skeletonNodes[i+1].y=oldSkeletonNodes[i+1].y-oldSkeletonNodes[i].y+bone_inverse_scale[i+1]*diff[i+1].y+skeletonNodes[i].y;
	}

}
int DrawnSkeleton::min_dist_skeletonNodes(POINT select){
	int min_val=INT_MAX;
	int min_ind;
	for(int i=0;i<skeletonNodes.size();i++){
		POINT tmp;
		tmp.x=skeletonNodes[i].x+base_x;
		tmp.y=skeletonNodes[i].y+base_y;
		float dist=find_dist(select,tmp);
		if(dist<min_val){
			min_ind=i;
			min_val=dist;
		}
	}
	return min_ind;
}
void DrawnSkeleton::update_Transform_Matrix(){//can use update_Binding_Matrix()
	float cos_t,sin_t,D;
	util::math::mat33 tmp_B;
	util::math::mat33 tmp_I;

	Transform.resize(node_count);
	int i=0;
	for(i=0;i<5;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		tmp_B=util::math::mat33(cos_t,sin_t,skeletonNodes[i].x,
				-sin_t,cos_t,skeletonNodes[i].y,	
				0,0,1);
		Transform[i]=tmp_B*Binding[i];
	}

	for(i=6;i<10;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		tmp_B=(util::math::mat33(cos_t,sin_t,skeletonNodes[i].x,
					-sin_t,cos_t,skeletonNodes[i].y,	
					0,0,1));

		Transform[i]=tmp_B*Binding[i];
	}

	for(int i=11;i<15;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		tmp_B=(util::math::mat33(cos_t,sin_t,skeletonNodes[i].x,
					-sin_t,cos_t,skeletonNodes[i].y,	
					0,0,1));
		Transform[i]=tmp_B*Binding[i];
	}


	for(int i=16;i<20;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		tmp_B=(util::math::mat33(cos_t,sin_t,skeletonNodes[i].x,
					-sin_t,cos_t,skeletonNodes[i].y,	
					0,0,1));
		Transform[i]=tmp_B*Binding[i];

	}

	for(int i=21;i<25;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		tmp_B=(util::math::mat33(cos_t,sin_t,skeletonNodes[i].x,
					-sin_t,cos_t,skeletonNodes[i].y,	
					0,0,1));
		Transform[i]=tmp_B*Binding[i];
	}



}
void DrawnSkeleton::update_Binding_Matrix(){

	float cos_t,sin_t,D;
	Binding.resize(node_count);
	int i=0;
	for(i=0;i<5;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		Binding[i]=util::math::mat33(cos_t,-sin_t,0,
				sin_t,cos_t,0,	
				0,0,1)*util::math::mat33(1,0,-skeletonNodes[i].x,0,1,-skeletonNodes[i].y,0,0,1);

	}

	for(i=6;i<10;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		Binding[i]=util::math::mat33(cos_t,-sin_t,0,
				sin_t,cos_t,0,	
				0,0,1)*util::math::mat33(1,0,-skeletonNodes[i].x,0,1,-skeletonNodes[i].y,0,0,1);

	}

	for(int i=11;i<15;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		Binding[i]=util::math::mat33(cos_t,-sin_t,0,
				sin_t,cos_t,0,	
				0,0,1)*util::math::mat33(1,0,-skeletonNodes[i].x,0,1,-skeletonNodes[i].y,0,0,1);

	}

	for(int i=16;i<20;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		Binding[i]=util::math::mat33(cos_t,-sin_t,0,
				sin_t,cos_t,0,	
				0,0,1)*util::math::mat33(1,0,-skeletonNodes[i].x,0,1,-skeletonNodes[i].y,0,0,1);
	}

	for(int i=21;i<25;i++){
		POINT bl=skeletonNodes[i+1]-skeletonNodes[i];
		D= sqrt(bl.x*bl.x+bl.y*bl.y);
		cos_t=bl.y/D;
		sin_t=bl.x/D;
		Binding[i]=util::math::mat33(cos_t,-sin_t,0,
				sin_t,cos_t,0,	
				0,0,1)*util::math::mat33(1,0,-skeletonNodes[i].x,0,1,-skeletonNodes[i].y,0,0,1);

	}


}
void DrawnSkeleton::update(){
	node_count=skeletonNodes.size();
	update_flag=1;
	oldSkeletonNodes.resize(node_count);

	base_x=skeletonNodes[0].x;
	base_y=skeletonNodes[0].y;
	for(int i=1;i<skeletonNodes.size();i++){
		skeletonNodes[i].x=skeletonNodes[i].x-skeletonNodes[0].x;
		skeletonNodes[i].y=skeletonNodes[i].y-skeletonNodes[0].y;}
	skeletonNodes[0].x=0;
	skeletonNodes[0].y=0;
	
}
