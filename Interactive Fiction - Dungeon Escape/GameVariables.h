#pragma once


namespace Variables
{
	//Whether the cell key has been found or not
	extern bool FoundCellKey;

	//Whether the cell is unlocked or not
	extern bool CellUnlocked;

	extern bool largeDoorUnlocked;

	extern int doorCode;

	extern bool foundNote;


	void Reset();
}