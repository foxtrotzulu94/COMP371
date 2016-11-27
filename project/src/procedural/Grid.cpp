#include <iostream>
#include <vector>

#include "procedural\Grid.h"

std::ostream& operator<<(std::ostream& os, const Grid::Coordinate& coord)
{
	os <<'('<<coord.x << ',' << coord.y<< ')';
	return os;
}

Grid::Grid()
{
	realWidth = ((float)WIDTH)*CELL;
	realHeight = ((float)HEIGHT)*CELL;

	//Initialize all to zero
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; j++){
			Cells[i][j] = Type::Empty;
		}
	}
}

Grid::~Grid()
{
	//Nothing to cleanup here
}

void Grid::FillLine(int start, int end, int axisPoint, Grid::Axis axis, Grid::Type fillValue)
{
	//Error checking
	#if _DEBUG
	if (start<0||start>=WIDTH||end<0||end<start||end>=WIDTH||axis>Y||axis<X) {
		__debugbreak();
	}
	#endif

	if (axis == Axis::X) {
		for (int i = start; i < end; i++){
			Cells[i][axisPoint] = fillValue;
		}
	}
	else if (axis == Axis::Y) {
		for (int i = start; i < end; i++)	{
			Cells[axisPoint][i] = fillValue;
		}
	}

	//TODO: perhaps record all the segments in here...
}

void Grid::FillRecursive(int x, int y, Grid::Type fillValue)
{
	//Check bounds
	if (x < 0 || x >= WIDTH || y<0 || y>HEIGHT) {
		std::cerr << "ERROR: Attempted to fill recursively outside of grid! " << std::endl;
		#if _DEBUG
		__debugbreak();
		#endif
	}

	Grid::Type value = Cells[x][y];
	std::vector<Coordinate> stack;
	stack.push_back(Coordinate(x, y));
	while (stack.size()>0)
	{
		Coordinate currCell = stack.back();
		stack.pop_back();
		//Check if valid for recursiveness
		if (currCell.isValid() && Cells[currCell.x][currCell.y]==value) {
			x = currCell.x;
			y = currCell.y;
			Cells[x][y] = fillValue;
			//add the neighbors
			stack.push_back(Coordinate(x-1, y));
			stack.push_back(Coordinate(x-1, y-1));
			stack.push_back(Coordinate(x-1, y + 1));

			stack.push_back(Coordinate(x + 1, y + 1));
			stack.push_back(Coordinate(x + 1, y - 1));
			stack.push_back(Coordinate(x + 1, y));

			stack.push_back(Coordinate(x, y + 1));
			stack.push_back(Coordinate(x, y - 1));
		}
	}
}

void Grid::TerminalPrint()
{
	for (int i = 0; i < WIDTH; i++)
	{
		std::cout << "_";
	}
	std::cout << std::endl;
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; j++)
		{
			if (Cells[i][j] == Grid::Type::Road)
				std::cout << '#';
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < WIDTH; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;
}

Bounds Grid::GetRealBounds()
{
	return Bounds(0.f,realWidth,0.f,realHeight);
}