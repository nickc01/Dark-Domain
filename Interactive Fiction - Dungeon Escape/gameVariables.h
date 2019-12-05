#pragma once
#include "gameEnums.h"
#include <vector>
#include <string>


//--Variables--

//Whether the game is over or not
extern bool GameOver;

//The current room that the player is in
extern Room currentRoom;

//The previous room that the player was in
extern Room previousRoom;

//The player's inventory
extern std::vector<std::string> Inventory;

//Whether the cell key has been found or not
extern bool FoundCellKey;

//Whether the cell is unlocked or not
extern bool CellUnlocked;

//The code for the large door. This is needed in order to escape
extern int doorCode;

//Whether the large door is unlocked or not
extern bool largeDoorUnlocked;

//Whether the code note in the office has been found or not
extern bool foundNote;