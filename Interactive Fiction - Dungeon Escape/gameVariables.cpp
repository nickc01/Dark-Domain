#include "gameVariables.h"

//--Variables--

//Whether the game is over or not
bool GameOver = false;

//The current room that the player is in
Room currentRoom;

//The previous room that the player was in
Room previousRoom;

//The player's inventory
std::vector<std::string> Inventory;

//Whether the cell key has been found or not
bool FoundCellKey = false;

//Whether the cell is unlocked or not
bool CellUnlocked = false;

//The code for the large door. This is needed in order to escape
int doorCode = 1234;

//Whether the large door is unlocked or not
bool largeDoorUnlocked = false;

//Whether the code note in the office has been found or not
bool foundNote = false;