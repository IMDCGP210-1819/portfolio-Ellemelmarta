#include "Main.h"
#include <iostream>

#include "Grid.h"
using namespace std;


int main()
{

	Grid *testGrid = new Grid();

	testGrid->CreateGrid();

	cin.get();

	return 0;
}