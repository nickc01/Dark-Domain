#include "OfficeRoom.h"
#include "../gameEnums.h"
#include "../gameFunctions.h"
#include "../GameVariables.h"
#include <iostream>
#include "../Inventory.h"
#include "HallwayRoom.h"


using namespace std;

void OfficeRoom::OnStart()
{
	//Clear the screen
	system("cls");
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);
	//Print the office introduction
	cout << "You slowly walk down the long hallway. After about a minute of traveling past other locked, empty jail cells, you find a door to an office. You head inside.\n";
	//Set the text back to normal
	SetColor(Color::Black, Color::BrightWhite);
}

void OfficeRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	if (Command == "GO")
	{
		//If no other arguments have been passed alongside the command
		if (Arguments.size() == 0)
		{
			//Ask the player where they want to go and present them their options
			cout << "Where do you want to go?\n";
			cout << "Valid options:\n";
			cout << "OUT : Go back out into the hallway and back to where your cell is\n";
		}
		//If the OUT argument has been passed
		else if (Arguments[0] == "OUT")
		{
			//Go to the hallway
			GoToRoom<HallwayRoom>();
		}
		//If no valid command has been entered
		else
		{
			//Tell the player that an invalid argument has been entered
			InvalidCommand("Unrecognized place to go\n");
		}
	}
	//If no valid command has been entered
	else
	{
		//Tell the player that an invalid command has been entered
		InvalidCommand();
	}
}

void OfficeRoom::Inspect()
{
	//If the not has not been found yet
	if (!Variables::foundNote)
	{
		//Set the text to blue
		SetColor(Color::Black, Color::LightBlue);

		//Set the door code to a random number between 0000 and 9999
		Variables::doorCode = (rand() % 9000) + 1000;
		//Tell how the player found the note
		cout << "You begin searching the room. In one corner of the room, you find some shelves with lots of papers on it. You pick some of them out, but their writing has been destroyed by moisture, so you leave it.\n";
		cout << "In the opposite corner, you see a chair, desk, and a computer system on top of it. You try powering it on, but it does not seem to work, even though it is plugged in.\n";
		cout << "You open one of the drawers inside the desk and you see a small note.\n";
		cout << "It has a four digit code on it:\n";
		cout << "\"" << Variables::doorCode << "\"\n";
		cout << "You put the note in your inventory\n";
		//Add the note to the player's inventory
		Inventory::AddItem(string("Note with the code: ") + to_string(Variables::doorCode));
		//Inventory.push_back(string("Note with the code: ") + to_string(doorCode));
		//Specify that the note has been found
		Variables::foundNote = true;
		//Set the text color back to normal
		SetColor(Color::Black, Color::BrightWhite);
	}
	//If the note has already been found
	else
	{
		//Tell the player that they did not find anything useful
		cout << "After looking around, you don't find anything useful.\n";
	}
}

std::string OfficeRoom::GetName() const
{
	return "Office";
}
