#ifndef POINT_H_
#define POINT_H_

struct POINT{
float x,y;

bool operator<(const POINT &o)  const {
 return x < o.x || (x == o.x && y < o.y);}
POINT operator + ( POINT& N)
    {
     
      POINT tmp;
	tmp.x=x+N.x;
	tmp.y=y+N.y;
      return tmp;
    }
POINT operator - (POINT& N)
    {
     
      POINT tmp;
	tmp.x=x-N.x;
	tmp.y=y-N.y;
      return tmp;
    }


};

#endif

