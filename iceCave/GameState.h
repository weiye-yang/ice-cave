#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Cave.h"

class GameState
{
private:
	Cave m_cave;
	int m_playerDown;
	int m_playerAcross;
public:
	GameState(int height, int width)
		: m_cave(height,width), m_playerDown( m_cave.m_startLoc / width), m_playerAcross( m_cave.m_startLoc % width)
	{
		;
	}

	void randomize()
	{
		m_cave.randomize();
		reset();
	}

	void reset(); //puts player back at start
	void print() const; //print game state to console

	bool moveUp(); //move player in different directions, return whether this move won the game
	bool moveDown();
	bool moveLeft();
	bool moveRight();

private:
	bool victory() const; //whether the current position represents a win
};
#endif

