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
bool CellHasKey = true;


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
	cout << "You have woken up in an old, mossy cell within a dark dungeon. You have no idea how you got here, and there is nobody else in sight.\n\n";
	cout << "Type \"HELP\" at anytime to see a list of commands you can use\n\n";
}

string DoCellRoom(bool doRoomDescription)
{
	system("cls");
	if (doRoomDescription)
	{
		cout << "You are now back in the cell you have woken up in\n\n";
	}
	vector<string> commandInput;
	while (GetCommand(commandInput))
	{
		if (true)
		{

		}
	}
	return "";
}

void ResetGame()
{
	Ending = false;
	CellHasKey = true;
	currentRoom = "Cell";
	Inventory.clear();
}

bool GetCommand(vector<string>& commandResult)
{
	cout << '\n';
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
		cout << "GO : Go to a different room or area\n";
		return true;
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
		return true;
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
