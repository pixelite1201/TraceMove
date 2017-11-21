#include "Grid.h"
Grid::Grid(){
}
Grid::Grid(int width,int height){
	cellSize=60;
	cellOffset=15;
	cells.resize(1+(width-cellSize)/cellOffset);
	for(int i=0;i<cells.size();i++)
		cells[i].resize(1+(height-cellSize)/cellOffset);

	for(int i = 0, x = 0; i < cells.size(); i++, x += cellOffset) { 
		for(int j = 0, y = 0; j < cells[0].size(); j++, y += cellOffset) {
			cells[i][j] = Cell(x,y);
		}
	}
}


