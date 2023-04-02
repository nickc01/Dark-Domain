#include "GameVariables.h" //Used to gain access to common game variables
#pragma once

//The namespace that stores all the variables. This is where the prototypes will be implemented
namespace Variables
{
	//Whether the cell key has been found or not
	bool FoundCellKey = false;

	//Whether the cell is unlocked or not
	bool CellUnlocked = false;

	//The code for escaping the dungeon
	int doorCode = 0;

	//Whether the large exit door is unlocked
	bool largeDoorUnlocked = false;

	//Whether the note in the office room has been found
	bool foundNote = false;

	//Whether the zombie has been defeated or not
	bool battledZombie = false;

	//The name of the player playing the game
	std::string PlayerName = "";


	//Resets the variables to their starting state
	void Reset()
	{
		//Reset the variables
		FoundCellKey = false;
		CellUnlocked = false;
		largeDoorUnlocked = false;
		foundNote = false;
		//Set the door code to a random number between 0000 and 9999
		doorCode = (rand() % 9000) + 1000;
		PlayerName = "";
		Variables::battledZombie = false;
	}
}