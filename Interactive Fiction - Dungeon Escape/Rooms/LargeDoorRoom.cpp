#include "LargeDoorRoom.h"
#include "../gameEnums.h"
#include "../gameFunctions.h"
#include "../GameVariables.h"
#include <iostream>
#include "HallwayRoom.h"

using namespace std;

void LargeDoorRoom::OnStart()
{
	//Clear the screen
	system("cls");
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);
	//Print the description of the door and how to enter the code for the lock
	cout << "You now find yourself in front of a large door. You see some light around the edges, so you assume it's the way out.\n";
	cout << "The door however is locked. You notice that there is another lock on the door. But this time it seems to be a numerical lock.\n";
	cout << "You need to input the correct 4 digit password into the lock in order to open the door.\n";
	cout << "Type in the command \"CODE\" to try out a numerical code on the lock.\n";
	//Set the text color back to normal
	SetColor(Color::Black, Color::BrightWhite);
}

void LargeDoorRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	if (Command == "GO")
	{
		//If no other arguments have been passed alongside the command
		if (Arguments.size() == 0)
		{
			//Ask the player where they want to go and present them their options
			cout << "Where do you want to go?\n";
			cout << "Valid options:\n";
			cout << "OUT : Go out the large door and escape.\n";
			cout << "BACK : Go back through the hallway just outside your cell.\n";
		}
		//If an argument has been entered alongside the command
		else
		{
			//If the OUT argument has been entered
			if (Arguments[0] == "OUT")
			{
				//If the door has been unlocked
				if (Variables::largeDoorUnlocked)
				{
					//Clear the screen
					system("cls");
					//Set the text color to yellow
					SetColor(Color::Black, Color::LightYellow);
					//Tell the player that they are free and won the game
					cout << "You have escaped the old prison and you are now free!\n";
					//Set the text color back to normal
					SetColor(Color::Black, Color::BrightWhite);
					//Set the room to None, signifying the end of the game
					Quit();
					//return RoomEnum::None;
				}
			}
			//If the BACK argument has been entered
			else if (Arguments[0] == "BACK")
			{
				//Go back to the hallway room
				GoToRoom<HallwayRoom>();
				//return RoomEnum::Hallway;
			}
			//If no valid argument has been passed
			else
			{
				//Tell the player that an invalid argument has been passed
				InvalidCommand("Unrecognized place to go\n");
			}
		}
	}
	//If the "CODE" command has been entered
	else if (Command == "CODE")
	{
		//If the large door is locked
		if (!Variables::largeDoorUnlocked)
		{
			//If no arguments have been passed alongside the command
			if (Arguments.size() == 0)
			{
				//Tell the player to enter a 4 digit code
				cout << "Enter the 4 digit code:\n";
				//Get a number from the player
				int number = GetNumber();
				//If the number matches the door code
				if (number == Variables::doorCode)
				{
					//Set the text to yellow
					SetColor(Color::Black, Color::LightYellow);
					//Tell the player that the door has been unlocked!
					cout << "The door has now been unlocked! You can now escape!\n";
					//Set the text back to normal
					SetColor(Color::Black, Color::LightBlue);
					//Unlock the door
					Variables::largeDoorUnlocked = true;
				}
				//If the number did not match the door code
				else
				{
					//Tell the player that the code is invalid
					cout << "The code entered was invalid\n";
				}
			}
			//If an argument has been passed alongside the command
			else
			{
				int code = 0;
				//Convert the argument into a number and see if that number matches the door code
				if (TryConvertToNumber(Arguments[0], code) && code == Variables::doorCode)
				{
					//If it matches, tell the player that the door is unlocked
					cout << "The door has now been unlocked! You can now escape!\n";
					//Unlock the door
					Variables::largeDoorUnlocked = true;
				}
				//If the number does not match the door code
				else
				{
					//Tell the player that the code is invalid
					InvalidCommand("The code entered was invalid\n");
				}
			}
		}
		//If the door is unlocked
		else
		{
			//Tell the player that the door is already unlocked
			cout << "The door is already unlocked\n";
		}
	}
	//If no valid command has been entered
	else
	{
		//Tell the player that an invalid command has been entered
		InvalidCommand();
	}
}

std::string LargeDoorRoom::GetName() const
{
	return "LargeDoor";
}
