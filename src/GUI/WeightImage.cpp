#include "WeightImage.h"
#include "algorithm"
WeightImage::WeightImage(){
}
WeightImage::WeightImage(int size,Mat img):_testImg(img){
	matchingImg.resize(size);
	V.resize(size);
	W.resize(size);
	for(int i=0;i<size;i++){
		matchingImg[i]=Mat::zeros(img.rows,img.cols,CV_64F);
		V[i]=Mat::zeros(img.rows,img.cols,CV_64F);
		W[i]=Mat::zeros(img.rows,img.cols,CV_64F);
	}

	v.resize(size);
	_testImg.convertTo(_testImg,CV_64F);
	testImg=OrientedImage(_testImg);  // I have used OrientedImage testImg(_testImg) here, so it has created a testImg local var here 
	//and not modifying the orig one
	testImg.calculateOrient();


}
void WeightImage:: fillImg(int pos,Mat retrievedImages){
	matchingImg[pos]=retrievedImages.clone();  
	matchingImg[pos].convertTo(matchingImg[pos],CV_64F); // required in MatchingImage.cpp to perform mult with W[i]
	
}
void WeightImage:: calculate(){
	vector<double> maxhighScores;

	for(int i=0;i<matchingImg.size();i++){
		OrientedImage matchImg(matchingImg[i]);
		//Mat M=Mat::zeros(matchingImg[i].rows,matchingImg[i].cols,CV_64F);
		//normalize(matchingImg[i],M,0.0,1.0,NORM_MINMAX);
		//imshow("img",M);
		matchImg.calculateOrient();	
		Correlation C(matchImg,testImg);
		C.calcOrientedImage();
		C.positiveC=C.positiveC;
		GaussianBlur(C.positiveC,V[i],Size(27,27),-1,-1);
		//V[i]=V[i]+Mat::ones(V[i].rows,V[i].cols,CV_64F);//small offset
		//V[i]=C.positiveC;
		maxhighScores.push_back(C.hScore);
		//normalize(V[i],V[i],0.0,1.0,NORM_MINMAX);
		//imshow("werr",V[i]);
		//waitKey(0);
	}
	
	vector<double> tempmaxhighScores;
	tempmaxhighScores.resize(maxhighScores.size());
	copy(maxhighScores.begin(),maxhighScores.end(),tempmaxhighScores.begin());
	sort(tempmaxhighScores.rbegin(),tempmaxhighScores.rend());
	double avgH;

	for(int k=0;k<5;k++)
		avgH+=tempmaxhighScores[k];
	avgH/=5.0;
	avgH/=2.0;  //as avgH not needed but avgH/2 needed
	Mat normalize=Mat(V[0].size(),V[0].type());

	for(int i=0;i<matchingImg.size();i++){
	v[i]=std::max(0.0,std::pow((maxhighScores[i]-avgH)/avgH,2.0));  //confirm that 3 is ok
		V[i]=v[i]*V[i];
		normalize+=V[i];
		cout<<v[i]<<endl;
	}
	for(int i=0;i<matchingImg.size();i++){
		divide(V[i],normalize,W[i]);
		//cv::normalize(W[i],W[i],0.0,1.0,NORM_MINMAX);
		//imshow("werr",W[i]);
		//waitKey(0);
	}

	/*for(int i=0;i<matchingImg[0].rows;i++){
	  for(int j=0;j<matchingImg[0].cols;j++){
	  cout<<(int)W[0].at<uchar>(i,j)<<" ";
	  }
	  cout<<endl;
	  }*/


}

