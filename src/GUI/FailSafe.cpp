#include "FailSafe.h"
void FailSafe::write(ScribbleArea* S,string path){
	RetrievedSkeleton rS= S->rS;
	ofstream ofs (path+"FS");
	ofs<<S->dS.node_count<<" "<<S->dS.base_x<<" "<<S->dS.base_y<<" ";
	ofs<<rS.position.size()<<endl;
	for(int i=0;i<rS.position.size();i++){
		ofs<<rS.position[i].size()<<" ";
		for(int j=0;j<rS.position[i].size();j++){
			ofs<<rS.position[i][j].x<<" "<<rS.position[i][j].y<<" ";
		}
		ofs<<endl;
	}
	CurvePoints cV=S->cV;
	ofs<<cV.skeleton_midPt.size()<<endl;
	for(int i=0;i<cV.skeleton_midPt.size();i++){
		ofs<<cV.skeleton_midPt[i].size()<<" ";
		for(int j=0;j<cV.skeleton_midPt[i].size();j++){
			ofs<<cV.skeleton_midPt[i][j].x<<" "<<cV.skeleton_midPt[i][j].y<<" ";
		}
		ofs<<endl;
	}
	for(int i=0;i<rS.node_count;i++){
		ofs<<S->bone_scale[i]<<" "<<S->dS.bone_inverse_scale[i]<<endl;
	}
}	
void FailSafe::read(ScribbleArea* S,string path){

	ifstream ifs(path+"FS");
	ifs>>S->dS.node_count>>S->dS.base_x>>S->dS.base_y;
	S->rS.node_count=S->dS.node_count;
	int size_val;
	ifs>>size_val;
	S->rS.position.resize(size_val);
	int i=0;
	while(i<S->rS.position.size() && !ifs.eof()){
		int size;
		ifs>>size;
		S->rS.position[i].resize(size);
		for(int j=0;j<S->rS.position[i].size();j++){
			ifs>>S->rS.position[i][j].x>>S->rS.position[i][j].y;
		}
		i++;
	}
	i=0;
	ifs>>size_val;
	S->cV.skeleton_midPt.resize(size_val);
	while(i<S->cV.skeleton_midPt.size() && !ifs.eof()){
		int size;
		ifs>>size;
		S->cV.skeleton_midPt[i].resize(size);
		for(int j=0;j<S->cV.skeleton_midPt[i].size();j++){
			ifs>>S->cV.skeleton_midPt[i][j].x>>S->cV.skeleton_midPt[i][j].y;
		}
		i++;
	}
	i=0;
	S->bone_scale.resize(S->dS.node_count);
	S->dS.bone_inverse_scale.resize(S->dS.node_count);
	while(i<S->dS.node_count && !ifs.eof()){
		ifs>>S->bone_scale[i]>>S->dS.bone_inverse_scale[i];
		i++;
	}
	
}	
