#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <ctime>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace std;

enum class Color
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Aqua = 3,
	Red = 4,
	Purple = 5,
	Yellow = 6,
	White = 7,
	Gray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightAqua = 11,
	LightRed = 12,
	LightPurple = 13,
	LightYellow = 14,
	BrightWhite = 15

};

//--Functions--
//Prints the introduction
void PrintIntro();
//void PrintCommands();
//Resets the game to its base state
void ResetGame();
//Gets a command from the player to execute
bool GetCommand(vector<string>& commandInput);
//Converts a string to uppercase letters
string& ToUpperCase(string& input);

void SetColor(Color Background = Color::Black, Color Text = Color::BrightWhite);

//Splits a string into multiple strings
vector<string> Split(string input, char delimiter = ' ');

int GetNumber(string prefix = "/CODE/>");
string GetString(bool toUpperCase = true, string prefix = "/>");

//Attempts to convert the inputString to a number. Returns true if the conversion is successful, and returns false otherwise.
//If the conversion was successful, the "output" parameter will be set to the converted number
bool TryConvertToNumber(string inputString,int& output);

//--Room Functions--
string DoCellRoom(bool doRoomDescription = true);
string DoHallway();
string DoLargeDoor();
string DoOfficeRoom();

//--Command Functions--
//void Quit();
//void Move();
//void Inspect();

//--Structs--
/*struct Command
{
	string Keyword; //The name of the command
	string Description; //The description of the command
	function<void()> Function; //The function to execute when the player types in the command
};*/

//--Variables--
bool Ending = false;
string currentRoom;
string previousRoom;
vector<string> Inventory;
bool FoundCellKey = false;
bool CellUnlocked = false;
int doorCode = 1234;
bool largeDoorUnlocked = false;
bool foundNote = false;



int main()
{
	srand(time(0));
	SetColor(Color::Black, Color::LightGreen);
	cout << "Welcome to Dungeon Escape!\n\n";
	SetColor(Color::Black, Color::BrightWhite);
	system("pause");
	system("cls");
	do
	{
		ResetGame();
		PrintIntro();
		string nextRoom = DoCellRoom(false);
		while (true)
		{
			currentRoom = nextRoom;
			if (currentRoom == "Cell")
			{
				nextRoom = DoCellRoom();
			}
			else if (currentRoom == "Hallway")
			{
				nextRoom = DoHallway();
			}
			else if (currentRoom == "LargeDoor")
			{
				nextRoom = DoLargeDoor();
			}
			else if (currentRoom == "Office")
			{
				nextRoom = DoOfficeRoom();
			}
			else
			{
				break;
			}
		}
		cout << "\nThanks for playing!\n";
		cout << "Want to play again? (Y/N)\n";
		while (true)
		{
			string input = GetString(true, "/YN/>");
			if (input.find("Y") < string::npos)
			{
				Ending = false;
				break;
			}
			else if (input.find("N") < string::npos)
			{
				Ending = true;
				break;
			}
			else
			{
				cout << "Invalid option, try again\n";
			}
		}

	} while (!Ending);
}



void PrintIntro()
{
	SetColor(Color::Black, Color::LightBlue);
	cout << "You have woken up in an old, mossy cell within a dark dungeon. You have no idea how you got here, and there is nobody else in sight. The iron bars in your cell seem to be locked with a key.\n\n";
	cout << "Type \"HELP\" at anytime to see a list of commands you can use\n\n";
	SetColor(Color::Black, Color::BrightWhite);
}

string DoCellRoom(bool doRoomDescription)
{
	if (doRoomDescription)
	{
		SetColor(Color::Black, Color::LightBlue);
		cout << "You are now back in the cell you have woken up in\n\n";
		SetColor(Color::Black, Color::BrightWhite);
	}
	vector<string> commandInput;
	while (GetCommand(commandInput))
	{
		if (commandInput[0] == "INSPECT")
		{
			if (!FoundCellKey)
			{
				SetColor(Color::Black, Color::LightBlue);
				cout << "After looking around the room for a while, you find a small key underneath some moss nearby the bars.\n";
				cout << "A key has been added to your inventory\n";
				SetColor(Color::Black, Color::BrightWhite);
				FoundCellKey = true;
				Inventory.push_back("Small Key");
			}
			else
			{
				cout << "After looking around, you don't find anything useful.\n";
			}
		}
		else if (commandInput[0] == "GO")
		{
			if (commandInput.size() == 1)
			{
				cout << "Where do you want to go?\n";
				cout << "Valid options:\n";
				cout << "OUT : Leave the cell and out into the hallway\n";
			}
			else if (commandInput[1] == "OUT")
			{
				if (!CellUnlocked)
				{
					auto index = find(Inventory.begin(), Inventory.end(), "Small Key");
					if (index < Inventory.end())
					{
						CellUnlocked = true;
						system("cls");
						SetColor(Color::Black, Color::LightBlue);
						cout << "You unlocked your cell using the small key that you found.\n";
						cout << "You are now in the hallway just outside of your cell. The hallway splits into two directions, left and right.\n\n";
						cout << "Use the \"GO\" command to pick where you want to go";
						SetColor(Color::Black, Color::BrightWhite);
						return "Hallway";
					}
					else
					{
						cout << "You aren't able to leave the cell. The cell is locked. You might need to find a key.\n";
					}
				}
				else
				{
					system("cls");
					SetColor(Color::Black, Color::LightBlue);
					cout << "You are now in a hallway just outside of your cell. You can either go to the left or to the right.\n";
					SetColor(Color::Black, Color::BrightWhite);
					return "Hallway";
				}
			}
		}
		else if (commandInput[0] == "RECAP")
		{
			SetColor(Color::Black, Color::LightBlue);
			cout << "You are in your cell that you have awoken in.\n\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
		else
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Unrecognized command. Type \"HELP\" for a list of valid commands\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
	}
	return "";
}

string DoHallway()
{
	vector<string> commandInput;
	while (GetCommand(commandInput))
	{
		if (commandInput[0] == "INSPECT")
		{
			cout << "After looking around, you don't find anything useful.\n";
		}
		else if (commandInput[0] == "GO")
		{
			if (commandInput.size() == 1)
			{
				cout << "In which direction do you want to go?\n";
				cout << "Valid options:\n";
				cout << "LEFT : Follow the hallway to the left\n";
				cout << "RIGHT : Follow the hallway to the right\n";
			}
			else
			{
				if (commandInput[1] == "LEFT")
				{
					system("cls");
					SetColor(Color::Black, Color::LightBlue);
					cout << "You now find yourself in front of a large door. You see some light around the edges, so you assume it's the way out.\n";
					cout << "The door however is locked. You notice that there is another lock on the door. But this time it seems to be a numerical lock.\n";
					cout << "You need to input the correct 4 digit password into the lock in order to open the door.\n";
					cout << "Type in the command \"CODE\" to try out a numerical code on the lock.\n";
					SetColor(Color::Black, Color::BrightWhite);
					return "LargeDoor";
				}
				else if (commandInput[1] == "RIGHT")
				{
					system("cls");
					cout << "You slowly walk down the long hallway. After about a minute of traveling past other locked, empty jail cells, you find a door to an office. You head inside.\n";
					return "Office";
				}
			}
		}
		else if (commandInput[0] == "RECAP")
		{
			SetColor(Color::Black, Color::LightBlue);
			cout << "You are now in the hallway just outside of your cell. The hallway splits into two directions, left and right.\n\n";
			cout << "Use the \"GO\" command to pick where you want to go";
			SetColor(Color::Black, Color::BrightWhite);
		}
		else
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Unrecognized command. Type \"HELP\" for a list of valid commands\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
	}
	return "";
}

string DoLargeDoor()
{
	vector<string> commandInput;
	while (GetCommand(commandInput))
	{
		if (commandInput[0] == "INSPECT")
		{
			cout << "After looking around, you don't find anything useful.\n";
		}
		else if (commandInput[0] == "GO")
		{
			if (commandInput.size() == 1)
			{
				cout << "Where do you want to go?\n";
				cout << "Valid options:\n";
				cout << "OUT : Go out the large door and escape.\n";
				cout << "BACK : Go back through the hallway just outside your cell.\n";
			}
			else
			{
				if (commandInput[1] == "OUT")
				{
					if (largeDoorUnlocked)
					{
						system("cls");
						SetColor(Color::Black, Color::LightYellow);
						cout << "You have escaped the old prison and you are now free!\n";
						SetColor(Color::Black, Color::BrightWhite);
						return "";
					}
				}
				else if (commandInput[1] == "BACK")
				{
					system("cls");
					SetColor(Color::Black, Color::LightBlue);
					cout << "You are now in a hallway just outside of your cell. You can either go to the left or to the right.\n";
					SetColor(Color::Black, Color::BrightWhite);
					return "Hallway";
				}
			}
		}
		else if (commandInput[0] == "CODE")
		{
			if (!largeDoorUnlocked)
			{
				if (commandInput.size() == 1)
				{
					cout << "Enter the 4 digit code:\n";
					int number = GetNumber();
					if (number == doorCode)
					{
						SetColor(Color::Black, Color::LightYellow);
						cout << "The door has now been unlocked! You can now escape!\n";
						SetColor(Color::Black, Color::LightBlue);
						largeDoorUnlocked = true;
					}
					else
					{
						cout << "The code entered was invalid\n";
					}
				}
				else
				{
					int code = 0;
					if (TryConvertToNumber(commandInput[1], code) && code == doorCode)
					{
						cout << "The door has now been unlocked! You can now escape!\n";
						largeDoorUnlocked = true;
					}
					else
					{
						SetColor(Color::Black, Color::LightRed);
						cout << "The code entered was invalid\n";
						SetColor(Color::Black, Color::BrightWhite);
					}
				}
			}
			else
			{
				cout << "The door is already unlocked\n";
			}
		}
		else if (commandInput[0] == "RECAP")
		{
			SetColor(Color::Black, Color::LightBlue);
			cout << "You now find yourself in front of a large door. You see some light around the edges, so you assume it's the way out.\n";
			cout << "The door however is locked. You notice that there is another lock on the door. But this time it seems to be a numerical lock.\n";
			cout << "You need to input the correct 4 digit password into the lock in order to open the door.\n";
			cout << "Type in the command \"CODE\" to try out a numerical code on the lock.\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
		else
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Unrecognized command. Type \"HELP\" for a list of valid commands\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
	}
	return "";
}

string DoOfficeRoom()
{
	vector<string> commandInput;
	while (GetCommand(commandInput))
	{
		if (commandInput[0] == "INSPECT")
		{
			SetColor(Color::Black, Color::LightBlue);

			cout << "You begin searching the room. In one corner of the room, you find some shelves with lots of papers on it. You pick some of them out, but their writing has been destroyed by moisture, so you leave it.\n";
			cout << "In the opposite corner, you see a chair, desk, and a computer system on top of it. You try powering it on, but doesn't seem to work, even though it's plugged in.\n";
			cout << "You open one of the drawers inside the desk and you see a small note.\n";
			cout << "It has a four digit code on it:\n";
			cout << "\"" << doorCode << "\"\n";
			cout << "You put the note in your inventory\n";
			Inventory.push_back(string("Note with the code: ") + to_string(doorCode));

			SetColor(Color::Black, Color::BrightWhite);
		}
		else if (commandInput[0] == "GO")
		{
			if (commandInput.size() == 1)
			{
				cout << "Where do you want to go?\n";
				cout << "Valid options:\n";
				cout << "OUT : Go back out into the hallway and back to where your cell is\n";
			}
			else if (commandInput[1] == "OUT")
			{
				system("cls");
				SetColor(Color::Black, Color::LightBlue);
				cout << "You are now back in the hallway just outside of your cell. You can either go to the left or to the right.\n";
				SetColor(Color::Black, Color::BrightWhite);
				return "Hallway";
			}
		}
		else if (commandInput[0] == "RECAP")
		{
			SetColor(Color::Black, Color::LightBlue);
			cout << "After about a minute of traveling past other locked, empty jail cells in the hallway, you find a door to an office. You head inside.\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
		else
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Unrecognized command. Type \"HELP\" for a list of valid commands\n";
			SetColor(Color::Black, Color::BrightWhite);
		}
	}
	return "";
}

void ResetGame()
{
	Ending = false;
	FoundCellKey = false;
	currentRoom = "Cell";
	previousRoom = "Cell";
	doorCode = rand() % 10000;
	largeDoorUnlocked = false;
	Inventory.clear();
}

bool GetCommand(vector<string>& commandResult)
{
	string input = GetString();

	commandResult = Split(input);

	if (commandResult.size() == 0)
	{
		SetColor(Color::Black, Color::LightRed);
		cout << "Please enter a command\n";
		SetColor(Color::Black, Color::BrightWhite);
		return GetCommand(commandResult);
	}

	if (commandResult[0] == "QUIT")
	{
		system("cls");
		cout << "Quitting the game\n\n";
		return false;
	}
	else if (commandResult[0] == "HELP")
	{
		cout << "QUIT : Exits out of the game\n";
		cout << "INVENTORY : Shows what you have in your inventory\n";
		cout << "INSPECT : Inspects the current room that you are in. It may help you find something useful\n";
		cout << "GO : Go or attempt to go to a different room or area\n";
		cout << "CLEAR : Clears the console window\n";
		cout << "RECAP : Retells you where you are at\n";
		return GetCommand(commandResult);
	}
	else if (commandResult[0] == "INVENTORY" || commandResult[0] == "INV")
	{
		if (Inventory.size() == 0)
		{
			cout << "Your Inventory is empty\n";
		}
		else
		{
			cout << "Your Inventory:\n";
			for (string& item : Inventory)
			{
				cout << item << '\n';
			}
		}
		return GetCommand(commandResult);
		//return true;
	}
	else if (commandResult[0] == "CLEAR")
	{
		system("cls");
		return GetCommand(commandResult);
	}
	else
	{
		return true;
	}
}

string& ToUpperCase(string& input)
{
	for (char& character : input)
	{
		character = toupper(character);
	}
	return input;
}

vector<string> Split(string input, char delimiter)
{
	vector<string> result;
	string current = "";
	for (char& character : input)
	{
		if (character == delimiter)
		{
			if (current != "")
			{
				result.push_back(current);
				current = "";
			}
		}
		else
		{
			current += character;
		}
	}
	if (current != "")
	{
		result.push_back(current);
	}
	return result;
}

int GetNumber(string prefix)
{
	while (true)
	{
		cout << "\n" << prefix;
		string input;
		getline(cin, input);
		if (input == "")
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Please enter a valid number\n";
			SetColor(Color::Black, Color::BrightWhite);
			continue;
		}
		else
		{
			int result = 0;
			if (TryConvertToNumber(input,result))
			{
				return result;
			}
			else
			{
				SetColor(Color::Black, Color::LightRed);
				cout << "Please enter a valid number\n";
				SetColor(Color::Black, Color::BrightWhite);
				continue;
			}
		}
	}
}

string GetString(bool toUpperCase, string prefix)
{
	while (true)
	{
		cout << "\n" << prefix;
		string input;
		getline(cin, input);
		if (input == "")
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Please enter a valid word\n";
			SetColor(Color::Black, Color::BrightWhite);
			continue;
		}
		else
		{
			if (toUpperCase)
			{
				ToUpperCase(input);
			}
			return input;
		}
	}
}


bool TryConvertToNumber(string inputString, int& output)
{
	try
	{
		output = stoi(inputString);
		return true;
	}
	catch (...)
	{
		output = 0;
		return false;
	}
}

void SetColor(Color Background, Color Text)
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set the background and text color the console
	SetConsoleTextAttribute(consoleHandle,static_cast<int>(Text) + (static_cast<int>(Background) * 16));
}
