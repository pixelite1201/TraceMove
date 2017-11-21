#include "CurvePoints.h"

#define THRESHOLD 12
CurvePoints::CurvePoints(){
}

float CurvePoints:: find_dist(POINT skeletonNodes,POINT curvePoint){
	float x_d=(skeletonNodes.x-curvePoint.x);
	float y_d=(skeletonNodes.y-curvePoint.y);
	return sqrt(x_d*x_d+y_d*y_d);
}

void CurvePoints::divideCurve(){
	float threshold=THRESHOLD;
	for(int i=0;i<rigPoints.size();i++){
		int k=final_rigPoints[i].size();;

		if(rigPoints[i].size()>0){
			final_rigPoints[i].push_back(pair<vector<POINT>,bool>());
			final_rigPoints[i][k].second=0;
			final_rigPoints[i][k].first.push_back(rigPoints[i][0]);}
		for(int j=1;j<rigPoints[i].size();j++){
			if(find_dist(rigPoints[i][j-1],rigPoints[i][j])<=threshold){

				final_rigPoints[i][k].first.push_back(rigPoints[i][j]);}
			else{
				k++;
				final_rigPoints[i].push_back(pair<vector<POINT>,bool>());
				final_rigPoints[i][k].second=0;
				final_rigPoints[i][k].first.push_back(rigPoints[i][j]);
			}
		}
	}
	//further divide for the dual weights node
	for(int i=0;i<rigPoints_dualWt.size();i++){
		int k=final_rigPoints[i].size();
		if(rigPoints_dualWt[i].size()>0){
			final_rigPoints[i].push_back(pair<vector<POINT>,bool>());
			final_rigPoints[i][k].second=1;
			final_rigPoints[i][k].first.push_back(rigPoints_dualWt[i][0]);
		}
		for(int j=1;j<rigPoints_dualWt[i].size();j++){
			if(find_dist(rigPoints_dualWt[i][j-1],rigPoints_dualWt[i][j])<=threshold)
				final_rigPoints[i][k].first.push_back(rigPoints_dualWt[i][j]);
			else{
				k++;
				final_rigPoints[i].push_back(pair<vector<POINT>,bool>());
				final_rigPoints[i][k].second=0;
				final_rigPoints[i][k].first.push_back(rigPoints_dualWt[i][j]);
			}

		}
	}
	for(int i=0;i<rigPoints.size();i++){
		rigPoints[i].clear();	
		rigPoints_dualWt[i].clear();
	}

}


POINT CurvePoints::min_dist_curvePoints(POINT select){
	POINT min_ind;
	float min_val=INT_MAX;
	for(int i=0;i<final_rigPoints.size();i++){
		for(int j=0;j<final_rigPoints[i].size();j++){
			for(int k=0;k<final_rigPoints[i][j].first.size();k++){
				float dist=find_dist(select,final_rigPoints[i][j].first[k]);
				if(dist<min_val){
					min_ind.x=i;
					min_ind.y=j;
					min_val=dist;
				}
			}
		}
	}	
	return min_ind;
}
int CurvePoints::erase_curve(POINT tmp){
	float min_val=INT_MAX;
	int min_ind;
	for(int i=0;i<curvePoints.size();i++){
		for(int j=0;j<curvePoints[i].size();j++){
			float dist = find_dist(tmp,curvePoints[i][j]);
			if(dist<min_val){
				min_ind=i;
				min_val=dist;
			}
		}
	}
	curvePoints.erase(curvePoints.begin()+min_ind);
	return min_ind;
}

POINT CurvePoints::erase_curve2(POINT tmp){
	float min_val=INT_MAX;
	POINT ret;
	int min_ind1;
	int min_ind2;
	int min_ind3;
	for(int i=0;i<final_rigPoints.size();i++){
		for(int j=0;j<final_rigPoints[i].size();j++){
			for(int k=0;k<final_rigPoints[i][j].first.size();k++){
				float dist = find_dist(tmp,final_rigPoints[i][j].first[k]);
				if(dist<min_val){
					min_ind1=i;
					min_ind2=j;
					min_val=dist;
				}
			}
		}

	}
	ret.x=min_ind1;
	ret.y=min_ind2;

	return ret;

}
void CurvePoints::midPt_helper(int a,int b,DrawnSkeleton& dS){
	POINT add_dis;
	POINT inf;
	inf.x=INT_MAX;
	inf.y=INT_MAX;
	int i;
	for(i=a;i<b;i++){

		skeleton_midPt[i].resize(4);
		add_dis.x=(dS.skeletonNodes[i+1].x-dS.skeletonNodes[i].x)/4;//generalize 4
		add_dis.y=(dS.skeletonNodes[i+1].y-dS.skeletonNodes[i].y)/4;
		skeleton_midPt[i][0]=dS.skeletonNodes[i];

		for(int j=1;j<4;j++){
			skeleton_midPt[i][j]=skeleton_midPt[i][j-1]+add_dis;

		}
	}
	skeleton_midPt[i].push_back(inf);
}
void CurvePoints::assign_skeleton_midPt(DrawnSkeleton dS){
	rigPoints.resize(dS.skeletonNodes.size());
	rigPoints_dualWt.resize(dS.skeletonNodes.size());
	final_rigPoints.resize(dS.skeletonNodes.size());
	for(int i=0;i<26;i++){
		dS.skeletonNodes[i].x=dS.skeletonNodes[i].x+dS.base_x;
		dS.skeletonNodes[i].y=dS.skeletonNodes[i].y+dS.base_y;
	}
	skeleton_midPt.resize(dS.node_count);
	midPt_helper(0,5,dS);
	midPt_helper(6,10,dS);
	midPt_helper(11,15,dS);
	midPt_helper(16,20,dS);
	midPt_helper(21,25,dS);	
}

void CurvePoints::riggingPerCurve(vector<POINT> curvePoint){
	int min_ind=INT_MAX;
	int min_ind2=INT_MAX;
	float min_val=INT_MAX;
	for(int j=0;j<curvePoint.size();j++){
		for(int k=0;k<skeleton_midPt.size();k++){
			for(int l=0;l<skeleton_midPt[k].size();l++){	
				float dist=find_dist(skeleton_midPt[k][l],curvePoint[j]);
				if(dist<min_val){
					min_ind=k;
					min_ind2=l;
					min_val=dist;
				}
			}
		}		
		if(min_ind2==0 && min_ind!=0){
			rigPoints_dualWt[min_ind].push_back(curvePoint[j]);
		}
		else{
			rigPoints[min_ind].push_back(curvePoint[j]);}
			min_ind=INT_MAX;
			min_ind2=INT_MAX;
			min_val=INT_MAX;
	}	

}
void CurvePoints::riggingPerCurve(vector<POINT> curvePoint,vector<int> P){
int min_ind=INT_MAX;
	int min_ind2=INT_MAX;
	float min_val=INT_MAX;
	for(int j=0;j<curvePoint.size();j++){
		for(int k=0;k<P.size();k++){
			
			for(int l=0;l<skeleton_midPt[P[k]].size();l++){
				cout<<P[k]<<" "<<l<<endl;
				float dist=find_dist(skeleton_midPt[P[k]][l],curvePoint[j]);
				if(dist<min_val){
					min_ind=P[k];
					min_ind2=l;
					min_val=dist;
				}
			}
		}
		if(min_ind2==0 && min_ind!=0){
			rigPoints_dualWt[min_ind].push_back(curvePoint[j]);
		}
		else{
			rigPoints[min_ind].push_back(curvePoint[j]);}
			min_ind=INT_MAX;
			min_ind2=INT_MAX;
			min_val=INT_MAX;
	}	
	

}
void CurvePoints::manualRigging(vector<POINT> curvePoint,int skeleton){
vector<int> P;
switch(skeleton){
	case 0:
		P.push_back(0);
		P.push_back(1);
		riggingPerCurve(curvePoint,P);
		break;
	case 6:
	case 11:
		P.push_back(3);
		P.push_back(skeleton);
		P.push_back(skeleton+1);
		riggingPerCurve(curvePoint,P);
		break;
	case 16:
	case 21:
		P.push_back(0);
		P.push_back(skeleton);
		P.push_back(skeleton+1);
		riggingPerCurve(curvePoint,P);
		break;
	case 5:
	case 10:
	case 15:
	case 20:
	case 25:
		P.push_back(skeleton-1);
		riggingPerCurve(curvePoint,P);
		break;
	default:
		P.push_back(skeleton-1);	
		P.push_back(skeleton);
		P.push_back(skeleton+1);
		riggingPerCurve(curvePoint,P);
		break;
	}

}
void CurvePoints::rigging(){
	for(int i=0;i<curvePoints.size();i++){
		riggingPerCurve(curvePoints[i]);
	}
	
}

