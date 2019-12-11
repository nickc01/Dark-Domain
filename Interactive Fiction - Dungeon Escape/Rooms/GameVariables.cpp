#include "GameVariables.h"
#pragma once


namespace Variables
{
	//Whether the cell key has been found or not
	bool FoundCellKey = false;

	//Whether the cell is unlocked or not
	bool CellUnlocked = false;


	void Reset()
	{
		FoundCellKey = false;
		CellUnlocked = false;
	}
}