#include "Room.h" //Used to gain access to the room definition for creating and executing rooms
#include <exception> //Used to gain access to "std::exception" for throwing exceptions
#include <iostream> //Used to gain access to cout for printing to the console
#include "../../gameFunctions.h" //Used to gain access to common game functions
#include "../CellRoom.h" //Used to gain access to the room definition for creating and executing rooms

using namespace std; //Used to prevent me from having to type "std::cout" everywhere


//The next room to go to
Room* Room::NextRoom = nullptr;

//The previous room the player was at
Room* PreviousRoom = nullptr;

//The current room the player is in now
Room* CurrentRoom = nullptr;

//Quits the game
void Room::Quit()
{
	Quitting = true;
}

//Gets the previous room the player was at
const Room* Room::GetPreviousRoom()
{
	return PreviousRoom;
}

//Gets the current room the player is in now
const Room* Room::GetCurrentRoom()
{
	return NextRoom;
}

//Resets the room
void Room::Reset()
{
	//Reset the current, previous, and next room
	CurrentRoom = nullptr;
	PreviousRoom = nullptr;
	NextRoom = nullptr;
	//Set the next room to the cell room
	GoToRoom<CellRoom>();
}

//Gets the next room to go to
Room* Room::PopNextRoom()
{
	//If there is no next room
	if (NextRoom == nullptr)
	{
		//Return null
		return nullptr;
	}
	//If there is a next room
	else
	{
		//Get the next room
		auto storage = NextRoom;
		//Set the next room variable to null
		NextRoom = nullptr;
		//Return the room
		return storage;
	}
}

//Executes the logic of the next room
bool Room::ExecuteNextRoom()
{
	//If there is a previous room
	if (PreviousRoom != nullptr)
	{
		//Delete it
		delete PreviousRoom;
	}
	//If there is a current room
	if (CurrentRoom != nullptr)
	{
		//Set it to be the previous room
		PreviousRoom = CurrentRoom;
	}
	//Get the next room
	auto nextRoom = PopNextRoom();
	//If there is no next room set
	if (nextRoom == nullptr)
	{
		//Quit the function
		return false;
	}
	//Set the current room to the next room
	CurrentRoom = nextRoom;
	//Set the color to light blue
	SetColor(Color::Black, Color::LightBlue);
	//Start the room. This will print the rooms introduction
	CurrentRoom->OnStart();
	//Reset the color
	SetColor(Color::Black, Color::BrightWhite);
	
	//The command input list. Used to retrieve commands from the player as well as their arguments
	vector<string> commandInput;

	//Repeatedly ask the player for commands to input. This runs until the "QUIT" command is inputted.
	while (GetCommand(commandInput))
	{
		//Get the command entered by the player
		string command = commandInput[0];
		//Remove it from the command list. The command list now consists of just arguments
		commandInput.erase(commandInput.begin());

		//Set the color to light blue
		SetColor(Color::Black, Color::LightBlue);
		//If the command is "INSPECT"
		if (command == "INSPECT")
		{
			//Inspect the room
			CurrentRoom->Inspect();
		}
		//If the command is "RECAP"
		else if (command == "RECAP")
		{
			//Print a recap of the current room
			CurrentRoom->Recap();
		}
		//If any other command is entered
		else
		{
			//Forward it to the room's command handler
			CurrentRoom->OnCommand(command, commandInput);
		}
		//Reset the colors
		SetColor(Color::Black, Color::BrightWhite);

		//If a next room is set or the room wants to quit the game
		if (NextRoom != nullptr || CurrentRoom->Quitting)
		{
			//Break out of the loop
			break;
		}
	}
	//Set the color to blue
	SetColor(Color::Black, Color::LightBlue);
	//Finish up the room
	CurrentRoom->OnFinish();
	//Reset the color
	SetColor(Color::Black, Color::BrightWhite);
	//Return whether the room wants to quit or not
	return !CurrentRoom->Quitting;
}

//Used to make the "GO" command easier
int Room::GoCommandShortcut(std::vector<std::string> Arguments, std::vector<RoomDestination> Rooms)
{
	//If no other arguments were passed in
	if (Arguments.size() == 0)
	{
		//Ask the player where they want to go and present them their options
		cout << "Where do you want to go?\n";
		cout << "Valid options:\n";
		//For each room
		for (auto& room : Rooms)
		{
			//Print out the room and it's description
			cout << room.Room << " : " << room.Description << "\n";
		}
		return -1;
	}
	//If an argument was passed in
	else
	{
		//Loop over all the possible rooms to go to
		for (int i = 0; i < Rooms.size(); i++)
		{
			//If the argument matches the room name
			if (Arguments[0] == Rooms[i].Room)
			{
				//Return the index
				return i;
			}
		}
	}
	//If an invalid destination was entered, tell the player that this is an invalid place to go
	InvalidCommand("Unrecognized place to go\n");
	return -2;
}

//Called when the room starts. Does nothing by default, but can be overridden
void Room::OnStart()
{

}

//Prints a recap of the current room. Calls the OnStart() method by default
void Room::Recap()
{
	OnStart();
}

//Called when the player inspects the room. The default behaviour is to tell the player they found nothing useful
void Room::Inspect()
{
	//Tell the player that they did not find anything useful
	std::cout << "After looking around, you don't find anything useful.\n";
}

//Called when the room is finished. By default, it does nothing
void Room::OnFinish()
{

}

//A constructor for easily creating a RoomDestination for the GO command
RoomDestination::RoomDestination(std::string room, std::string description) : Room(room), Description(description) {}
