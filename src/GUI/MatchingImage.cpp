#include "MatchingImage.h"
#include<stdlib.h>
Mat mat2gray(const Mat& src)
{
	Mat dst;
	normalize(src, dst, 0.0, 1.0, NORM_MINMAX);
	return dst;
}
bool valid(int a,int b){
	if(a>=0 && a<b)
		return 1;
	else 
		return 0;
}
MatchingImage::MatchingImage(){
}
MatchingImage::MatchingImage(int _maxNumber,string path_to_DB):maxNumber(_maxNumber),path(path_to_DB){
	//resize(img,resizeimg,Size(40,40));
	//Weight= WeightImage(maxNumber,img); //note that by initialzing it using initializer list, I don't need to define 
	//WeightImage(){}, because WeightImage Weight; is not called as this initializer 
	//list is called even before that

	IndexStorage is;

	index= is.read(path);

	descriptor = descriptor.offLine(); 
	
}
void MatchingImage::castVotes(Mat& img_){
img=img_;
votes.clear();
descriptor.setImage(img);
	grid = Grid(img.cols,img.rows);
	vector<bool> desc;
	for(int i=0;i<grid.cells.size();i++){
		for(int j=0;j<grid.cells[i].size();j++){
			desc.clear();
			descriptor.calc(grid.cells[i][j].x,grid.cells[i][j].y,desc);
			if(desc.size()>0){
				
				ResultSet* found = index.findAllEntries(desc);
				for(int l=0;l<20;l++) {
					vector<Entry> es=found->results[l];
					for(int k=0;k<es.size();k++) { 
						Entry e=es[k];
						//	cout<<e.sketch<<endl;
						addVotes(grid.cells[i][j],e,min(20-l,4)); //check efficiency using 1
					}
				}
				delete found;
			}

		}

	}
}
void MatchingImage::addVotes(Cell c, Entry e,int l) {
	// c.matchingEntries.push_back(e);
	
	ImageVotes *v;
	if(votes.find(e.imgId)==votes.end())
	{
		v=new ImageVotes(e.imgId,grid);   //note that before I was using ImageVotes v= ImageVotes(e.imgId,grid) that was problem
		//see stackoverflow
		votes.insert(pair<int,ImageVotes>(e.imgId,*v));
	}
	else{
		v=&votes.find(e.imgId)->second;
	}
	v->alterVotes(c.x-e.x, c.y-e.y, l);

}
bool sort_function(const vector<int>& a,const vector<int>& b){
	if(a.size()==4 && b.size()==4)
	return a[1]>=b[1];
	else
	return 0;
}
void MatchingImage::fineAlignment(Mat matchingImg,Mat testImg, int& final_dx,int& final_dy){
	double maximum=0; 
	int range=grid.cellOffset;
	int dx=final_dx;
	int dy=final_dy;
	resize(matchingImg,matchingImg,Size(160,160));
	resize(testImg,testImg,Size(160,160));
	matchingImg.convertTo(matchingImg,CV_8UC1);
	testImg.convertTo(testImg,CV_8UC1);
	Mat o_Mimg = Mat::zeros(img.rows,img.cols,CV_32F);
	Mat m_Mimg = Mat::zeros(img.rows,img.cols,CV_32F);

	Mat o_Timg = Mat::zeros(img.rows,img.cols,CV_32F);
	Mat m_Timg = Mat::zeros(img.rows,img.cols,CV_32F);
	Steerable f_Mimg=Steerable(matchingImg);
	f_Mimg.applyFilter();
	f_Mimg.calculate(m_Mimg,o_Mimg,1);  
	Steerable f_Timg=Steerable(testImg);
	f_Timg.applyFilter();
	f_Timg.calculate(m_Timg,o_Timg,1);

	for(int x=-range;x<range;++x){
		double tmp=0;
		for(int i=0;i<matchingImg.rows;i++){
			for(int j=0;j<matchingImg.cols;j++){
				if(valid(i+dx+x,matchingImg.rows) && valid(j+dy,matchingImg.cols))
					tmp+=abs(sin(o_Timg.at<float>(i,j)))*testImg.at<uchar>(i,j)*abs(sin(o_Mimg.at<float>(i+dx+x,j+dy)))*matchingImg.at<uchar>(i+dx+x,j+dy);  //check if doing abs is correct
			}
		}

		if(tmp>maximum){
			final_dx = dx + x;
			maximum = tmp;

		}
	}

	maximum = 0;
	for(int y=-range;y<range;++y){
		double tmp=0;
		for(int i=0;i<matchingImg.rows;i++)
			for(int j=0;j<matchingImg.cols;j++)
				if(valid(i+dx,matchingImg.rows) && valid(j+dy+y,matchingImg.cols))
					tmp+=abs(cos(o_Timg.at<float>(i,j)))*testImg.at<uchar>(i,j)*abs(cos(o_Mimg.at<float>(i+dx,j+dy+y)))*matchingImg.at<uchar>(i+dx,j+dy+y);
		if(tmp>maximum){
			final_dy = dy + y;
			maximum = tmp;
		}
	}

}
void MatchingImage::findMaxima(){
Weight=(WeightImage(maxNumber,img));
	vector<vector<int> > mImages;
	vector<int> mImagestemp;
	for(unordered_map<int,ImageVotes>:: iterator it=votes.begin();it!=votes.end();it++){
		mImagestemp.push_back(it->first);
		mImagestemp.push_back(it->second.maxVotes);
		mImagestemp.push_back((it->second.maxbinX-1)*grid.cellOffset);
		mImagestemp.push_back((it->second.maxbinY-1)*grid.cellOffset);

		mImages.push_back(mImagestemp);
		mImagestemp.clear();

	}
cout<<mImages.size()<<endl;
	sort(mImages.begin(),mImages.end(),sort_function);

	Mat retrievedImages;string dirName="./image/";
	
	for(int i=0;i<maxNumber ;i++){
		cout<<dirName+index.imageNames[mImages[i][0]]<<endl;
		
		retrievedImages=imread(dirName+index.imageNames[mImages[i][0]]);
		imwrite(to_string(i)+"_shd.jpg",retrievedImages);
		cvtColor(retrievedImages,retrievedImages,CV_BGR2GRAY);
		cout<<mImages[i][2]<<" "<<mImages[i][3]<<endl;
		fineAlignment(retrievedImages,img,mImages[i][2],mImages[i][3]);
		cout<<mImages[i][2]<<" "<<mImages[i][3]<<endl;
		shift(retrievedImages,retrievedImages,Point2f(mImages[i][3],mImages[i][2]),cv::BORDER_CONSTANT,cv::Scalar(0,0,0,0)); 

	
		if(!retrievedImages.empty()){

			Weight.fillImg(i,retrievedImages);


		}
	}

	Weight.calculate();
	Mat finalImage=Mat::zeros(Weight.matchingImg[0].size(),Weight.matchingImg[0].type());
	Mat finalImageblur=Mat::zeros(Weight.matchingImg[0].size(),Weight.matchingImg[0].type());
	Mat eps=Mat::ones(Weight.matchingImg[0].size(),Weight.matchingImg[0].type());
	for(int i=0;i<maxNumber;i++){
		normalize(Weight.matchingImg[i],Weight.matchingImg[i],0,255,NORM_MINMAX);
		img.convertTo(img,Weight.matchingImg[i].type());
		normalize(img,img,0,255,NORM_MINMAX);
		Mat blend=Mat::zeros(Weight.matchingImg[i].size(),Weight.matchingImg[i].type());
		blend=0.5*Weight.matchingImg[i]+0.5*img;
		
	//imshow("blend",mat2gray(blend));
	
	//waitKey(0);
}
	for(int i=0;i<maxNumber;i++){

		finalImage+=Weight.W[i].mul(Weight.matchingImg[i]);
		//imshow("a.jpg",mat2gray(finalImage));
		//waitKey(0);
		//cout<<Weight.W[i].type()<<" "<<Weight.matchingImg[i].type()<<endl;
	}
	GaussianBlur(finalImage,finalImageblur,Size(-1,-1),16,16);
	finalImage=finalImage.mul(finalImageblur-eps);
	GaussianBlur(finalImage,finalImage,Size(-1,-1),1.25,1.25);
	//GaussianBlur(finalImage,finalImage,Size(-1,-1),1.25,1.25);
	normalize(finalImage, finalImage, 0, 255, NORM_MINMAX);
	imwrite("b.jpg",(finalImage));
	finalImage=Scalar::all(255) - finalImage;
	imwrite("a.jpg",(finalImage));
	/////////////////////// for showing top matching images //////////////////////////
	/*for(int i=0;i<=5 ;i++){
	  img=imread(dirName+index.imageNames[mImages[i].first]);
	  imshow("a",img);
	  waitKey(0);

	  }*/


}


	
	
