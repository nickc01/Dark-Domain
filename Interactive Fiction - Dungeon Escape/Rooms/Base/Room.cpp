#include "Room.h"
#include <exception>
#include <iostream>
#include "../../gameFunctions.h"
#include "../CellRoom.h"

using namespace std;


Room* Room::NextRoom = nullptr;

Room* PreviousRoom = nullptr;
Room* CurrentRoom = nullptr;


/*class TestRoom : public Room
{
	std::string GetName() const override
	{
		return "";
	}

	void OnStart() override
	{

	}

	void OnCommand(std::string Command, std::vector<std::string> Arguments) override
	{

	}

	void OnFinish() override
	{

	}
};*/

void Room::Quit()
{
	Quitting = true;
}

const Room* Room::GetPreviousRoom()
{
	return PreviousRoom;
}

const Room* Room::GetCurrentRoom()
{
	return NextRoom;
}

void Room::Reset()
{
	CurrentRoom = nullptr;
	PreviousRoom = nullptr;
	NextRoom = nullptr;
	GoToRoom<CellRoom>();
}

Room* Room::PopNextRoom()
{
	if (NextRoom == nullptr)
	{
		return nullptr;
	}
	else
	{
		auto storage = NextRoom;
		NextRoom = nullptr;
		return storage;
	}
}

bool Room::ExecuteNextRoom()
{
	if (PreviousRoom != nullptr)
	{
		delete PreviousRoom;
	}
	if (CurrentRoom != nullptr)
	{
		PreviousRoom = CurrentRoom;
	}
	auto nextRoom = PopNextRoom();
	if (nextRoom == nullptr)
	{
		return false;
	}
	CurrentRoom = nextRoom;
	CurrentRoom->OnStart();
	
	//The command input list. Used to retrieve commands from the player as well as their arguments
	vector<string> commandInput;

	//Repeatedly ask the player for commands to input. This runs until the "QUIT" command is inputted.
	while (GetCommand(commandInput))
	{
		string command = commandInput[0];
		commandInput.erase(commandInput.begin());

		if (command == "INSPECT")
		{
			CurrentRoom->Inspect();
		}
		else if (command == "RECAP")
		{
			CurrentRoom->Recap();
		}
		else
		{
			CurrentRoom->OnCommand(command, commandInput);
		}

		if (NextRoom != nullptr || CurrentRoom->Quitting)
		{
			break;
		}
	}
	CurrentRoom->OnFinish();
	return !CurrentRoom->Quitting;
}

void Room::OnStart()
{

}

void Room::Recap()
{
	OnStart();
}

void Room::Inspect()
{
	//Tell the player that they did not find anything useful
	std::cout << "After looking around, you don't find anything useful.\n";
}

void Room::OnFinish()
{

}
