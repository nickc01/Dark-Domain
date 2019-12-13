#include "OfficeRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include "../gameEnums.h" //Used to gain access to common game enums
#include "../gameFunctions.h" //Used to gain access to common game variables
#include "../GameVariables.h" //Used to gain access to common game variables
#include <iostream> //Used to gain access to cout for printing to the console
#include "../Inventory.h" //Used to gain access to viewing and modifying the inventory
#include "HallwayEndRoom.h" //Used to gain access to the room definition for creating and executing rooms


using namespace std; //Used to prevent me from having to type "std::cout" everywhere

void OfficeRoom::OnStart()
{
	//Clear the screen
	system("cls");

	//Print the office intro
	cout << "You see what looks like an office room, perhaps where someone of importance used to work.\n";
	cout << "You see several shelves with lots of paperwork, A few chairs, and a computer desk.\n";
	cout << "The floor feels cold, wet, and is covered in mold.\n";
}

//Called when a command is entered
void OfficeRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	//If the "GO" command is entered
	if (Command == "GO")
	{
		//If the player wants to go "OUT"
		if (GoCommandShortcut(Arguments, { {"OUT","Go back out into the hallway"} }) == 0)
		{
			//Go to the hallway end room
			GoToRoom<HallwayEndRoom>();
		}
	}
	//If an invalid command was entered
	else
	{
		//Tell the player that an invalid command has been entered
		InvalidCommand();
	}
}

//Called when the player inspects the room
void OfficeRoom::Inspect()
{
	//If the not has not been found yet
	if (!Variables::foundNote)
	{
		//Tell how the player found the note
		cout << "You begin searching the room. In one corner of the room, you find some shelves with lots of papers on it. You pick some of them out, but their writing has been destroyed by moisture, so you leave it.\n";
		cout << "In the opposite corner, you see a chair, desk, and a computer system on top of it. You try powering it on, but it does not seem to work, even though it is plugged in.\n";
		cout << "You open one of the drawers inside the desk and you see a small ripped note.\n";
		cout << "You attempt to read what it says.\n";

		//Convert the door code to a string and remove the first two characters
		string firstPart = to_string(Variables::doorCode);
		firstPart.erase(0, 2);
		firstPart = string("__") + firstPart;

		//Tell the player what the code says
		cout << "It says: " << firstPart << "\n";

		//Add the note to the player's inventory
		Inventory::AddItem(string("Ripped Note with code : ") + firstPart);
		//Specify that the note has been found
		Variables::foundNote = true;
	}
	//If the note has already been found
	else
	{
		//Tell the player that they did not find anything useful
		cout << "After looking around, you don't find anything useful.\n";
	}
}

//Gets the name of the room
std::string OfficeRoom::GetName() const
{
	return "Office";
}
