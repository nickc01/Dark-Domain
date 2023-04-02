#include <Rooms/CellRoom.h> //Used to gain access to the room definition for creating and executing rooms
#include <gameFunctions.h> //Used to gain access to command game functions
#include <iostream> //Used to gain access to cout for printing to the console
#include <GameVariables.h> //Used to gain access to common game variables
#include <Inventory.h> //Used to gain access to viewing and modifying the inventory
#include <Rooms/HallwayRoom.h>//Used to gain access to the room definition for creating and executing rooms

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

//Called when the room starts
void CellRoom::OnStart()
{
	//If the previous room and the current room are set to the cell. This is only true if the game has just started up
	if (Room::GetPreviousRoom() != nullptr)
	{
		//Clear the screen
		ClearConsole();
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
}

//Called when a command is entered
void CellRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	//If the player has called the "GO" command
	if (Command == "GO")
	{
		//If the player want to go "OUT"
		if (Room::GoCommandShortcut(Arguments, { {"OUT","Leave the cell and out into the hallway"} }) == 0)
		{
			//If the cell is locked
			if (!Variables::CellUnlocked)
			{
				//If the player has a small key in their inventory
				if (Inventory::HasItem("Small Key"))
				{
					//Unlock the cell
					Variables::CellUnlocked = true;
					//Clear the console
					ClearConsole();
					//Tell the player that the cell has been unlocked
					cout << "You unlocked your cell using the small key that you found.\n";
					//Go to the hallway room
					GoToRoom<HallwayRoom>();
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
				ClearConsole();
				//Go to the hallway room
				GoToRoom<HallwayRoom>();
				//return Room::Hallway;
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

//Called when the player inspects the room
void CellRoom::Inspect()
{
	//If the cell key has not been found
	if (!Variables::FoundCellKey)
	{
		//Tell the player that they found a key
		cout << "After looking around the room for a while, you find a small key underneath some moss nearby the bars.\n";
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

//Returns the name of the room
std::string CellRoom::GetName() const
{
	return "Cell";
}
