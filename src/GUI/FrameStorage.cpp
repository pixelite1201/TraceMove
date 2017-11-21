#include "FrameStorage.h"
void FrameStorage::write(ScribbleArea* S,string path,int frame_no){
	stringstream ss;
	ss<<frame_no;
	ofstream ofs (path+"DS"+ss.str());//check whether c_str() required
	DrawnSkeleton dS= S->dS;

	for(int i=0;i<dS.skeletonNodes.size();i++){
		ofs<<dS.skeletonNodes[i].x<<" "<<dS.skeletonNodes[i].y<<endl;
	}
	//check whether dS.diff needed,dS.oldSkeletonNodes etc.
	/*	for(int i=0;i<dS.skeletonNodes.size();i++){//maybe not needed
		for(int j=0;j<3;j++){
		for(int k=0;k<3;k++){
		ofs<<dS.Transform[i][j][k]<<" ";
		}
		}
		ofs<<endl;
		}*/

	for(int i=0;i<dS.skeletonNodes.size();i++){
		ofs<<dS.oldSkeletonNodes[i].x<<" "<<dS.oldSkeletonNodes[i].y<<endl;
	}
	ofs.close();

	ofstream ofs2(path+"CV"+ss.str());

	CurvePoints cV= S->cV;
	

	ofs2<<cV.final_rigPoints.size()<<endl;
	for(int i=0;i<cV.final_rigPoints.size();i++){
		ofs2<<cV.final_rigPoints[i].size()<<" ";
		for(int j=0;j<cV.final_rigPoints[i].size();j++){
			ofs2<<cV.final_rigPoints[i][j].first.size()<<" ";
			for(int k=0;k<cV.final_rigPoints[i][j].first.size();k++){
				ofs2<<cV.final_rigPoints[i][j].first[k].x<<" "<<cV.final_rigPoints[i][j].first[k].y<<" ";
			}
			ofs2<<cV.final_rigPoints[i][j].second<<endl;
		}
	}
	ofs2<<S->rS.frameNo<<endl;
	ofs2.close();
}


void FrameStorage::read(ScribbleArea* S,string path,int frame_no){
	stringstream ss;
	ss<<frame_no;
	ifstream ifs (path+"DS"+ss.str());

	S->dS.skeletonNodes.clear();
	S->dS.skeletonNodes.resize(S->dS.node_count);

	int i=0;
	while(i<S->dS.node_count && !ifs.eof() ){

		ifs>>S->dS.skeletonNodes[i].x>>S->dS.skeletonNodes[i].y;
		i++;
	}
	i=0;
	
	S->dS.oldSkeletonNodes.clear();
	S->dS.oldSkeletonNodes.resize(S->dS.node_count);
	while(i<S->dS.node_count && !ifs.eof() ){
		ifs>>S->dS.oldSkeletonNodes[i].x>>S->dS.oldSkeletonNodes[i].y;
		i++;
	}
	ifs.close();
	ifstream ifs2(path+"CV"+ss.str());
	ss.str("");


	for(int i=0;i<S->cV.final_rigPoints.size();i++){
		S->cV.final_rigPoints[i].clear();
	}
	S->cV.final_rigPoints.clear();

	int rigPoints_size;
	ifs2>>rigPoints_size;
	S->cV.final_rigPoints.resize(rigPoints_size);
	i=0;
	while(i<rigPoints_size && !ifs2.eof()){
		int size;
		ifs2>>size;
		S->cV.final_rigPoints[i].resize(size);
		for(int j=0;j<size;j++){
			int size2;
			ifs2>>size2;
			S->cV.final_rigPoints[i][j].first.resize(size2);
			for(int k=0;k<size2;k++){
				ifs2>>S->cV.final_rigPoints[i][j].first[k].x>>S->cV.final_rigPoints[i][j].first[k].y;
			}
			ifs2>>S->cV.final_rigPoints[i][j].second;
		}
		i++;
	}
	
	ifs2>>S->rS.frameNo;	
	ifs2.close();
}
