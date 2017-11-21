#include "Histogram.h"
using namespace std;
using namespace cv;
Histogram::Histogram(
		double minX, double maxX, int bin_x,
		double minY, double maxY, int bin_y,
		double minT, double maxT, int bin_t
		) {
	xbuck = bin_x;
	ybuck = bin_y;
	tbuck = bin_t;
	x_mult = xbuck/(maxX-minX); x_low = minX;
	y_mult = ybuck/(maxY-minY); y_low = minY;
	t_mult = tbuck/(maxT-minT); t_low = minT; 
	values.resize(tbuck);
	for(int i=0;i<tbuck;i++){
		values[i].resize(xbuck);
		for(int j=0;j<xbuck;j++){
			values[i][j].resize(ybuck);
		}
	}

}
 /*Histogram::Histogram(int xBuck, int yBuck, int tBuck) {
    xbuck = xBuck;
    ybuck = yBuck;
    tbuck = tBuck;
    values.resize(tbuck);
	for(int i=0;i<tbuck;i++){
		values[i].resize(xbuck);
		for(int j=0;j<xbuck;j++){
			values[i][j].resize(ybuck);
		}
	}

  }*/
void Histogram:: increment(double x,double y,double t,double norMagnitude){
	double tb=int(t-t_low)*t_mult; 
	double xb=int(x-x_low)*x_mult; 
	double yb=int(y-y_low)*y_mult; 
       // cout<<"tb "<<tb<<" xb "<<xb<<" yb "<<yb<<endl;
	 int tbl = (int)tb;
int tbr = (int)ceil(tb)%tbuck;
int xbl = (int)xb;
int xbr = (int)ceil(xb)%xbuck;
int ybl = (int)yb;
int ybr = (int)ceil(yb)%ybuck;
double tt = tb-tbl, tx = xb-xbl, ty = yb-ybl; 
values[tbl][xbl][ybl]+= norMagnitude*(1-tt)*(1-tx)*(1-ty);
values[tbl][xbl][ybr]+= norMagnitude*(1-tt)*(1-tx)*(ty);
values[tbl][xbr][ybl]+= norMagnitude*(1-tt)*(tx)*(1-ty);
values[tbr][xbl][ybl]+= norMagnitude*(tt)*(1-tx)*(1-ty);
values[tbl][xbr][ybr]+= norMagnitude*(1-tt)*(tx)*(ty);
values[tbr][xbl][ybr]+= norMagnitude*(tt)*(1-tx)*(ty);
values[tbr][xbr][ybl]+= norMagnitude*(tt)*(tx)*(1-ty);
values[tbr][xbr][ybr]+= norMagnitude*(tt)*(tx)*(ty);

	//values[tb][xb][yb] += norMagnitude;//do linear soft binning 
//cout<<"nor "<<norMagnitude<<endl; 
//cout<<values[tb][xb][yb]<<endl;
}
/*Mat mat2gray(const Mat& src)
{
	Mat dst;
	normalize(src, dst, 0.0, 1.0, NORM_MINMAX);
	return dst;
}*/
void Histogram::show(){
Mat show=Mat::zeros(xbuck,ybuck,CV_64F);
for(int t=0;t<tbuck;t++){
for(int x=0;x<xbuck;x++){
for(int y=0;y<ybuck;y++){
show.at<double>(x,y)=values[t][x][y];
}
}
cout<<t<<endl;
namedWindow("w",CV_WINDOW_NORMAL);
imshow("w",(show));  //show at t(th) bucket orientation
waitKey(0);
}
cout<<endl;
}
void Histogram::blur(int sigma1,int sigma2){//a,b,c = xbuck,tbuck,ybuck - different order
	Mat temp_blur;
	
	for(int i=0;i<tbuck;i++){
		temp_blur=Mat(xbuck,ybuck,CV_64F);
		for(int j=0;j<xbuck;j++){
			for(int k=0;k<ybuck;k++){
				temp_blur.at<double>(j,k)=values[i][j][k];
			}
		}
		GaussianBlur(temp_blur,temp_blur,Size(-1,-1),sigma1,sigma2); 
		
		for(int j=0;j<xbuck;j++){
			for(int k=0;k<ybuck;k++){
				values[i][j][k]=temp_blur.at<double>(j,k);
			}
		}
	}


	for(int i=0;i<xbuck;i++){
		temp_blur=Mat(tbuck,ybuck,CV_64F);
		for(int j=0;j<tbuck;j++){
			for(int k=0;k<ybuck;k++){
				temp_blur.at<double>(j,k)=values[j][i][k];
			}
		}
		GaussianBlur(temp_blur,temp_blur,Size(1,2*sigma1+1),sigma1,sigma1); //check if its Size should be same or (2*sigma1,1)
		//GaussianBlur(temp_blur,temp_blur,Size(2*sigma2+1,1),sigma2,sigma2); 
		for(int j=0;j<tbuck;j++){
			for(int k=0;k<ybuck;k++){
				values[j][i][k]=temp_blur.at<double>(j,k);
			}
		}
	}

}

vector<double> Histogram::resample(int xbuck2,int ybuck2,int tbuck2){
vector<double> vals;
vals.resize(tbuck2*xbuck2*ybuck2);
int i = 0;
double tStep = tbuck/(double)tbuck2;
double yStep = ybuck/(double)ybuck2;
double xStep = xbuck/(double)xbuck2;   
    for(double t = 0; t < tbuck; t += tStep) {
      for(double y = 0; y < ybuck; y += yStep) {
        for(double x = 0; x < xbuck; x += xStep) {
          vals[i] = bFinalValue(x, y, t);
          i++;
        }
      }
    }
    return vals;
}
double Histogram::interpolate(double v1,double v2,double div){ 

return (v1*(1-div)+v2*div);
}
double Histogram::bFinalValue(double xb, double yb, double tb) { //note that here tt and ty are 0 hence no interpolation is required, but still
 							     // I kept it so that if these values are changed later, it will help
    int
    tbl = (int)tb, tbr = (int)ceil(tb),
    xbl = (int)xb, xbr = (int)ceil(xb),
    ybl = (int)yb, ybr = (int)ceil(yb);
    double tt = tb-tbl, tx = xb-xbl, ty = yb-ybl; 
    return interpolate(
	interpolate(
      	  interpolate(values[tbl][xbl][ybl], values[tbr][xbl][ybl], tt),
          interpolate(values[tbl][xbr][ybl], values[tbr][xbr][ybl], tt),
            tx),
        interpolate(
            interpolate(values[tbl][xbl][ybr], values[tbr][xbl][ybr], tt),
            interpolate(values[tbl][xbr][ybr], values[tbr][xbr][ybr], tt),
            tx),
        ty);
    
    
  }



