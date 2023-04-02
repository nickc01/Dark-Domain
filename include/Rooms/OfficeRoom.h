#pragma once

#include "Base/Room.h" //Used to gain access to the room definition for creating and executing rooms

//The office room that contains the first half of the code
class OfficeRoom : public Room
{
	//Called when the room starts
	void OnStart() override;

	//Called when a command is entered
	void OnCommand(std::string Command, std::vector<std::string> Arguments) override;

	//Called when the player inspects the room
	void Inspect() override;

	//Used to get the name of the room 
	std::string GetName() const override;
};