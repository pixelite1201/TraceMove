#include "Steerable.h" 
double argum(double x, double y)
  {
     double out;
     //first quadrant
     if ((x >  0) && (y >  0)) {out = atan(y/x);}
     //second quadrant
     if ((x <  0) && (y >  0)) {out = M_PI + atan(y/x);}
     //third qudrant
     if ((x <  0) && (y <  0)) {out = M_PI + atan(y/x);}
     //fourth quadrant
     if ((x >  0) && (y < 0))  {out = 2 * M_PI + atan(y/x);}

     //limit cases
     if ((x == 0) && (y >  0)) {out = M_PI / 2;}
     if ((x == 0) && (y <  0)) {out = 3 * M_PI /2;}
     if ((x >  0) && (y == 0)) {out = 0.0;}

   //  printf("out = %lf\n",out);
     return out;
  }
Steerable::Steerable(){
}
Steerable::Steerable(Mat& img_):img(img_),g2f1_({ 0.001933,  0.118119,  0.338927, -0.921300,  0.338927, 0.118119, 0.001933}),
	g2f2_({ 0.000123,  0.018316,  0.367879,  1.000000,  0.367879, 0.018316, 0.000123}),
	g2f3_({-0.000503, -0.049745, -0.499580,  0.000000,  0.499580, 0.049745, 0.000503}),
	h2f1_( {-0.002443, -0.062551,  0.451172,  0.000000, -0.451172, 0.062551, 0.002443}),
	h2f2_({ 0.000123,  0.018316,  0.367879,  1.000000,  0.367879, 0.018316, 0.000123}),
	h2f3_({-0.000370, -0.036631, -0.367879,  0.000000,  0.367879, 0.036631, 0.000370}),
	h2f4_({ 0.001018,  0.059498,  0.091418, -0.751500,  0.091418, 0.059498, 0.001018}){
		//before I had define g2f1_,g2f2_ etc. in Constructor only and here next 14 lines are using its address to initialize Mat, hence getting random output
		g2f1y=Mat(7,1,CV_64F,g2f1_);
		g2f2y=Mat(7,1,CV_64F,g2f2_);
		g2f3y=Mat(7,1,CV_64F,g2f3_);
		h2f1y=Mat(7,1,CV_64F,h2f1_);
		h2f2y=Mat(7,1,CV_64F,h2f2_);
		h2f3y=Mat(7,1,CV_64F,h2f3_);
		h2f4y=Mat(7,1,CV_64F,h2f4_);
		g2f1x=Mat(1,7,CV_64F,g2f1_);
		g2f2x=Mat(1,7,CV_64F,g2f2_);
		g2f3x=Mat(1,7,CV_64F,g2f3_);
		h2f1x=Mat(1,7,CV_64F,h2f1_);
		h2f2x=Mat(1,7,CV_64F,h2f2_);
		h2f3x=Mat(1,7,CV_64F,h2f3_);
		h2f4x=Mat(1,7,CV_64F,h2f4_);
		G2a=Mat::zeros(img.rows,img.cols,CV_64F);
		G2b=Mat::zeros(img.rows,img.cols,CV_64F);
		G2c=Mat::zeros(img.rows,img.cols,CV_64F);
		H2a=Mat::zeros(img.rows,img.cols,CV_64F);
		H2b=Mat::zeros(img.rows,img.cols,CV_64F);
		H2c=Mat::zeros(img.rows,img.cols,CV_64F);
		H2d=Mat::zeros(img.rows,img.cols,CV_64F);
		C1=Mat::zeros(img.rows,img.cols,CV_64F);
		C2=Mat::zeros(img.rows,img.cols,CV_64F);
		C3=Mat::zeros(img.rows,img.cols,CV_64F);

	}
void Steerable::applyFilter(){
	sepFilter2D(img,G2a,CV_64FC1,g2f1x,g2f2y,Point(-1,-1),0,BORDER_REPLICATE);
	sepFilter2D(img,G2b,CV_64FC1,g2f3x,g2f3y,Point(-1,-1),0,BORDER_REPLICATE);
	sepFilter2D(img,G2c,CV_64FC1,g2f2x,g2f1y,Point(-1,-1),0,BORDER_REPLICATE);
	sepFilter2D(img,H2a,CV_64FC1,h2f1x,h2f2y,Point(-1,-1),0,BORDER_REPLICATE);
	sepFilter2D(img,H2b,CV_64FC1,h2f4x,h2f3y,Point(-1,-1),0,BORDER_REPLICATE);
	sepFilter2D(img,H2c,CV_64FC1,h2f3x,h2f4y,Point(-1,-1),0,BORDER_REPLICATE);
	sepFilter2D(img,H2d,CV_64FC1,h2f2x,h2f1y,Point(-1,-1),0,BORDER_REPLICATE);
}
void Steerable::saveOrientedImages(){
	imwrite("G2a.jpg",G2a);
	imwrite("G2b.jpg",G2b);
	imwrite("G2a.jpg",G2c);
	imwrite("H2a.jpg",H2a);
	imwrite("H2b.jpg",H2b);
	imwrite("H2c.jpg",H2c);
	imwrite("H2d.jpg",H2d);

}
void Steerable::calculate(Mat& mag,Mat& orient,int flag){
	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{

			C1.at<double>(i,j) =  0.5    * pow(G2b.at<double>(i,j),2)
				+ 0.25   * G2a.at<double>(i,j) * G2c.at<double>(i,j)
				+ 0.375  * (pow(G2a.at<double>(i,j),2) + pow(G2c.at<double>(i,j),2))
				+ 0.3125 * (pow(H2a.at<double>(i,j),2) + pow(H2d.at<double>(i,j),2))
				+ 0.5625 * (pow(H2b.at<double>(i,j),2) + pow(H2c.at<double>(i,j),2))
				+ 0.375  * ((H2a.at<double>(i,j) * H2c.at<double>(i,j)) + (H2b.at<double>(i,j) * H2d.at<double>(i,j)));

			C2.at<double>(i,j) =      0.5 * (pow(G2a.at<double>(i,j),2) - pow(G2c.at<double>(i,j),2))
				+ 0.46875 * (pow(H2a.at<double>(i,j),2) - pow(H2d.at<double>(i,j),2))
				+ 0.28125 * (pow(H2b.at<double>(i,j),2) - pow(H2c.at<double>(i,j),2))
				+ 0.1875  * (H2a.at<double>(i,j) * H2c.at<double>(i,j) - H2b.at<double>(i,j) * H2d.at<double>(i,j));

			C3.at<double>(i,j) = - G2a.at<double>(i,j) * G2b.at<double>(i,j)
				- G2b.at<double>(i,j) * G2c.at<double>(i,j)
				- 0.9375 * (H2c.at<double>(i,j) * H2d.at<double>(i,j) + H2a.at<double>(i,j) * H2b.at<double>(i,j))
				- 1.6875 * H2b.at<double>(i,j) * H2c.at<double>(i,j)
				- 0.1875 * H2a.at<double>(i,j) * H2d.at<double>(i,j);
		}
	}
	if(flag==1){
	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			mag.at<double>(i,j) = sqrt(pow(C2.at<double>(i,j), 2) + pow(C3.at<double>(i,j), 2));
			orient.at<double>(i,j) = argum(C2.at<double>(i,j), C3.at<double>(i,j)) * 0.5;
			//cout<<orient.at<double>(i,j)<<" ";
		}//cout<<endl;
	}

}
else{
	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			mag.at<double>(i,j) = sqrt(pow(C2.at<double>(i,j), 2) + pow(C3.at<double>(i,j), 2));
			orient.at<double>(i,j) = argum(C2.at<double>(i,j), C3.at<double>(i,j)) * 0.5*180.0*(7.0/22.0);
			//cout<<orient.at<double>(i,j)<<" ";
		}//cout<<endl;
	}
}


	//	normalize(G2a,G2a,0,1,NORM_MINMAX);
	//	normalize(G2b,G2b,0,1,NORM_MINMAX);
	//	normalize(G2c,G2c,0,1,NORM_MINMAX);
	//	normalize(H2a,H2a,0,1,NORM_MINMAX);
	//	normalize(H2b,H2b,0,1,NORM_MINMAX);
	//	imshow("A",G2a);
	//	imshow("B",G2b);
	//	imshow("C",G2c);
	//	imshow("D",H2a);
	//	imshow("E",H2b);
	//	waitKey(0);
}
