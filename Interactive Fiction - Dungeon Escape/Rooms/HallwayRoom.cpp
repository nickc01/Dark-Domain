#include "HallwayRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include "../gameFunctions.h" //Used to gain access to common game functions
#include <iostream> //Used to gain access to cout for printing to the console
#include "CellRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include "LargeDoorRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include "HallwayEndRoom.h" //Used to gain access to the room definition for creating and executing rooms

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

//Called when the room starts
void HallwayRoom::OnStart()
{
	//If the previous room was the cell room
	if (GetPreviousRoom()->GetName() != "Cell")
	{
		//Clear the screen
		system("cls");
	}
	//Tell the player that they are now in the hallway
	cout << "You are now in the hallway just outside of your cell. The hallway splits into two directions, left and right.\n\n";
	//If the previous room was the cell room
	if (GetPreviousRoom()->GetName() == "Cell")
	{
		//The the player how to use the go command
		cout << "Use the \"GO\" command to pick where you want to go";
	}
}

//Called when the player enters a command
void HallwayRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	//If the "GO" command was entered
	if (Command == "GO")
	{
		//Call the go command shortcut and see which room the player wants to go in
		switch (GoCommandShortcut(Arguments, { {"LEFT","Follow the hallway to the left"},{"RIGHT","Follow the hallway to the right"},{"BACK", "Go back into the cell you came out of"} }))
		{
			//If the player wants to go "LEFT"
		case 0:
			//Go to the large door room
			GoToRoom<LargeDoorRoom>();
			break;
			//If the player wants to go "RIGHT"
		case 1:
			//Go to the hallway end room
			GoToRoom<HallwayEndRoom>();
			break;
			//If the player wants to go "BACK"
		case 2:
			//Go back to the cell room
			GoToRoom<CellRoom>();
			break;
		}
	}
	//If an invalid command was entered
	else
	{
		//Tell the player an invalid command was entered
		InvalidCommand();
	}
}

//Used to get the name of the room
std::string HallwayRoom::GetName() const
{
	return "Hallway";
}
