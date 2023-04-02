#pragma once
#include "Base/Room.h" //Used to gain access to the room definition for creating and executing rooms

//The room with the large escape door
class LargeDoorRoom : public Room
{
	//Called when the room starts
	void OnStart() override;

	//Called when a command is entered
	void OnCommand(std::string Command, std::vector<std::string> Arguments) override;

	//Used to get the name of the room 
	std::string GetName() const override;
};