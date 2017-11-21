/*!
  \file Cell.h
  \brief This file describe the location of Cell within image
*/
#include<vector>
using namespace std;
class Cell {
	public:
		int x, y;
		//vector<Entry> matchingEntries;
		Cell(int _x=0,int _y=0){
		x=_x;y=_y;}
		//void clear(){
		//	matchingEntries.clear();
		//	}
};

