#pragma once
#include "Base/Room.h" //Used to gain access to the room definition for creating and executing rooms

//The room for the hallway just outside the cell
class HallwayRoom : public Room
{
	//Called when the room starts
	void OnStart() override;

	//Called when a command is entered
	void OnCommand(std::string Command, std::vector<std::string> Arguments) override;

	//Used to get the name of the room 
	std::string GetName() const override;
};