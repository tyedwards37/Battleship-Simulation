/// @file Game.cpp
/// @brief DEfines the rules of the game.
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#include <iostream> 
#include <tuple>    
#include <cmath>   
#include <random>  
#include <ctime>    

#include "Game.h"   

//#define TEST  // enable test mode functionality 
//#define DIAG  // enable diagnostic output 

// Defines the base case for a "Game" object.
// @input N/A
// @output N/A
Game::Game() : m_nGridRows(k_nGridRowsDefault), m_nGridColumns(k_nGridColumnsDefault), m_iRowBoat(0), m_iColumnBoat(0), m_nTorpedoes(k_nMaxTorpedoes)
{
	initializeGrid();
}

// Creates the grid that the game will be played on
// @input N/A
// @output N/A
void Game::initializeGrid()
{
	for (int iRow = 0; iRow < this->m_nGridRows; iRow++)
	{
		for (int iColumn = 0; iColumn < this->m_nGridColumns; iColumn++)
		{
			a_cGrid[iRow][iColumn] = '~';
		}
	}
	return;
}

// Prints the grid 
// @input bool
// @output N/A
void Game::displayGrid(bool bShowBoat) 
{
	for (int iRow = 0; iRow < this->m_nGridRows; ++iRow)
	{
		std::cout << "|";
		for (int iColumn = 0; iColumn < this->m_nGridColumns; ++iColumn)
		{
			if ('V' == this->a_cGrid[iRow][iColumn])
			{
				if (bShowBoat)
				{
					std::cout << "V" << "|";
				}
				else
			       	{
					std::cout << "~" << "|";
				}
			}
			else
		       	{
				std::cout << this->a_cGrid[iRow][iColumn] << "|";
			}
		}
		std::cout << std::endl;
	}
	return;
}

// "Fires" a torpedo at the grid location that the player specifies
// @input N/A
// @output tuple<int, int>
std::tuple<int, int>  Game::fireTorpedo()
{
	int iRow = 0;
	int iColumn = 0;

	this->m_nTorpedoes--;

	std::cout << "Enter grid Coordinates (row, column) of torpedo target grid square" << std::endl;
	std::tie(iRow, iColumn) = promptForGridCoord();

	this->a_cGrid[iRow][iColumn] = '*';

	std::tuple<int, int> tupleTorpedoCoord(iRow, iColumn);
	return tupleTorpedoCoord;
}

// Places the boat at a random location on the grid
// @input N/A
// @output N/A
void Game::placeBoatRandomly()
{
	std::random_device randomDevice;
	std::default_random_engine randomNumbreGenerator(randomDevice());
	std::uniform_int_distribution<int> uniformIntegerDistributionRows(0, (this->m_nGridRows - 1));

	this->m_iRowBoat = uniformIntegerDistributionRows(randomNumbreGenerator);


	std::uniform_int_distribution<int> uniformIntegerDistributionColumns(0, (this->m_nGridColumns - 1));
	this->m_iColumnBoat = uniformIntegerDistributionColumns(randomNumbreGenerator);
	this->a_cGrid[m_iRowBoat][m_iColumnBoat] = 'V';

#if defined(DIAG)
	std::cout << "DIAG: Boat location (Row/Column): " << this->m_iRowBoat << "; " << this->m_iColumnBoat << std::endl;
#endif

}

// Allows the user to place the boat manually on the grid for testing
// @input N/A
// @output N/A
void Game::placeBoat()
{
	int iRow = 0;
	int iColumn = 0;

	std::cout << "Enter the grid square coordinates  (row, column) of target boat" << std::endl;

	std::tie(iRow, iColumn) = promptForGridCoord();

	this->a_cGrid[iRow][iColumn] = 'V';
	this->m_iRowBoat = iRow;
	this->m_iColumnBoat = iColumn;
	return;
}

// Checks if the player has hit the boat
// @input int, int
// @output bool
bool Game::isOnTarget(int iRow, int iColumn)
{
	bool bHit = false; 

	if ((this->m_iRowBoat == iRow) && (this->m_iColumnBoat == iColumn))
	{
		bHit = true;
	}

	return bHit;
}

// Prompts the user if they were within one space of the boat
// @input int, int
// @output bool
bool Game::isCloseToTarget(int iRow, int iColumn)
{
	bool bClose = false;

	if ((std::abs(iRow - this->m_iRowBoat) <= 1) && (std::abs(iColumn - this->m_iColumnBoat) <= 1))
	{
		bClose = true;
	}

	return bClose;
}

// Displays an 'X' if the user has hit the boat
// @input N/A
// @output N/A
void Game::showSunk()
{
	this->a_cGrid[this->m_iRowBoat][this->m_iColumnBoat] = 'X';
	return;
}

// Prompts the player for grid coordinates
// @input N/A
// @output tuple<int, int>
std::tuple<int, int> Game::promptForGridCoord()
{
	int iRow = 0;
	int iColumn = 0;

  	std::cout << "Please enter grid row number: ";
	std::cin >> iRow;

	while(iRow < 0 || iRow > 3)
	{
		std::cout << "Please enter a valid grid row number: ";
		std::cin >> iRow;
	}

	std::cout << "Please enter grid column number: ";
	std::cin >> iColumn;

	while(iColumn < 0 || iColumn > 4)
	{
		std::cout << "Please enter a valid grid column number: ";
		std::cin >> iColumn;
	}

	std::tuple<int, int> tupleCoord = std::make_tuple(iRow, iColumn);

	return tupleCoord;
}

// Simulates the game
// @input N/A
// @output N/A
void Game::play()
{
	int iRow = 0;
	int iColumn = 0;

	this->reset();         
	this->displayGrid(false); 
	std::cout << "Magazine: " << this->m_nTorpedoes << " torpedoes" << std::endl;
	std::cout << std::endl;

	bool bSunk = false;
	while ((!bSunk) && (this->m_nTorpedoes > 0))
	{
		std::cout << std::endl;
		std::tie(iRow, iColumn) = this->fireTorpedo();

		if (this->isOnTarget(iRow, iColumn))
		{
			this->showSunk();
			this->displayGrid(false);
			std::cout << "Hit!  Kaboom!" << std::endl;
			std::cout << "Victory!" << std::endl;
			bSunk = true;
		}
		else if (this->isCloseToTarget(iRow, iColumn))
		{
			this->displayGrid(false);
			std::cout << "Location row: " << iRow << "; column: " << iColumn << " is close!" << std::endl;
		}
		else
		{
			this->displayGrid(false);
			std::cout << "Location row: " << iRow << "; column: " << iColumn << " is a miss." << std::endl;
		}

		if (!bSunk)
		{
			std::cout << "Magazine: " << this->m_nTorpedoes << " torpedoes" << std::endl;
		}

		if (this->m_nTorpedoes == 0 && !bSunk)
		{
			this->displayGrid(true);
			std::cout << "Torpedoes expended" << std::endl;
			std::cout << "Game over" << std::endl;
		}
	}
}

// Creates a new grid and starts the game from scratch
// @input N/A
// @output N/A
void Game::reset()
{
	this->initializeGrid();
#if defined TEST
	// test gameplay
	this->placeBoat();
#else
	// normal gameplay
	this->placeBoatRandomly();
#endif
	this->m_nTorpedoes = Game::k_nMaxTorpedoes;
}
