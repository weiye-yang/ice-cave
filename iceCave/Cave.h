#ifndef CAVE_H
#define CAVE_H
#include <vector>
#include <cassert>
#include <iostream>

// legend: * is ice, O is rock, P is player, S is start, E is end
class Cave
{
private:
	int m_height;
	int m_width;
	std::vector<char> m_grid; // grid with one index. We deal with this later

	int m_startLoc;
	int m_exitLoc;

public:
	const int totalCells{ m_height * m_width };
	const int rockRatio = 4; //the proportion of spaces that are rock on average. 1/rockRatio

	Cave( int height, int width)
		: m_height(height), m_width(width)
	{
		assert(m_height > 1 && m_width > 1); //sanity check

		m_grid.resize(totalCells); //allocate grid
		m_startLoc = 0;
		m_exitLoc = totalCells - 1;
		m_grid[m_startLoc] = 'S';
		m_grid[m_exitLoc] = 'E';
		for (int i = 1; i < totalCells - 1; ++i) m_grid[i] = '*';
		
	}
	/*
	~Cave() //deallocate grid
	{
		delete[] m_grid;
	}
	*/

	//overload print
	friend std::ostream& operator<< (std::ostream &out, const Cave &cave);

	//overload parentheses to make it easier to fetch cells of the grid
	char& operator()(int down, int across);
	//and a const version for being an r-value
	const char& operator()(int down, int across) const;

	void randomize(); //random cave generator

private:// accessories for randomizer
	bool placeStart(); //the exit is placed randomly; this function places the start such that the cave is solvable

	friend class GameState;

};

#endif // !CAVE_H

