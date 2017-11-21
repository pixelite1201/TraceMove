#include "Correlation.h"
Correlation::Correlation(OrientedImage& img1,OrientedImage& img2):matchImg(img1),testImg(img2){
	hScore=0;
	positiveC=Mat::zeros(matchImg.img.rows,matchImg.img.cols,CV_64F);
	negativeC=Mat::zeros(matchImg.img.rows,matchImg.img.cols,CV_64F);
}
void Correlation:: calcOrientedImage(){

	for(int i=0;i<8;i++){


		positiveC+= matchImg.direction[i].mul(testImg.direction[i]);

		negativeC+= matchImg.direction[i].mul(testImg.direction[(i+4)%8]);
	}
Mat positiveC_resize=positiveC.clone();
Mat negativeC_resize=negativeC.clone();
resize(positiveC,positiveC_resize,Size(40,40));
resize(negativeC,negativeC_resize,Size(40,40));
positiveC_resize.convertTo(positiveC_resize,CV_8UC1);
negativeC_resize.convertTo(negativeC_resize,CV_8UC1);
//cv::normalize(positiveC,positiveC,0.0,1.0,NORM_MINMAX);
//cv::normalize(negativeC,negativeC,0.0,1.0,NORM_MINMAX);
//imshow("neg",negativeC);
//imshow("pos",positiveC);
//waitKey(0);
	for(int i=0;i<negativeC_resize.rows;i++){
		for(int j=0;j<negativeC_resize.cols;j++){
			//cout<<(int)positiveC.at<uchar>(i,j)<<" "<<(int)negativeC.at<uchar>(i,j)<<endl;
			hScore+=positiveC_resize.at<uchar>(i,j)-negativeC_resize.at<uchar>(i,j);  //note that double not used here, and converted 	                                                                                    to int because of large values. Not sure if correct

		}
	}
}
