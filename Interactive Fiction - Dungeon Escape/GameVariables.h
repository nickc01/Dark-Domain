#pragma once
#include <string> //Used to gain access to "std::string"

//A namespace containing all the variables used throughout the game. The extern keyword is to prototype the variables
namespace Variables
{
	//Whether the cell key has been found or not
	extern bool FoundCellKey;

	//Whether the cell is unlocked or not
	extern bool CellUnlocked;

	//Whether the large exit door is unlocked
	extern bool largeDoorUnlocked;

	//The code to open the large door
	extern int doorCode;

	//Whether the note in the office room was found or not
	extern bool foundNote;

	//Whether the zombie has been defeated or not
	extern bool battledZombie;

	//The name of the player playing the game
	extern std::string PlayerName;

	//Resets the variables back to their starting states
	void Reset();
}