#include "Descriptor.h"

Descriptor Descriptor::offLine() {
	Descriptor descriptor;
	descriptor.patchSize = 60;
	descriptor.minimumEdge = 0.03f;
	descriptor.norMagnitude =  Mat::zeros(300,300,CV_64F);
	descriptor.orientation = Mat::zeros(300,300,CV_64F);
	return descriptor;
}

Descriptor::Descriptor(){
	patchSize = 60;  
	blurInitial = 0.5;
	sigma = 3;
	epsilon=4;
	sigma1=1;
	sigma2=3;
	xbuck=24;ybuck=24;tbuck=8;
	xbuck2=18;ybuck2=6;tbuck2=4;
	threshold=0.2f; 
	minimumEdge=0.01f;
	minPixVal = 0.02f;
	histogramRange = 1.0f/sqrt(2);  
	norMagnitude =  Mat::zeros(480,480,CV_64F);
	orientation = Mat::zeros(480,480,CV_64F);
}
int Descriptor:: getNumBits() {
	return xbuck2*ybuck2*tbuck2;
}
void Descriptor:: setImage(Mat& srcImage){
	Mat avgImage = Mat::zeros(srcImage.rows,srcImage.cols,CV_64F);
	Mat gradient = Mat::zeros(srcImage.rows,srcImage.cols,CV_64F);
	GaussianBlur(srcImage,srcImage,Size(-1,-1),blurInitial,blurInitial);
	double dx,dy;
	/*Steerable steer=Steerable(srcImage);	                //taking a lot of time and matching results are very bad
	  steer.applyFilter();   
	  steer.calculate(gradient,orientation,1);*/
	Mat_<uchar> srcImagetemp = srcImage;
	//cout<<srcImage.type()<<" "<<srcImagetemp.type()<<endl;
	
////////////// finding gradient and orientation //////////////

	for(int i=0;i<srcImage.rows-1;i++){
		for(int j=0;j<srcImage.cols-1;j++){

			//dx=FUN(srcImage,i,j+1,double)-FUN(srcImage,i,j,double);
			//dy=FUN(srcImage,i+1,j,double)-FUN(srcImage,i,j,double);
			dx=srcImagetemp(i,j+1)-srcImagetemp(i,j);
			dy=srcImagetemp(i+1,j)-srcImagetemp(i,j);
			FUN(gradient,i,j,double)=sqrt(dx*dx+dy*dy);
			FUN(orientation,i,j,double)=atan2(dy,dx);
			//cout<<FUN(gradient,i,j,double)<<" "<<FUN(orientation,i,j,double)<<endl;

		}
	}

///////////////normalizing gradient //////////////////////

	GaussianBlur(gradient,avgImage,Size(-1,-1),sigma,sigma); 
	for(int i=0;i<srcImage.rows;i++){
		for(int j=0;j<srcImage.cols;j++){
			FUN(norMagnitude,i,j,double)=FUN(gradient,i,j,double)/max(FUN(avgImage,i,j,double),epsilon);
		}
	}

}

void Descriptor::calc(int patchX,int patchY,vector<bool> &desc){
	double valRange=patchSize*histogramRange; 
	Histogram histogram(-valRange,valRange,xbuck,-valRange,valRange,ybuck,-M_PI,M_PI,tbuck);
	double minGradient=0;
	vector<double> vals;
	int patchBottom = patchY+patchSize;
	int patchRight = patchX+patchSize;
	int centralx = patchX+patchSize/2, centraly = patchY+patchSize/2;
	for(int i=patchX;i<patchRight;i++){
		for(int j=patchY;j<patchBottom;j++){
			if(FUN(norMagnitude,i,j,double) < minPixVal)
				continue;
			double xp = i-centralx, yp = j-centraly;
			double cos_t = cos(FUN(orientation,i,j,double));
			double sin_t = sin(FUN(orientation,i,j,double));
			double xpPrime = xp*cos_t - yp*sin_t;
			double ypPrime = xp*sin_t + yp*cos_t;

			histogram.increment(xpPrime,ypPrime,FUN(orientation,i,j,double),FUN(norMagnitude,i,j,double));
			minGradient++;
		}
	}
	if(minGradient < patchSize*patchSize*minimumEdge) //if atleast 60*60*0.01 pixel are not more than minPixVal then blank patch
		return;
	//Mat patch= norMagnitude(Rect(patchY,patchX,patchBottom-patchY,patchRight-patchX));
	//namedWindow("k",CV_WINDOW_NORMAL);
	//imshow("k",patch);

	histogram.blur(sigma1,sigma2);

	//histogram.show();
	vals=histogram.resample(xbuck2,ybuck2,tbuck2); 
	int hist_size=xbuck2*ybuck2*tbuck2;
	vector<double> arr=vals;
	sort(arr.begin(),arr.end());
	double histTh = arr[(int)(hist_size*(1-threshold))];
	for(int i=0;i<hist_size;i++){
		if(vals[i]>histTh) 
			desc.push_back(1);
		else 
			desc.push_back(0);
	}
}


