#include <assert.h>
#include <QtGui>
#include <queue>
#include <vector>
#include <math.h>
#include<iostream>
#include<pthread.h>
#include<QHBoxLayout>
#include "scribblearea.h"

#define PI 3.14159265358979323846
#define STEP 0.001 //check values
using namespace std;

float find_dist(POINT skeletonNodes,POINT curvePoint){
	float x_d=(skeletonNodes.x-curvePoint.x);
	float y_d=(skeletonNodes.y-curvePoint.y);
	return sqrt(x_d*x_d+y_d*y_d);
}
vector<vector<long double> > bnml;


long double binomial(int n, int k)
{
	long double* C = (long double*)calloc(k+1, sizeof(long double));
	int i, j; 
	long double res;

	C[0] = 1.0;

	for(i = 1; i <= n; i++)
	{
		for(j = min(i, k); j > 0; j--)
			C[j] = C[j] + C[j-1];
	}
	res = C[k];  // Store the result before freeing memory
	free(C);  // free dynamically allocated memory to avoid memory leak
	return res;
}
POINT bernstein(vector<POINT> ctrl,float t,int n){POINT N;N.x=N.y=0;
	for(int i=0;i<=n;i++){
		N.x+=ctrl[i].x*bnml[n][i]*pow(t,i)*pow((1-t),(n-i));
		N.y+=ctrl[i].y*bnml[n][i]*pow(t,i)*pow((1-t),(n-i));
	}
	return N;
} 
/*---------------------------------------------------------------------------------------------*/


ScribbleArea::ScribbleArea(QWidget *parent): QWidget(parent){
	setAttribute(Qt::WA_StaticContents);
	setFocusPolicy( Qt::StrongFocus );


	modified = false;
	scribbling = false;
	skeleton = false;
	erase=false;
	erase2=false;
	normal2=false;
	shadow_flag=false;
	first_frame_done=false;
	curve=-1;
	setFixedSize(600, 600);
	resizeImage(&image, QSize(600, 600));
	myPenWidth = 2;
	myPenColor = Qt::blue;
	shadowVisibility = 1;
	path_to_DB="./DatabaseFiles/";
	matchI=MatchingImage(10,path_to_DB);
	rS= RetrievedSkeleton();  
	dS= DrawnSkeleton(); 
	cV= CurvePoints();

}
void ScribbleArea::read_display(QColor color1,QColor color2){
	if(dS.skeletonNodes.size()==0)
		return;
	QPainter painter(&image);
	//draw original skeleton
	painter.setPen(QPen(color1, myPenWidth+2, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	for(int i=0;i<dS.skeletonNodes.size();i++){

		painter.drawPoint(QPointF(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y));
	}

	painter.setPen(QPen(color2, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));

	for(int i=0;i<5;i++){
		painter.drawLine(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y,dS.skeletonNodes[i+1].x+dS.base_x,dS.skeletonNodes[i+1].y+dS.base_y);
	}
	for(int i=6;i<10;i++){
		painter.drawLine(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y,dS.skeletonNodes[i+1].x+dS.base_x,dS.skeletonNodes[i+1].y+dS.base_y);
	}
	for(int i=11;i<15;i++){
		painter.drawLine(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y,dS.skeletonNodes[i+1].x+dS.base_x,dS.skeletonNodes[i+1].y+dS.base_y);}
	for(int i=16;i<20;i++){
		painter.drawLine(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y,dS.skeletonNodes[i+1].x+dS.base_x,dS.skeletonNodes[i+1].y+dS.base_y);}
	for(int i=21;i<25;i++){
		painter.drawLine(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y,dS.skeletonNodes[i+1].x+dS.base_x,dS.skeletonNodes[i+1].y+dS.base_y);}
	image.save("temp", "jpg");

	update();
}

void ScribbleArea::scale_f(DrawnSkeleton* dS,RetrievedSkeleton* rS){
	bone_scale.resize(rS->node_count);
	for(int i=0;i<5;i++){
		bone_scale[i+1]=find_dist(rS->position[1][i],rS->position[1][i+1])/find_dist(dS->skeletonNodes[i],dS->skeletonNodes[i+1]);

	}
	for(int i=6;i<10;i++){
		bone_scale[i+1]=find_dist(rS->position[1][i],rS->position[1][i+1])/find_dist(dS->skeletonNodes[i],dS->skeletonNodes[i+1]);

	}
	for(int i=11;i<15;i++){
		bone_scale[i+1]=find_dist(rS->position[1][i],rS->position[1][i+1])/find_dist(dS->skeletonNodes[i],dS->skeletonNodes[i+1]);

	}
	for(int i=16;i<20;i++){
		bone_scale[i+1]=find_dist(rS->position[1][i],rS->position[1][i+1])/find_dist(dS->skeletonNodes[i],dS->skeletonNodes[i+1]);

	}
	for(int i=21;i<25;i++){
		bone_scale[i+1]=find_dist(rS->position[1][i],rS->position[1][i+1])/find_dist(dS->skeletonNodes[i],dS->skeletonNodes[i+1]);

	}
	dS->bone_inverse_scale.resize(rS->node_count);
	for(int i=1;i<rS->node_count;i++){        //store both positive and negative scale
		if(bone_scale[i]==0)
			dS->bone_inverse_scale[i]=0;
		else
			dS->bone_inverse_scale[i]=1.0/bone_scale[i];
	}
}

void ScribbleArea::calculate_newP(vector<POINT> originalP,vector<POINT>& newP){
	for(int i=0;i<5;i++){
		newP[i+1].x=bone_scale[i+1]*(originalP[i+1].x-originalP[i].x)+newP[i].x;
		newP[i+1].y=bone_scale[i+1]*(originalP[i+1].y-originalP[i].y)+newP[i].y;
	}
	newP[6].x=newP[3].x;//change 11 to i
	newP[6].y=newP[3].y;
	for(int i=6;i<10;i++){
		newP[i+1].x=bone_scale[i+1]*(originalP[i+1].x-originalP[i].x)+newP[i].x;
		newP[i+1].y=bone_scale[i+1]*(originalP[i+1].y-originalP[i].y)+newP[i].y;
	}
	newP[11].x=newP[3].x;//change 11 to i
	newP[11].y=newP[3].y;
	for(int i=11;i<15;i++){
		newP[i+1].x=bone_scale[i+1]*(originalP[i+1].x-originalP[i].x)+newP[i].x;
		newP[i+1].y=bone_scale[i+1]*(originalP[i+1].y-originalP[i].y)+newP[i].y;
	}
	for(int i=16;i<20;i++){
		newP[i+1].x=bone_scale[i+1]*(originalP[i+1].x-originalP[i].x)+newP[i].x;
		newP[i+1].y=bone_scale[i+1]*(originalP[i+1].y-originalP[i].y)+newP[i].y;
	}
	for(int i=21;i<25;i++){
		newP[i+1].x=bone_scale[i+1]*(originalP[i+1].x-originalP[i].x)+newP[i].x;
		newP[i+1].y=bone_scale[i+1]*(originalP[i+1].y-originalP[i].y)+newP[i].y;
	}
}



void ScribbleArea::drawCurve(vector<POINT> curve_){
	POINT P,M;  //improve
	cV.curvePoints.push_back(vector<POINT>());
	cV.curvePoints[curve].clear();
	int nPoints=curve_.size();
	bnml.resize(nPoints,vector<long double>(nPoints,0.0));
	for(int i=0;i<nPoints;i++){
		bnml[nPoints-1][i]=binomial(nPoints-1,i);
	}
	float t;
	for( t = 0;t <= 1; t += STEP) {
		M=bernstein(curve_,t,curve_.size()-1);
		cV.curvePoints[curve].push_back(M);
	}

}
void ScribbleArea::drawCurveDefaultColor(){
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	for(int i=0;i<cV.final_rigPoints.size();i++){

		for(int j=0;j<cV.final_rigPoints[i].size();j++){
			for(int k=0;k<cV.final_rigPoints[i][j].first.size();k++){

				painter.drawPoint(QPointF(cV.final_rigPoints[i][j].first[k].x,cV.final_rigPoints[i][j].first[k].y));
			}
		}
	}
	image.save(QString::number(rS.frameNo)+"_anim","jpg");
	update();
}

void ScribbleArea::drawCurveDiffColor(){

	QPainter painter(&image);
	painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));

	for(int i=0;i<cV.curvePoints2.size();i++){//erase curve

		for(int j=0;j<cV.curvePoints2[i].size();j++){
			painter.drawLine(cV.curvePoints2[i][j].x,cV.curvePoints2[i][j].y,cV.curvePoints2[i][j+1].x,cV.curvePoints2[i][j+1].y);
		}
	}
	cV.curvePoints2.clear();
	cV.curvePoints.clear();
	curve=-1;
	for(int i=0;i<cV.final_rigPoints.size();i++){


		switch(i){
			case 0:
				painter.setPen(QPen(QColor(255,0,255), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 1:
				painter.setPen(QPen(QColor(255,255,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;

			case 2:
				painter.setPen(QPen(QColor(255,0,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 3:
				painter.setPen(QPen(QColor(0,0,255), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 4:
				painter.setPen(QPen(QColor(0,255,255), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 6:
				painter.setPen(QPen(QColor(128,128,128), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 7:
				painter.setPen(QPen(QColor(128,0,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 8:
				painter.setPen(QPen(QColor(0,128,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 9:
				painter.setPen(QPen(QColor(0,0,128), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 11:
				painter.setPen(QPen(QColor(0,128,128), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 12:
				painter.setPen(QPen(QColor(128,0,128), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 13:
				painter.setPen(QPen(QColor(0,250,154), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 14:
				painter.setPen(QPen(QColor(255,69,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 16:
				painter.setPen(QPen(QColor(0,255,255), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 17:
				painter.setPen(QPen(QColor(0,0,255), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 18:
				painter.setPen(QPen(QColor(255,0,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 19:
				painter.setPen(QPen(QColor(255,255,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;

			case 21:
				painter.setPen(QPen(QColor(0,0,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 22:
				painter.setPen(QPen(QColor(128,128,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 23:
				painter.setPen(QPen(QColor(0,128,128), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
			case 24:
				painter.setPen(QPen(QColor(0,0,128), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;

			default:

				painter.setPen(QPen(QColor(0,0,0), myPenWidth, Qt::SolidLine, Qt::RoundCap,
							Qt::RoundJoin));
				break;
		}

		for(int j=0;j<cV.final_rigPoints[i].size();j++){
			for(int k=0;k<cV.final_rigPoints[i][j].first.size();k++){

				painter.drawPoint(QPointF(cV.final_rigPoints[i][j].first[k].x,cV.final_rigPoints[i][j].first[k].y));
			}
		}
	}

	update();
}
void ScribbleArea::eraseSketch(){
	QPainter painter(&image);
	painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));

	for(int i=0;i<cV.final_rigPoints.size();i++){

		for(int j=0;j<cV.final_rigPoints[i].size();j++){
			for(int k=0;k<cV.final_rigPoints[i][j].first.size();k++){

				painter.drawPoint(QPointF(cV.final_rigPoints[i][j].first[k].x,cV.final_rigPoints[i][j].first[k].y));
			}
		}
	}
	update();
}

void ScribbleArea:: modify_rig(){
	POINT curve=cV.min_dist_curvePoints(reassociate[0]);
	int skeleton=dS.min_dist_skeletonNodes(reassociate[1]);
	cV.manualRigging(cV.final_rigPoints[curve.x][curve.y].first,skeleton);
	cV.divideCurve();
	cV.final_rigPoints[curve.x].erase(cV.final_rigPoints[curve.x].begin()+curve.y);
	/*if(skeleton.y==0)
	  cV.final_rigPoints[skeleton.x].push_back(make_pair(cV.final_rigPoints[curve.x][curve.y].first,1));

	  else
	  cV.final_rigPoints[skeleton.x].push_back(make_pair(cV.final_rigPoints[curve.x][curve.y].first,0));


	  cV.final_rigPoints[curve.x].erase(cV.final_rigPoints[curve.x].begin()+curve.y);*/
}

void ScribbleArea::after_erase(int id){
	QPainter painter(&image);
	painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	for(int j=0;j<cV.curvePoints2[id].size()-1;j++){
		painter.drawLine(cV.curvePoints2[id][j].x,cV.curvePoints2[id][j].y,cV.curvePoints2[id][j+1].x,cV.curvePoints2[id][j+1].y);
	}	
	cV.curvePoints2.erase(cV.curvePoints2.begin()+id);
	update();

}


void ScribbleArea::after_erase2(POINT id){
	QPainter painter(&image);
	painter.setPen(QPen(Qt::white, myPenWidth+1, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	for(int i=0;i<cV.final_rigPoints[id.x][id.y].first.size()-1;i++){
		painter.drawLine(cV.final_rigPoints[id.x][id.y].first[i].x,cV.final_rigPoints[id.x][id.y].first[i].y,cV.final_rigPoints[id.x][id.y].first[i+1].x,cV.final_rigPoints[id.x][id.y].first[i+1].y);
	}
	cV.final_rigPoints[id.x].erase(cV.final_rigPoints[id.x].begin()+id.y);//
	update();
}


void ScribbleArea::drawNextFrameCurve(){
	//QPainter painter(&image);
	//painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
	//Qt::RoundJoin));
	util::math::vec3 finalCurvePt;
	util::math::mat33 tmp;
	for(int i=0;i<cV.final_rigPoints.size();i++){
		for(int j=0;j<cV.final_rigPoints[i].size();j++){
			int k=0;
			for(int k=0;k<cV.final_rigPoints[i][j].first.size();k++){
				if(cV.final_rigPoints[i][j].second==1){
					if(i==6 || i==11)
						tmp= (0.5*dS.Transform[i] + 0.5*dS.Transform[3]);
					else if(i==16 || i==21)
						tmp= (0.5*dS.Transform[i] + 0.5*dS.Transform[0]);
					else
						tmp= (0.5*dS.Transform[i] + 0.5*dS.Transform[i-1]);

					finalCurvePt=tmp*(util::math::vec3(cV.final_rigPoints[i][j].first[k].x-dS.base_x,cV.final_rigPoints[i][j].first[k].y-dS.base_y,1));

				}
				else{
					finalCurvePt=dS.Transform[i]*(util::math::vec3(cV.final_rigPoints[i][j].first[k].x-dS.base_x,cV.final_rigPoints[i][j].first[k].y-dS.base_y,1));
				}
				cV.final_rigPoints[i][j].first[k].x=finalCurvePt[0]+dS.base_x;
				cV.final_rigPoints[i][j].first[k].y=finalCurvePt[1]+dS.base_y;
				//painter.drawPoint(QPointF(finalCurvePt[0]+dS.base_x,finalCurvePt[1]+dS.base_y));	
			}
		}
	}


	image.save(QString::number(rS.frameNo)+"_anim","jpg");
}
void ScribbleArea::redrawSkeleton(){
	QPainter painter(&image);
	painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	if(dS.update_flag==0){
		for(int i=0;i<dS.skeletonNodes.size();i++)
			painter.drawPoint(QPointF(dS.skeletonNodes[i].x,dS.skeletonNodes[i].y));	
	}
	else{
		for(int i=0;i<dS.skeletonNodes.size();i++)
			painter.drawPoint(QPointF(dS.skeletonNodes[i].x+dS.base_x,dS.skeletonNodes[i].y+dS.base_y));	
	}
	dS.skeletonNodes.clear();

	update();
}
void ScribbleArea::keyPressEvent(QKeyEvent* event){

	switch ( event->key() ) {
		case Qt::Key_Q:
			rig=false;
			erase=false;
			erase2=false;
			skeleton=true;
			normal2=false;
			break;

		case Qt::Key_P:
			dS.update();
			rS.node_count=dS.skeletonNodes.size();
			rS.read();
			scale_f(&dS,&rS);
			calculate_newP(dS.skeletonNodes,dS.oldSkeletonNodes);
			rS.compare(&dS);
			dS.update_Binding_Matrix();
			read_display(Qt::red,Qt::green);
			break;
		case Qt::Key_R:
			cV.assign_skeleton_midPt(dS);
			cV.rigging();
			cV.divideCurve();
			//drawCurve();
			drawCurveDiffColor();
			first_frame_done=true;
			cV.curvePoints.clear();
			cV.curvePoints2.clear();
			curve=-1;
			break;
		case Qt::Key_I:
			erase=false;
			erase2=false;
			rig=true;
			skeleton=false;
			normal2=false;
			reassociate.clear();
			break;
		case Qt::Key_J:
			modify_rig();
			drawCurveDiffColor();
			break;
		case Qt::Key_E:
			skeleton=false;
			rig=false;
			erase=true;
			erase2=false;
			normal2=false;
			break;
		case Qt::Key_Z:
			skeleton=false;
			rig=false;
			erase=false;
			erase2=true;
			normal2=false;
			break;
		case Qt::Key_N:
			rig=false;
			erase=false;
			erase2=false;
			skeleton=false;
			if(first_frame_done)
				normal2=true;
			else
				normal2=false;

			break;

		default:
			event->ignore();
			break;
	}
}


void ScribbleArea::setPenColor(const QColor &newColor)
{
	myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
	myPenWidth = newWidth;
}

void ScribbleArea::setVisibility(double newVisibility)
{
	shadowVisibility = newVisibility;
	update();
}

void ScribbleArea::clearImage()
{
	image.fill(qRgb(255, 255, 255));
	modified = true;

	update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{

	if (event->button() == Qt::LeftButton && !skeleton && !rig && !erase && !erase2 ) {
		lastPoint = event->pos();
		POINT *tmp=new POINT;
		tmp->x=event->pos().x();
		tmp->y=event->pos().y();
		cV.curvePoints2.push_back(vector<POINT>());
		curve++;
		cout<<curve<<endl;
		cV.curvePoints2[curve].push_back(*tmp);
		scribbling = true;
		delete tmp;
	}

	else if(event->button() == Qt::LeftButton && skeleton ){
		POINT *tmp=new POINT;
		tmp->x=event->pos().x();
		tmp->y=event->pos().y();
		dS.skeletonNodes.push_back(*tmp);
		drawPointTo(event->pos());
		delete tmp;
	}
	else if(event->button() == Qt::LeftButton && rig ){
		POINT *tmp=new POINT;
		tmp->x=event->pos().x();
		tmp->y=event->pos().y();
		if(reassociate.size()>=2)
			reassociate.clear();
		reassociate.push_back(*tmp);
		delete tmp;
	}
	else if(event->button() == Qt::LeftButton && erase ){
		POINT *tmp=new POINT;
		tmp->x=event->pos().x();
		tmp->y=event->pos().y();

		if(curve>-1){
			int id=cV.erase_curve(*tmp);
			curve--;
			cout<<curve<<endl;
			after_erase(id);}
		delete tmp;

	}
	else if(event->button() == Qt::LeftButton && erase2 ){
		POINT *tmp=new POINT;
		tmp->x=event->pos().x();
		tmp->y=event->pos().y();
		POINT id=cV.erase_curve2(*tmp);
		delete tmp;
		after_erase2(id);
	}


}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && scribbling){
		drawLineTo(event->pos());
		POINT *tmp=new POINT;
		tmp->x=event->pos().x();
		tmp->y=event->pos().y();
		cV.curvePoints2[curve].push_back(*tmp);
		delete tmp;
	}
}

void ScribbleArea::save_updateShadow(){

	QImage visibleImage = image.scaled(300,300,Qt::KeepAspectRatio);
	//resizeImage(&visibleImage, size());
	visibleImage.save("temp", "jpg");
	testImg=imread("temp");
	//imshow("a",testImg);
	//waitKey(0);
	cvtColor(testImg,testImg,CV_BGR2GRAY);
	updateShadow();
}
void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && scribbling &&!normal2) {
		drawLineTo(event->pos());
		scribbling = false;
		lastCursor = event->pos();
		drawCurve(cV.curvePoints2[curve]);
	}	
	else if (event->button() == Qt::LeftButton && scribbling && normal2) {
		drawLineTo(event->pos());
		scribbling = false;
		lastCursor = event->pos();
		drawCurve(cV.curvePoints2[curve]);

		cV.riggingPerCurve(cV.curvePoints[curve]);
		cV.divideCurve();
		drawCurveDiffColor();
	}
}


void ScribbleArea::updateShadow(){
	matchI.castVotes(testImg);
	matchI.findMaxima();
	QImage output;
	output.load("a.jpg");
	shadow = output.scaled(600,600,Qt::KeepAspectRatio);
	update();
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
	if(shadow_flag==0)
		shadow=QImage();
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	QImage output(image);
	for(int i=0;i<shadow.width();++i)
		for(int j=0;j<shadow.height();++j){
			double dists = (i-lastCursor.x())*(i-lastCursor.x())+(j-lastCursor.y())*(j-lastCursor.y());
			double coeff = shadowVisibility;
			int r = qRed(image.pixel(i,j))   - qRed(shadow.pixel(i,j))*coeff;
			int g = qGreen(image.pixel(i,j)) - qGreen(shadow.pixel(i,j))*coeff;
			int b = qBlue(image.pixel(i,j))  - qBlue(shadow.pixel(i,j))*coeff;
			if(r<0) r = 0;
			if(g<0) g = 0;
			if(b<0) b = 0;
			output.setPixel(i, j, qRgb(r,g,b));
		}
	//painter.drawImage(dirtyRect, output, dirtyRect);
	painter.drawImage(0, 0, output);
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
	if (width() > image.width() || height() > image.height()) {
		int newWidth = qMax(width() + 128, image.width());
		int newHeight = qMax(height() + 128, image.height());
		resizeImage(&image, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	painter.drawLine(lastPoint, endPoint);
	modified = true;

	//int rad = (myPenWidth / 2) + 2;
	update();
	//	update(QRect(lastPoint, endPoint).normalized()
	//			.adjusted(-rad, -rad, +rad, +rad));
	lastPoint = endPoint;
}
void ScribbleArea::drawPointTo(const QPoint &endPoint)
{
	QPainter painter(&image);
	painter.setPen(QPen(Qt::red, myPenWidth, Qt::SolidLine, Qt::RoundCap,
				Qt::RoundJoin));
	painter.drawPoint(endPoint);
	modified = true;

	//int rad = (myPenWidth / 2) + 2;
	update();
	//	update(QRect(lastPoint, endPoint).normalized()
	//			.adjusted(-rad, -rad, +rad, +rad));
}
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
	if (image->size() == newSize)
		return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}



