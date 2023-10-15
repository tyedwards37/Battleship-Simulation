/// @file main.cpp
/// @brief Simulates and plays the game.
/// @author Tyler Edwards - tk.edwards2003gmail.com

#include <iostream>   
#include "Game.h"   

int main()
{
	bool bPlay = true;
	Game game;

	while(bPlay)
	{
		game.play();

		std::cout << std::endl;
		char cPlay = 'n';
		std::cout << "Play another game? (y/n)" << std::endl;
		std::cin >> cPlay;
		if (cPlay == 'n')
		{
			bPlay = false;
		}
	}

	return 0;
}
