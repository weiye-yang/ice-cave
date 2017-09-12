#include "stdafx.h"
#include "GameState.h"
#include "Cave.h"

void GameState::reset()
{
	m_playerDown = m_cave.m_startLoc / m_cave.m_width;
	m_playerAcross = m_cave.m_startLoc % m_cave.m_width;
}

void GameState::print() const
{
	for (int down = 0; down < m_cave.m_height; ++down)
	{
		for (int across = 0; across < m_cave.m_width; ++across)
		{
			char character;
			if (down == m_playerDown && across == m_playerAcross)
				character = 'P';
			else
				character = m_cave(down, across);

			std::cout << character << " ";
		}
		std::cout << "\n";
	}
}

bool GameState::victory() const
{
	return m_cave.m_exitLoc == m_playerDown * m_cave.m_width + m_playerAcross;
}

bool GameState::moveUp() //moves player up. stops if player hits a winning state. returns whether this move won the game.
{
	while (!(m_playerDown == 0 || m_cave(m_playerDown - 1, m_playerAcross) == 'O'))
	{
		--m_playerDown;
		if (victory())
			return true;
	}
	return false;
}
bool GameState::moveDown()
{
	while (!(m_playerDown == m_cave.m_height - 1 || m_cave(m_playerDown + 1, m_playerAcross) == 'O'))
	{
		++m_playerDown;
		if (victory())
			return true;
	}
	return false;
}
bool GameState::moveLeft()
{
	while (!(m_playerAcross == 0 || m_cave(m_playerDown, m_playerAcross - 1) == 'O'))
	{
		--m_playerAcross;
		if (victory())
			return true;
	}
	return false;
}
bool GameState::moveRight()
{
	while (!(m_playerAcross == m_cave.m_width - 1 || m_cave(m_playerDown, m_playerAcross + 1) == 'O'))
	{
		++m_playerAcross;
		if (victory())
			return true;
	}
	return false;
}