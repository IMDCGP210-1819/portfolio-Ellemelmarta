#include "Grid.h"



Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::CreateGrid()
{
	//Grid stored in an array of arrays
	char grid[5][5] = { {'0','0','0','0','0'},
	{'0','0','0','0','0'},
	{'0','0','0','0','0'},
	{'0','0','0','0','0'},
	{'0','0','0','0','0'} };

	//drawing the grid
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << grid[i][j];
			std::cout << " ";
		}
		std::cout << std::endl;
	}

}