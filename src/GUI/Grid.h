/*!
  \file Grid.h
  \brief This file will store the patch location of different patches of image
*/
#include "Cell.cpp"
class Grid{
public:
//! Size of one patch of user drawn image
int cellSize;
//! Offset between first patch and the next patch of user drawn image
int cellOffset;
//! Will store x,y location of patch in the user drawn image.
/*! First dimension denotes patches along x axis, second dimension along y axis*/
vector<vector<Cell> > cells;
//! Constructor
Grid(int,int);
//! Constructor2
Grid();
};
