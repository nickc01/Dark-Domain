#include "HallwayEndRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include <iostream> //Used to gain access to cout for printing to the console
#include "OfficeRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include "HallwayRoom.h" //Used to gain access to the room definition for creating and executing rooms
#include "../gameFunctions.h" //Used to gain access to common game functions
#include "BattleRoom.h" //Used to gain access to the room definition for creating and executing rooms

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

//Called when the room starts
void HallwayEndRoom::OnStart()
{
	//Clear the screen
	system("cls");
	//If the previous room was the hallway room
	if (GetPreviousRoom()->GetName() == "Hallway")
	{
		//Tell the player how they got there and what awaits them
		cout << "You slowly walk down the hallway, passing locked cells as you go.\n";
		cout << "After a little while, you reach the end of the hallway.\n";
		cout << "There are two doors, one to your left and the other to your right.\n";
		cout << "The one on the right seems to lead to a small room.\n";
		cout << "The other looks like it goes down another long hallway.\n";
	}
	//If the previous room was anything else
	else
	{
		//Print the alternate intro
		cout << "You are now back in the hallway just ouside of the doors\n";
		cout << "The door on the right leads to a small room\n";
		cout << "The door on the left leads to another long hallway\n";
	}
}

//Called when the player enters a command
void HallwayEndRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	//If the "GO" command was entered
	if (Command == "GO")
	{
		//Call the go command shortcut and see which room the player wants to go in
		switch (GoCommandShortcut(Arguments, { {"LEFT","Go in the door to the left that leads to a hallway"},{"RIGHT","Go to the door on the right that leads to a room"},{"BACK", "Go back down the hallway"} }))
		{
			//If the player wants to go "LEFT"
		case 0:
			//Go to the zombie battle room
			GoToRoom<BattleRoom>();
			break;
			//If the player wants to go "RIGHT"
		case 1:
			//Go to the office room
			GoToRoom<OfficeRoom>();
			break;
			//If the player wants to go "BACK"
		case 2:
			//Go back to the hallway room
			GoToRoom<HallwayRoom>();
			break;
		}
	}
	//If an invalid command was entered
	else
	{
		//Tell the player that an invalid command was entered
		InvalidCommand();
	}
}

//Gets the name of the room
std::string HallwayEndRoom::GetName() const
{
	return "HallwayEnd";
}
