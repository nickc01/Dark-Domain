#include "HallwayRoom.h"

#include "../gameEnums.h"
#include "../gameFunctions.h"
#include <iostream>
#include "CellRoom.h"
#include "LargeDoorRoom.h"
#include "OfficeRoom.h"

using namespace std;

void HallwayRoom::OnStart()
{
	//Clear the screen
	system("cls");
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);
	//Tell the player that they are now in the hallway
	cout << "You are now in the hallway just outside of your cell. The hallway splits into two directions, left and right.\n\n";
	//If the player originally came from the cell room
	if (GetPreviousRoom()->GetName() == "Cell")
	{
		//The the player how to use the go command
		cout << "Use the \"GO\" command to pick where you want to go";
	}
	//Set the text color back to normal
	SetColor(Color::Black, Color::BrightWhite);
}

void HallwayRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	if (Command == "GO")
	{
		//If no other arguments have been pass along with the command
		if (Arguments.size() == 0)
		{
			//Ask the player which way they want to go and present them their options
			cout << "In which direction do you want to go?\n";
			cout << "Valid options:\n";
			cout << "LEFT : Follow the hallway to the left\n";
			cout << "RIGHT : Follow the hallway to the right\n";
			cout << "BACK : Go back into the cell you came out of\n";
		}
		//If an argument has been passed alongside the command
		else
		{
			//If the LEFT argument has been entered
			if (Arguments[0] == "LEFT")
			{
				//Go to the large door room
				//return Room::LargeDoor;
				GoToRoom<LargeDoorRoom>();
			}
			//If the RIGHT argument has been entered
			else if (Arguments[0] == "RIGHT")
			{
				//Go to the office room
				//return Room::Office;
				GoToRoom<OfficeRoom>();
			}
			//If the BACK argument has been entered
			else if (Arguments[0] == "BACK")
			{
				//Go back to the Cell Room
				GoToRoom<CellRoom>();
				//return Room::Cell;
			}
			//If an unrecognized argument has been entered
			else
			{
				//Tell the player that an unrecognized argument has been entered
				InvalidCommand("Unrecognized place to go\n");
			}
		}
	}
	//If an invalid command has been entered
	else
	{
		//Tell the player that an invalid command has been entered
		InvalidCommand();
	}
}

std::string HallwayRoom::GetName() const
{
	return "Hallway";
}
