#pragma once
#include <string>
#include <vector>
#include <memory>




class Room
{
private:
	bool Quitting = false;
	static Room* NextRoom;
	static Room* PopNextRoom();
protected:
	template <typename RoomType>
	static void GoToRoom()
	{
		if (NextRoom != nullptr)
		{
			delete NextRoom;
		}
		NextRoom = new RoomType();
	}

	//When called from the OnCommand() Method, it will cause the game to quit
	void Quit();

public:
	static const Room* GetPreviousRoom();
	static const Room* GetCurrentRoom();
	static void Reset();
	static bool ExecuteNextRoom();

	virtual std::string GetName() const = 0;

	//Called when the room is starting up. Primarily used to print the intro of the room to the screen
	virtual void OnStart();

	//Called when the player wants to reprint the intro. By default, this will call the OnStart() function again, but this can be modified
	virtual void Recap();

	//Called when the player wants to inspect the room. Can be overridden
	virtual void Inspect();

	//Called whenever a command is entered.
	virtual void OnCommand(std::string Command,std::vector<std::string> Arguments) = 0;

	//Called when the room is finished and the game is moving to the next one
	virtual void OnFinish();
};