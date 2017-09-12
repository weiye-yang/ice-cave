// generates random ice cave puzzles a la pokemon, which you can play
// cave is always solvable, and usually nontrivial

#include "stdafx.h"
#include <iostream>
#include "Cave.h"
#include "GameState.h"

bool playCave(int height, int width)
{
	std::cout << "\nLegend: * = ice; O = rock; P = player; S = start; E = exit\n\n";

	GameState game(height, width);
	game.randomize();

	while (true)
	{
		game.print();

		char command;
		do 
		{
			std::cout << "Controls: wasd to move, r to restart, q to give up.\nEnter a command: ";
			std::cin >> command;
			std::cin.ignore(255, '\n');
		} while (!(command == 'w' || command == 'a' || command == 's' || command == 'd' || command == 'r' || command == 'q'));

		bool victory = false;
		switch (command)
		{
		case 'w':
			victory = game.moveUp();
			break;
		case 'a':
			victory = game.moveLeft();
			break;
		case 's':
			victory = game.moveDown();
			break;
		case 'd':
			victory = game.moveRight();
			break;
		case 'r':
			game.reset();
			break;
		case 'q':
			return false;
		}
		//did we win?
		if (victory)
		{
			game.print();
			return true;
		}

	}
	return false;
}

void printTitle() //title
{
	std::cout << "===ICE CAVE===\nBy Weiye Yang\nSlide around on the ice and try to get to the exit.\n\n";
}

int main()
{
	printTitle();

	int length(1), width(1);
	std::cout << "Please enter length and width of cave (both >1).\n";
	while (length < 2)
	{
		std::cout << "Length: ";
		std::cin >> length;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	}
	while (width < 2)
	{
		std::cout << "Width: ";
		std::cin >> width;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	}

	while (true)
	{
		bool victory = playCave(length, width);
		if (victory)
		{
			std::cout << "Nice one.\n";
		}

		char choice;
		do
		{
			std::cout << "Play again? (y/n): ";
			std::cin >> choice;
			std::cin.ignore(255, '\n');
		} while (!(choice == 'y' || choice == 'n'));
		if (choice == 'n') break;
	}

    return 0;
}

