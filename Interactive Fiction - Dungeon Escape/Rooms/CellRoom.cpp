#include "CellRoom.h"
#include "../gameEnums.h"
#include "../gameFunctions.h"
#include <iostream>
#include "GameVariables.h"

using namespace std;

void CellRoom::OnStart()
{


	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);

	

	//If the previous room and the current room are set to the cell. This is only true if the game has just started up
	if (Room::GetPreviousRoom() == nullptr)
	{
		//Clear the screen
		system("cls");
		//Print the alternate intro. This is printed if the player has been here before
		cout << "You are now back in the cell you have woken up in\n";
	}
	else
	{
		//Print the main intro. This is only printed if the player just started in this room
		cout << "You have woken up in an old, mossy cell within a dark dungeon\n";
	}
	cout << "You have no idea how you got here, and there is nobody else in sight\n";

	//If the cell key has been found
	if (!Variables::FoundCellKey)
	{
		//Tell the player that the cell is locked
		cout << "The iron bars in your cell seem to be locked with a key\n";
	}
	//If the previous room and the current room are set to the cell. This is only true if the game has just started up
	if (Room::GetPreviousRoom() == nullptr)
	{
		//Tell the player that they can type "HELP" to get a list of commands used to navigate
		cout << "Type \"HELP\" at anytime to see a list of commands you can use\n";
	}
	//Set the text color back to normal
	SetColor(Color::Black, Color::BrightWhite);
}
