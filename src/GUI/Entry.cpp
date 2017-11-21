#include "Entry.h"
#include<iostream>
using namespace std;
Entry::Entry(int _sketch, int _imgId, int _x, int _y) {
    sketch = _sketch;
    imgId = _imgId;
    x = _x;
    y = _y;
}
 /*bool Entry::operator==(const Entry& a) const {
 return imgId==a.imgId && x==a.x && y==a.y;
  }
bool Entry:: operator < (const Entry& a){ //so that comparing operator work on two entries

if(imgId<a.imgId)
return 1;
else if(imgId==a.imgId && x<a.x)
return 1;
else if(imgId==a.imgId && x==a.x && y<a.y)
return 1;
//return (sketch<a.sketch) || (sketch==a.sketch && imgId<a.imgId) || (sketch==a.sketch && imgId==a.imgId && x<a.x) || (sketch==a.sketch && imgId==a.imgId && x==a.x && y<a.y);
else 
return 0;

}*/


