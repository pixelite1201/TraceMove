#include "OrientedImage.h"

OrientedImage::OrientedImage(){
}
OrientedImage::OrientedImage(Mat& img1):img(img1){

	direction.resize(8);//make it general
	orientation = Mat::zeros(img.rows,img.cols,CV_64F);
	mag = Mat::zeros(img.rows,img.cols,CV_64F);
	for(int i=0;i<direction.size();i++)
		direction[i]=Mat::zeros(img.rows,img.cols,CV_64F);


}
void OrientedImage::calculateOrient(){
	
	Steerable steer=Steerable(img);	          //why on defining it in constructor and methods here, it gave different answers
	steer.applyFilter();   
	steer.calculate(mag,orientation,0);
	for(int i=0;i<img.cols;i++){
		for(int j=0;j<img.rows;j++){
			double val;
			val=(orientation.at<double>(i,j))/22.5;        //map to 0-8

			int valb=(int)val;
			//cout<<i<<" "<<j<<" "<<val<<" "<<valb<<" "<<orientation.at<double>(i,j)<<endl;
			if(valb<0)
			break;
			double diff=val-valb;
			direction[valb%8].at<double>(i,j)= img.at<double>(i,j)*(1-diff);
			direction[(valb+1)%8].at<double>(i,j)= img.at<double>(i,j)*diff;
			//cout<<img.at<double>(i,j)<<" "<<direction[valb%8].at<double>(i,j)<<" "<<direction[(valb+1)%8].at<double>(i,j)<<endl;
		}
	}
	blur();
}
void OrientedImage::blur(){
	for(int i=0;i<direction.size();i++)
		GaussianBlur(direction[i],direction[i],Size(7,7),-1,-1);   
}

