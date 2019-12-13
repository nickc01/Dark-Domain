#pragma once
#include <string> //Used to gain access to "std::string"
#include <vector> //Used to gain access to "std::vector"

//Destination room that is used by the "GO" command
struct RoomDestination final
{
	std::string Room; //The room to travel to
	std::string Description; //The description of the room

	//A constructor for easily creating the RoomDestination
	RoomDestination(std::string room,std::string description);
};

//The room base class
class Room
{
private:
	//Whether the room is quitting the game or not
	bool Quitting = false;
	//The next room to go to
	static Room* NextRoom;
	//Gets the next room
	static Room* PopNextRoom();
protected:
	//Goes to the next specified room
	template <typename RoomType>
	static void GoToRoom()
	{
		//If there is a next room already set
		if (NextRoom != nullptr)
		{
			//Delete it
			delete NextRoom;
		}
		//Store the next room
		NextRoom = new RoomType();
	}

	//Used to make the "GO" command easier
	static int GoCommandShortcut(std::vector<std::string> Arguments,std::vector<RoomDestination> Rooms);

	//Called when the room is starting up. Primarily used to print the intro of the room to the screen
	virtual void OnStart();

	//Called when the player wants to reprint the intro. By default, this will call the OnStart() function again, but this can be modified
	virtual void Recap();

	//Called when the player wants to inspect the room. Can be overridden
	virtual void Inspect();

	//Called whenever a command is entered.
	virtual void OnCommand(std::string Command, std::vector<std::string> Arguments) = 0;

	//Called when the room is finished and the game is moving to the next one
	virtual void OnFinish();

	//When called from the OnCommand() Method, it will cause the game to quit
	void Quit();

public:
	//Gets the previous room
	static const Room* GetPreviousRoom();
	//Gets the current room
	static const Room* GetCurrentRoom();
	//Resets the rooms
	static void Reset();
	//Executes the logic of the next room the player is going into
	static bool ExecuteNextRoom();

	//Gets the name of the room
	virtual std::string GetName() const = 0;
};