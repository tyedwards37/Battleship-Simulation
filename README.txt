#READ.ME

Project: Battleship simulation
by Tyler Edwards
Added October 2023

Description: Mimics a game of battleship. A boat will be randomly placed in a grid and the user will be prompted to give coordinates to find it. They have a total of 10 attempts, or "torpedos" to locate it. When it is hit or the player runs out of "torpedos," it will ask the user if they would like to play again. If yes, it will reset the grid and the location of the boat. If no, the code will exit.  

Language: C++

Reason: For CPSC 298 (C++ Programming)

Successes: The project was very straightforward, but still rewarding in the end, despite using pretty rudimentary application.

Setbacks: My compiler struggeld with running the tuples despite it being clearly included in the files, so it took me a little while to find a work around for that.

Learned: how to work with tuples


/*
Commands:
g++ -std=c++11 *.cpp -o execute
./execute

Output:
|~|~|~|~|~|
|~|~|~|~|~|
|~|~|~|~|~|
|~|~|~|~|~|
Magazine: 10 torpedoes


Enter grid Coordinates (row, column) of torpedo target grid square
Please enter grid row number:
*/

- Started from in-class base code
