#include <string>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

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

//Splits a string into multiple strings
vector<string> Split(string input, char delimiter = ' ');

//--Room Functions--
string DoCellRoom(bool doRoomDescription = true);

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
vector<string> Inventory;
bool FoundCellKey = false;
bool CellUnlocked = false;


/*vector<Command> Commands =
{
	{"INSPECT","Inspects the current room. You may find something useful",Inspect},
	{"QUIT","Quits the game",Quit}
};*/



int main()
{
	cout << "Welcome to Dungeon Escape!\n\n";
	cout << "Press Enter to begin the game\n";

	system("pause");

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
			else
			{
				break;
			}
		}

	} while (!Ending);
}



void PrintIntro()
{
	cout << "You have woken up in an old, mossy cell within a dark dungeon. You have no idea how you got here, and there is nobody else in sight. The iron bars in your cell seem to be locked with a key.\n\n";
	cout << "Type \"HELP\" at anytime to see a list of commands you can use\n\n";
}

string DoCellRoom(bool doRoomDescription)
{
	if (doRoomDescription)
	{
		cout << "You are now back in the cell you have woken up in\n\n";
	}
	vector<string> commandInput;
	while (GetCommand(commandInput))
	{
		if (commandInput[0] == "INSPECT")
		{
			if (!FoundCellKey)
			{
				cout << "After looking around the room for a while, you find a small key underneath some moss nearby the bars.\n";
				cout << "A key has been added to your inventory\n";
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
				cout << "Valid optiosn:\n";
				cout << "OUT : Leave the cell and out into the hallway\n";
			}
			else if (commandInput[1] == "OUT")
			{
				if (!CellUnlocked)
				{
					auto index = find(Inventory.begin(), Inventory.end(), "Small Key");
					if (index < Inventory.end())
					{
						Inventory.erase(index);
						CellUnlocked = true;
						cout << "You unlocked your cell using the small key that you found.\n";
						cout << "You are now in a hallway just outside of your cell. You can either go to the left or to the right.\n";
						return "Hallway";
					}
					else
					{
						cout << "You aren't able to leave the cell. The cell is locked. You might need to find a key.\n";
					}
				}
				else
				{
					cout << "You are now in a hallway just outside of your cell. You can either go to the left or to the right.\n";
					return "Hallway";
				}
			}
		}
		else
		{
			cout << "Unrecognized command. Type \"HELP\" for a list of valid commands\n";
		}
	}
	return "";
}

void ResetGame()
{
	Ending = false;
	FoundCellKey = false;
	currentRoom = "Cell";
	Inventory.clear();
}

bool GetCommand(vector<string>& commandResult)
{
	cout << "\n/>";
	string input;
	getline(cin, input);

	ToUpperCase(input);

	commandResult = Split(input);

	if (commandResult.size() == 0)
	{
		cout << "Please enter a command\n";
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
		return GetCommand(commandResult);
	}
	else if (commandResult[0] == "INVENTORY")
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
