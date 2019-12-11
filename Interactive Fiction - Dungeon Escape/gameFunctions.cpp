#include "gameFunctions.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN //This is used to prevent importing extra windows features we don't need
#include <Windows.h> //Used to gain access to changing the color of the console

#include "Inventory.h"

using namespace std;

//--Variables--

//The current room that the player is in
//RoomEnum currentRoom;

//The previous room that the player was in
//RoomEnum previousRoom;

//The player's inventory
//std::vector<std::string> Inventory;

//Whether the cell key has been found or not
//bool FoundCellKey = false;

//Whether the cell is unlocked or not
//bool CellUnlocked = false;

//The code for the large door. This is needed in order to escape
//int doorCode = 1234;

//Whether the large door is unlocked or not
//bool largeDoorUnlocked = false;

//Whether the code note in the office has been found or not
//bool foundNote = false;

//Prints the introduction of the cell room the player spawns in
/*void CellIntro()
{
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);

	//If the previous room and the current room are set to the cell. This is only true if the game has just started up
	if (!(previousRoom == RoomEnum::Cell && currentRoom == RoomEnum::Cell))
	{
		//Clear the screen
		system("cls");
		//Print the alternate intro. This is printed if the player has been here before
		cout << "You are now back in the cell you have woken up in\n";
	}
	else
	{
		//Print the main intro. This is only printed if the player just started in this room
		cout << "You have woken up in an old, mossy cell within a dark dungeon\n";
	}
	cout << "You have no idea how you got here, and there is nobody else in sight\n";

	//If the cell key has been found
	if (!FoundCellKey)
	{
		//Tell the player that the cell is locked
		cout << "The iron bars in your cell seem to be locked with a key\n";
	}
	//If the previous room and the current room are set to the cell. This is only true if the game has just started up
	if (previousRoom == RoomEnum::Cell && currentRoom == RoomEnum::Cell)
	{
		//Tell the player that they can type "HELP" to get a list of commands used to navigate
		cout << "Type \"HELP\" at anytime to see a list of commands you can use\n";
	}
	//Set the text color back to normal
	SetColor(Color::Black, Color::BrightWhite);
}


//Does the main logic for the cell room
RoomEnum DoCellRoom()
{
	//Print the cell intro
	CellIntro();

	//The command input list. Used to retrieve commands from the player as well as their arguments
	vector<string> commandInput;

	//Repeatedly ask the player for commands to input. This runs until the "QUIT" command is inputted.
	while (GetCommand(commandInput))
	{
		//If the inspect command has been inputted
		if (commandInput[0] == "INSPECT")
		{
			//If the cell key has not been found
			if (!FoundCellKey)
			{
				//Set the text color to blue
				SetColor(Color::Black, Color::LightBlue);
				//Tell the player that they found a key
				cout << "After looking around the room for a while, you find a small key underneath some moss nearby the bars.\n";
				//Tell the player that the key has been added to their inventory
				cout << "A key has been added to your inventory\n";
				//Set the color back to normal
				SetColor(Color::Black, Color::BrightWhite);
				//Specify that the key has been found
				FoundCellKey = true;
				//Add the key to the inventory
				//Inventory.push_back("Small Key");
				Inventory::AddItem("Small Key");
			}
			//If the key has been found
			else
			{
				//Tell the player that there is nothing more interesting in the room
				cout << "After looking around, you don't find anything useful.\n";
			}
		}
		//If the GO command has been inputted
		else if (commandInput[0] == "GO")
		{
			//If there are no arguments passed along with the command
			if (commandInput.size() == 1)
			{
				//Ask the player where they want to go to, and list the valid options
				cout << "Where do you want to go?\n";
				cout << "Valid options:\n";
				cout << "OUT : Leave the cell and out into the hallway\n";
			}
			//If the "OUT" argument has been specified
			else if (commandInput[1] == "OUT")
			{
				//If the cell is locked
				if (!CellUnlocked)
				{
					//Find the key in the player's inventory
					//auto index = find(Inventory.begin(), Inventory.end(), "Small Key");
					//If it has been found
					//if (index < Inventory.end())
					if (Inventory::HasItem("Small Key"))
					{
						//Unlock the cell
						CellUnlocked = true;
						//Clear the console
						system("cls");
						//Set the text color to blue
						SetColor(Color::Black, Color::LightBlue);
						//Tell the player that the cell has been unlocked
						cout << "You unlocked your cell using the small key that you found.\n";
						//Set the text color back to normal
						SetColor(Color::Black, Color::BrightWhite);
						//Go to the hallway room
						return RoomEnum::Hallway;
					}
					//If the key has not been found in the inventory
					else
					{
						//Tell the player that they can't leave since the cell is still locked
						cout << "You aren't able to leave the cell. The cell is locked. You might need to find a key.\n";
					}
				}
				//If the cell is unlocked
				else
				{
					//Clear the screen
					system("cls");
					//Go to the hallway room
					return RoomEnum::Hallway;
				}
			}
			//If an invalid argument has been passed
			else
			{
				//Tell the player that an invalid argument has been passed
				InvalidCommand("Unrecognized place to go\n");
			}
		}
		//If the recap command has been inputted
		else if (commandInput[0] == "RECAP")
		{
			//Reprint the cell introduction
			CellIntro();
		}
		//If an invalid command has been entered
		else
		{
			//Tell the player that an invalid command has been entered
			InvalidCommand();
		}
	}
	//Return no room if the "QUIT" command has been entered. This signifies the end of the game
	return RoomEnum::None;
}

//Prints the introduction for the hallway
void HallwayIntro()
{
	//Clear the screen
	system("cls");
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);
	//Tell the player that they are now in the hallway
	cout << "You are now in the hallway just outside of your cell. The hallway splits into two directions, left and right.\n\n";
	//If the player originally came from the cell room
	if (previousRoom != RoomEnum::Cell)
	{
		//The the player how to use the go command
		cout << "Use the \"GO\" command to pick where you want to go";
	}
	//Set the text color back to normal
	SetColor(Color::Black, Color::BrightWhite);
}

//Does the main logic for the hallway
RoomEnum DoHallway()
{
	//Print the hallway intro
	HallwayIntro();


	//The command input list. Used to retrieve commands from the player as well as their arguments
	vector<string> commandInput;

	//Repeatedly ask the player for commands to input. This runs until the "QUIT" command is inputted.
	while (GetCommand(commandInput))
	{
		//If the inspect command has been entered
		if (commandInput[0] == "INSPECT")
		{
			//Tell the player that they did not find anything useful
			cout << "After looking around, you don't find anything useful.\n";
		}
		//If the go command has been entered
		else if (commandInput[0] == "GO")
		{
			//If no other arguments have been pass along with the command
			if (commandInput.size() == 1)
			{
				//Ask the player which way they want to go and present them their options
				cout << "In which direction do you want to go?\n";
				cout << "Valid options:\n";
				cout << "LEFT : Follow the hallway to the left\n";
				cout << "RIGHT : Follow the hallway to the right\n";
				cout << "BACK : Go back into the cell you came out of\n";
			}
			//If an argument has been passed alongside the command
			else
			{
				//If the LEFT argument has been entered
				if (commandInput[1] == "LEFT")
				{
					//Go to the large door room
					return RoomEnum::LargeDoor;
				}
				//If the RIGHT argument has been entered
				else if (commandInput[1] == "RIGHT")
				{
					//Go to the office room
					return RoomEnum::Office;
				}
				//If the BACK argument has been entered
				else if (commandInput[1] == "BACK")
				{
					//Go back to the Cell RoomEnum
					return RoomEnum::Cell;
				}
				//If an unrecognized argument has been entered
				else
				{
					//Tell the player that an unrecognized argument has been entered
					InvalidCommand("Unrecognized place to go\n");
				}
			}
		}
		//If the recap command has been entered
		else if (commandInput[0] == "RECAP")
		{
			//Reprint the hallway intro
			HallwayIntro();
		}
		//If an invalid command has been entered
		else
		{
			//Tell the player that an invalid command has been entered
			InvalidCommand();
		}
	}
	//Return no room if the "QUIT" command has been entered. This signifies the end of the game
	return RoomEnum::None;
}

//Prints the introduction for the large door
void LargeDoorIntro()
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

//Does the main logic for the large door
RoomEnum DoLargeDoor()
{
	//Print the large door intro
	LargeDoorIntro();

	//The command input list. Used to retrieve commands from the player as well as their arguments
	vector<string> commandInput;

	//Repeatedly ask the player for commands to input. This runs until the "QUIT" command is inputted.
	while (GetCommand(commandInput))
	{
		//If the inspect command has been entered
		if (commandInput[0] == "INSPECT")
		{
			//Tell the player that they didn't find anyting useful
			cout << "After looking around, you don't find anything useful.\n";
		}
		//If the go command has been entered
		else if (commandInput[0] == "GO")
		{
			//If no other arguments have been passed alongside the command
			if (commandInput.size() == 1)
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
				if (commandInput[1] == "OUT")
				{
					//If the door has been unlocked
					if (largeDoorUnlocked)
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
						return RoomEnum::None;
					}
				}
				//If the BACK argument has been entered
				else if (commandInput[1] == "BACK")
				{
					//Go back to the hallway room
					return RoomEnum::Hallway;
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
		else if (commandInput[0] == "CODE")
		{
			//If the large door is locked
			if (!largeDoorUnlocked)
			{
				//If no arguments have been passed alongside the command
				if (commandInput.size() == 1)
				{
					//Tell the player to enter a 4 digit code
					cout << "Enter the 4 digit code:\n";
					//Get a number from the player
					int number = GetNumber();
					//If the number matches the door code
					if (number == doorCode)
					{
						//Set the text to yellow
						SetColor(Color::Black, Color::LightYellow);
						//Tell the player that the door has been unlocked!
						cout << "The door has now been unlocked! You can now escape!\n";
						//Set the text back to normal
						SetColor(Color::Black, Color::LightBlue);
						//Unlock the door
						largeDoorUnlocked = true;
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
					if (TryConvertToNumber(commandInput[1], code) && code == doorCode)
					{
						//If it matches, tell the player that the door is unlocked
						cout << "The door has now been unlocked! You can now escape!\n";
						//Unlock the door
						largeDoorUnlocked = true;
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
		//If the recap command has been entered
		else if (commandInput[0] == "RECAP")
		{
			//Reprint the large door intro
			LargeDoorIntro();
		}
		//If no valid command has been entered
		else
		{
			//Tell the player that an invalid command has been entered
			InvalidCommand();
		}
	}
	//Return no room if the "QUIT" command has been entered. This signifies the end of the game
	return RoomEnum::None;
}

//Prints the intro for the office
void OfficeIntro()
{
	//Clear the screen
	system("cls");
	//Set the text color to blue
	SetColor(Color::Black, Color::LightBlue);
	//Print the office introduction
	cout << "You slowly walk down the long hallway. After about a minute of traveling past other locked, empty jail cells, you find a door to an office. You head inside.\n";
	//Set the text back to normal
	SetColor(Color::Black, Color::BrightWhite);
}

//Does the main logic for the office room
RoomEnum DoOfficeRoom()
{
	//Print the office intro
	OfficeIntro();

	//The command input list. Used to retrieve commands from the player as well as their arguments
	vector<string> commandInput;

	//Repeatedly ask the player for commands to input. This runs until the "QUIT" command is inputted.
	while (GetCommand(commandInput))
	{
		//If the inspect command has been entered
		if (commandInput[0] == "INSPECT")
		{
			//If the not has not been found yet
			if (!foundNote)
			{
				//Set the text to blue
				SetColor(Color::Black, Color::LightBlue);
				//Tell how the player found the note
				cout << "You begin searching the room. In one corner of the room, you find some shelves with lots of papers on it. You pick some of them out, but their writing has been destroyed by moisture, so you leave it.\n";
				cout << "In the opposite corner, you see a chair, desk, and a computer system on top of it. You try powering it on, but it does not seem to work, even though it is plugged in.\n";
				cout << "You open one of the drawers inside the desk and you see a small note.\n";
				cout << "It has a four digit code on it:\n";
				cout << "\"" << doorCode << "\"\n";
				cout << "You put the note in your inventory\n";
				//Add the note to the player's inventory
				Inventory::AddItem(string("Note with the code: ") + to_string(doorCode));
				//Inventory.push_back(string("Note with the code: ") + to_string(doorCode));
				//Specify that the note has been found
				foundNote = true;
				//Set the text color back to normal
				SetColor(Color::Black, Color::BrightWhite);
			}
			//If the note has already been found
			else
			{
				//Tell the player that they did not find anything useful
				cout << "After looking around, you don't find anything useful.\n";
			}
		}
		//If the GO command has been found
		else if (commandInput[0] == "GO")
		{
			//If no other arguments have been passed alongside the command
			if (commandInput.size() == 1)
			{
				//Ask the player where they want to go and present them their options
				cout << "Where do you want to go?\n";
				cout << "Valid options:\n";
				cout << "OUT : Go back out into the hallway and back to where your cell is\n";
			}
			//If the OUT argument has been passed
			else if (commandInput[1] == "OUT")
			{
				//Go to the hallway
				return RoomEnum::Hallway;
			}
			//If no valid command has been entered
			else
			{
				//Tell the player that an invalid argument has been entered
				InvalidCommand("Unrecognized place to go\n");
			}
		}
		//If the RECAP command has been entered
		else if (commandInput[0] == "RECAP")
		{
			//Reprint the office intro
			OfficeIntro();
		}
		//If no valid command has been entered
		else
		{
			//Tell the player that an invalid command has been entered
			InvalidCommand();
		}
	}
	//Return no room if the "QUIT" command has been entered. This signifies the end of the game
	return RoomEnum::None;
}*/

//Resets the game to its base state
//void ResetGame()
//{
	/*
	FoundCellKey = false; //Reset the whether the cell key has been found
	//currentRoom = RoomEnum::Cell; //Set the current room to the cell
	//previousRoom = RoomEnum::Cell; //Set the previous room to the cell
	doorCode = (rand() % 9000) + 1000; //Set the door code to a random number between 0000 and 9999
	largeDoorUnlocked = false; //Reset whether the large door is unlocked or not
	foundNote = false; //Reset whether the not has been found or not
	Inventory::Clear(); //Clear the player's inventory
	*/
//}

//Gets a command from the player to execute. Returns false if the "QUIT" command has been entered, and returns true for any other command
bool GetCommand(vector<string>& commandResult)
{
	//Get a string input from the player
	string input = GetString();

	//Split the input string into several to get the arguments for the command
	commandResult = Split(input);

	//If no command has been entered
	if (commandResult.size() == 0)
	{
		//Tell the player to enter a valid command
		InvalidCommand("Please enter a command\n");
		//Rerun the function
		return GetCommand(commandResult);
	}
	//If the QUIT command has been entered
	if (commandResult[0] == "QUIT")
	{
		//Clear the screen
		system("cls");
		//Tell the player that they are quitting the game
		cout << "Quitting the game\n\n";
		//Return false, signifying that the "QUIT" command has been entered
		return false;
	}
	//If the HELP command has been entered
	else if (commandResult[0] == "HELP")
	{
		//Display a list of all the possible commands the player can use
		cout << "QUIT : Exits out of the game\n";
		cout << "INVENTORY : Shows what you have in your inventory\n";
		cout << "INSPECT : Inspects the current room that you are in. It may help you find something useful\n";
		cout << "GO : Go or attempt to go to a different room or area\n";
		cout << "CLEAR : Clears the console window\n";
		cout << "RECAP : Retells you where you are at\n";
		//Rerun the function
		return GetCommand(commandResult);
	}
	//If the INVENTORY or INV command has been entered
	else if (commandResult[0] == "INVENTORY" || commandResult[0] == "INV")
	{
		//If the inventory is empty
		if (Inventory::Size() == 0)
		{
			//Tell the player that the inventory is empty
			cout << "Your Inventory is empty\n";
		}
		//If the inventory is not empty
		else
		{
			//Print all the contents of the inventory. Loop over all the inventory's contents and print each one of them
			cout << "Your Inventory:\n";
			for (const string& item : Inventory::AllItems())
			{
				cout << item << '\n';
			}
		}
		//Rerun the function
		return GetCommand(commandResult);
		//return true;
	}
	//IF the clear command has been entered
	else if (commandResult[0] == "CLEAR")
	{
		//Clear the screen
		system("cls");
		//Rerun the command
		return GetCommand(commandResult);
	}
	//If any other command has been entered
	else
	{
		//Return true, signifying that a command has been entered
		return true;
	}
}

//Converts a string to uppercase letters
string& ToUpperCase(string& input)
{
	//Loop over each of the characters of the string
	for (char& character : input)
	{
		//Make each character upper case
		character = toupper(character);
	}
	//Return the string
	return input;
}

//Splits a string into multiple strings. This is used to obtain the arguments for a command
vector<string> Split(string input, char delimiter)
{
	vector<string> arguments; //The arguments retrieved from the input
	string current = ""; //The current input string

	//Loop over all the characters in the input
	for (char& character : input)
	{
		//If the character is equal to the delimiter
		if (character == delimiter)
		{
			//If the current input string is not blank
			if (current != "")
			{
				//Add it to the list of arguments
				arguments.push_back(current);
				//Reset the current input string to blank
				current = "";
			}
		}
		//If the character is not equal to the delimiter
		else
		{
			//Add it onto the current input string
			current += character;
		}
	}
	//If the current string input is not blank
	if (current != "")
	{
		//Add it to the list of arguments
		arguments.push_back(current);
	}
	//Return the list of arguments
	return arguments;
}

//Gets a number from player input
int GetNumber(string prefix)
{
	//Repeat until a valid number has been entered
	while (true)
	{
		//Print the prefix
		cout << "\n" << prefix;
		//Get the player's input
		string input;
		getline(cin, input);
		//If no string has been entered
		if (input == "")
		{
			//Tell the player that an invalid number has been entered
			InvalidCommand("Please enter a valid number\n");
			//Go back to the top of the loop
			continue;
		}
		//If a string has been entered
		else
		{
			//Attempt to convert the string to a number
			int result = 0;
			if (TryConvertToNumber(input, result))
			{
				//If the string is valid number, return the number
				return result;
			}
			//If the string was not a valid number
			else
			{
				//Tell the player that an invalid number has been entered
				InvalidCommand("Please enter a valid number\n");
				//Go back to the top of the loop
				continue;
			}
		}
	}
}

//Gets a string from player input
string GetString(bool toUpperCase, string prefix)
{
	//Repeat until a valid string has been entered
	while (true)
	{
		//Print the prefix
		cout << "\n" << prefix;
		//Get the player's input
		string input;
		getline(cin, input);
		//If no string has been entered
		if (input == "")
		{
			//Tell the player that an invalid string has been entered
			InvalidCommand("Please enter a valid word\n");
			//Go back to the top of the loop
			continue;
		}
		//If a valid string has been entered
		else
		{
			//If the string should be converted to uppercase letters
			if (toUpperCase)
			{
				//Convert it to uppercase
				ToUpperCase(input);
			}
			//Return the final string
			return input;
		}
	}
}

//Attempts to convert the inputString to a number. Returns true if the conversion is successful, and returns false otherwise.
//If the conversion was successful, the "output" parameter will be set to the converted number
bool TryConvertToNumber(string inputString, int& output)
{
	try
	{
		//Attempt to convert the string to a number
		output = stoi(inputString);
		//If the attempt was successful, then return true
		return true;
	}
	//If the attempt was a failure
	catch (...)
	{
		//Set the output to 0
		output = 0;
		//Return false, signifying a failure
		return false;
	}
}

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background, Color Text)
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set the background and text color the console
	SetConsoleTextAttribute(consoleHandle, static_cast<int>(Text) + (static_cast<int>(Background) * 16));
}

//Prints out text in red color, signaling an error of some kind
void InvalidCommand(string output)
{
	//Set the color to red
	SetColor(Color::Black, Color::LightRed);
	//Print the output
	cout << output;
	//Set the color back to normal
	SetColor(Color::Black, Color::BrightWhite);
}

/*RoomEnum GetCurrentRoom()
{
	return currentRoom;
}

void SetCurrentRoom(RoomEnum nextRoom)
{
	previousRoom = currentRoom;
	currentRoom = nextRoom;
}

RoomEnum GetPreviousRoom()
{
	return previousRoom;
}*/
