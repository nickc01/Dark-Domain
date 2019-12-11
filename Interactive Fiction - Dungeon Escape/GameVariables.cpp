#include "GameVariables.h"
#pragma once


namespace Variables
{
	//Whether the cell key has been found or not
	bool FoundCellKey = false;

	//Whether the cell is unlocked or not
	bool CellUnlocked = false;

	int doorCode = 0;

	bool largeDoorUnlocked = false;

	bool foundNote = false;


	void Reset()
	{
		FoundCellKey = false;
		CellUnlocked = false;
		largeDoorUnlocked = false;
		foundNote = false;
		doorCode = 0;
	}
}