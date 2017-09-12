#include "stdafx.h"
#include "Cave.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


std::ostream& operator<< (std::ostream &out, const Cave &cave) //print
{
	for (int down = 0; down < cave.m_height; ++down)
	{
		for (int across = 0; across < cave.m_width; ++across)
		{
			std::cout << cave(down, across) << " ";
		}
		std::cout << "\n";
	}
	return out;
}

char& Cave::operator()(int down, int across) //get cells of grid
{
	assert(down >= 0 && down < m_height && across >= 0 && across < m_width);
	return m_grid[m_width * down + across];
}
const char& Cave::operator()(int down, int across) const //const version of above
{
	assert(down >= 0 && down < m_height && across >= 0 && across < m_width);
	return m_grid[m_width * down + across];
}

void Cave::randomize()
{
	srand(time(0));
	rand();

	bool success;
	do
	{
		for (int i = 0; i < totalCells; ++i) //place rocks
		{
			if ((rand() % rockRatio))
				m_grid[i] = '*';
			else
				m_grid[i] = 'O';
		}

		m_exitLoc = rand() % totalCells; //place exit
		m_grid[m_exitLoc] = 'E';

		success = placeStart(); //place start, potentially unsuccessfully
	} while (!success);

	m_grid[m_startLoc] = 'S';
	
}

bool Cave::placeStart() //places start location at a point from which cave is solvable. finds this via an iterative method
{
	std::vector<int> solvable(totalCells); //we want solvable to be 0 at i if and only if the cave is unsolvable from i
	//and positive at i if and only if i corresponds to a potential starting position
	//and if positive, equals the minimum number of steps to solve from i

	int solveCount(0); //we'll count the number of cells from which the cave is solvable in 1 step

	solvable[m_exitLoc] = -1; //the only index to have a negative value
	int exitDown = m_exitLoc / m_width;
	int exitAcross = m_exitLoc % m_width; //coordinates of exit
	for (int height = exitDown - 1; height >= 0 && (*this)(height, exitAcross) != 'O'; --height) //look up
	{
		solvable[height * m_width + exitAcross] = 1;
		++solveCount;
	}
	for (int height = exitDown + 1; height < m_height && (*this)(height, exitAcross) != 'O'; ++height) //look down
	{
		solvable[height * m_width + exitAcross] = 1;
		++solveCount;
	}
	for (int width = exitAcross - 1; width >= 0 && (*this)(exitDown, width) != 'O'; --width) //look left
	{
		solvable[exitDown * m_width + width] = 1;
		++solveCount;
	}
	for (int width = exitAcross + 1; width < m_width && (*this)(exitDown, width) != 'O'; ++width) //look right
	{
		solvable[exitDown * m_width + width] = 1;
		++solveCount;
	}
	// if there are no possible starting locations at this stage, give up
	if (solveCount == 0)
		return false;

	bool recurse = true; //determines whether we should keep looping
	int loopCounter(0);
	while (recurse)
	{
		++loopCounter;
		recurse = false; //first assume nothing will be added this loop

		for (int index = 0; index < totalCells; ++index)
		{
			if (solvable[index] == loopCounter) //if the current index was added last loop
			{
				int indexDown = index / m_width;
				int indexAcross = index % m_width; //coords associated with this index
				if (indexDown == m_height - 1 || (*this)(indexDown + 1, indexAcross) == 'O')
				{
					for (int height = indexDown - 1; height >= 0 && m_grid[height * m_width + indexAcross] != 'O'; --height) //look up
					{
						if (solvable[height * m_width + indexAcross] == 0)
						{
							solvable[height * m_width + indexAcross] = loopCounter + 1; //add new point
							recurse = true; //now we know we need to loop again
						}
					}
				}
				if (indexDown == 0 || (*this)(indexDown - 1, indexAcross) == 'O')
				{
					for (int height = indexDown + 1; height < m_height && m_grid[height * m_width + indexAcross] != 'O'; ++height) //look down
					{
						if (solvable[height * m_width + indexAcross] == 0)
						{
							solvable[height * m_width + indexAcross] = loopCounter + 1;
							recurse = true;
						}
					}
				}
				if (indexAcross == m_width - 1 || (*this)(indexDown, indexAcross + 1) == 'O')
				{
					for (int width = indexAcross - 1; width >= 0 && m_grid[indexDown * m_width + width] != 'O'; --width) //look left
					{
						if (solvable[indexDown * m_width + width] == 0)
						{
							solvable[indexDown * m_width + width] = loopCounter + 1;
							recurse = true;
						}
					}
				}
				if (indexAcross == 0 || (*this)(indexDown, indexAcross - 1) == 'O')
				{
					for (int width = indexAcross + 1; width < m_width && m_grid[indexDown * m_width + width] != 'O'; ++width) //look right
					{
						if (solvable[indexDown * m_width + width] == 0)
						{
							solvable[indexDown * m_width + width] = loopCounter + 1;
							recurse = true;
						}
					}
				}
			}
		}
	}

	//count potential starting locations with highest minimum solving distance
	int totalSolvable(0);
	for (int index = 0; index < totalCells; ++index)
	{
		if (solvable[index] == loopCounter)
		{
			++totalSolvable;
		}
	}

	//now look at the potential starting locations with highest minimum solving distance and pick one at random
	std::vector<int> potStart(totalSolvable); //vector containing indices of potential starting locations
	int i(0);
	for (int index = 0; index < totalCells; ++index) //enumerate potential starting locations
	{
		if (solvable[index] == loopCounter)
		{
			potStart[i++] = index;
		}
	}
	//choose random starting position
	m_startLoc = potStart[rand() % totalSolvable];
	return true;
}