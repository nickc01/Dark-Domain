#include "CellRoom.h"
#include "../gameEnums.h"
#include "../gameFunctions.h"
#include <iostream>
#include "../GameVariables.h"
#include "../Inventory.h"
#include "HallwayRoom.h"

using namespace std;

void CellRoom::OnStart()
{
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);
	//If the previous room and the current room are set to the cell. This is only true if the game has just started up
	if (Room::GetPreviousRoom() != nullptr)
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


void CellRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	if (Command == "GO")
	{
		//If there are no arguments passed along with the command
		if (Arguments.size() == 0)
		{
			//Ask the player where they want to go to, and list the valid options
			cout << "Where do you want to go?\n";
			cout << "Valid options:\n";
			cout << "OUT : Leave the cell and out into the hallway\n";
		}
		//If the "OUT" argument has been specified
		else if (Arguments[0] == "OUT")
		{
			//If the cell is locked
			if (!Variables::CellUnlocked)
			{
				//Find the key in the player's inventory
				//auto index = find(Inventory.begin(), Inventory.end(), "Small Key");
				//If it has been found
				//if (index < Inventory.end())
				if (Inventory::HasItem("Small Key"))
				{
					//Unlock the cell
					Variables::CellUnlocked = true;
					//Clear the console
					system("cls");
					//Set the text color to blue
					SetColor(Color::Black, Color::LightBlue);
					//Tell the player that the cell has been unlocked
					cout << "You unlocked your cell using the small key that you found.\n";
					//Set the text color back to normal
					SetColor(Color::Black, Color::BrightWhite);
					//Go to the hallway room
					GoToRoom<HallwayRoom>();
					//return Room::Hallway;
				}
				//If the key has not been found in the inventory
				else
				{
					//Tell the player that they can't leave since the cell is still locked
					cout << "You aren't able to leave the cell. The cell is locked. You might need to find a key.\n";
				}
			}
			//If the cell is unlocked
			else
			{
				//Clear the screen
				system("cls");
				//Go to the hallway room
				GoToRoom<HallwayRoom>();
				//return Room::Hallway;
			}
		}
		//If an invalid argument has been passed
		else
		{
			//Tell the player that an invalid argument has been passed
			InvalidCommand("Unrecognized place to go\n");
		}
	}
	else
	{
		//Tell the player that an invalid command has been entered
		InvalidCommand();
	}
}

void CellRoom::Inspect()
{
	//If the cell key has not been found
	if (!Variables::FoundCellKey)
	{
		//Set the text color to blue
		SetColor(Color::Black, Color::LightBlue);
		//Tell the player that they found a key
		cout << "After looking around the room for a while, you find a small key underneath some moss nearby the bars.\n";
		//Tell the player that the key has been added to their inventory
		cout << "A key has been added to your inventory\n";
		//Set the color back to normal
		SetColor(Color::Black, Color::BrightWhite);
		//Specify that the key has been found
		Variables::FoundCellKey = true;
		//Add the key to the inventory
		//Inventory.push_back("Small Key");
		Inventory::AddItem("Small Key");
	}
	//If the key has been found
	else
	{
		//Tell the player that there is nothing more interesting in the room
		cout << "After looking around, you don't find anything useful.\n";
	}
}

std::string CellRoom::GetName() const
{
	return "Cell";
}
