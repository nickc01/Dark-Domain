#include "gameFunctions.h" //Used to gain access to common game functions
#include <iostream> //Used to gain access to cout for printing to the console

#define WIN32_LEAN_AND_MEAN //This is used to prevent importing extra windows features we don't need
#include <Windows.h> //Used to gain access to changing the color of the console

#include "Inventory.h"

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

Color Background = Color::Black; //The current background color that is set
Color Foreground = Color::BrightWhite; //The current foreground color that is set

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
		ClearConsole();
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
		ClearConsole();
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
void ToUpperCase(string& input)
{
	//Loop over each of the characters of the string
	for (char& character : input)
	{
		//Make each character upper case
		character = toupper(character);
	}
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
		auto previousColor = GetColor();
		//Print the prefix
		SetColor(Color::Black,Color::LightPurple);
		cout << "\n" << prefix;
		SetColor(get<0>(previousColor), get<1>(previousColor));
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

//A randomizer that uses a percentage. The lower the percentage, the less this function will return true.
bool ChanceRandomizer(float percentage)
{
	//Gets a random number between 0 and 100
	int num = rand() % 101;
	//Check if the random number is greater than the percentage amound
	return num <= (int)(percentage * 100.0f);
}

//Gets a string from player input
string GetString(bool toUpperCase, string prefix)
{
	//Repeat until a valid string has been entered
	while (true)
	{
		//Store the previous color
		auto previousColor = GetColor();
		//Print the prefix
		SetColor(Color::Black, Color::LightPurple);
		//Print the prefix
		cout << "\n" << prefix;
		//Reset the color
		SetColor(previousColor);
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
	::Background = Background;
	::Foreground = Text;

	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set the background and text color the console
	SetConsoleTextAttribute(consoleHandle, static_cast<int>(Text) + (static_cast<int>(Background) * 16));
}

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(std::tuple<Color, Color> Colors)
{
	//Forward the call to the other SetColor function
	SetColor(get<0>(Colors), get<1>(Colors));
}

//Gets the maximum width and height of the console screen
std::tuple<int, int> GetConsoleDimensions()
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info; //Stores info about the console screen

	//Get the info about the console screen by passing the pointer to the info struct
	GetConsoleScreenBufferInfo(consoleHandle, &info);

	//Return a tuple with the width and height
	return {info.dwSize.X,info.dwSize.Y};
}

//Gets the currently set color
std::tuple<Color,Color> GetColor()
{
	return {Background,Foreground};
}

//Prints a specified amount of padding to the console
void PrintPadding(int amount, char paddingChar)
{
	//Loop the amound of padding to be printed
	for (int i = 0; i < amount; i++)
	{
		//Print the padding character
		cout << paddingChar;
	}
}

//Pads out a string to the desired length
std::string PadOutString(std::string value, int desiredLength,char paddingChar)
{
	//If the string is greater or equal to the desired length
	if (value.length() >= desiredLength)
	{
		//Don't change anything about it
		return value;
	}
	else
	{
		//Get the amount of padding needed on the left side
		int leftPadding = (desiredLength - value.length()) / 2;
		//Get the amount of padding needed on the right side
		int rightPadding = desiredLength - value.length() - leftPadding;

		//The final output
		string output = "";
		//Add the left padding
		for (int i = 0; i < leftPadding; i++)
		{
			output += paddingChar;
		}
		//Add the original string
		output += value;
		//Add the right padding
		for (int i = 0; i < rightPadding; i++)
		{
			output += paddingChar;
		}
		//Return the final result
		return output;
	}
}

//Similar to Print Anchored, but can print text that is seperated by newlines.
void PrintAnchoredMultiline(std::string text, Anchor anchor, std::tuple<Color, Color> TextColor, char leftFiller, char rightFiller)
{
	//Split the string by their lines
	auto strings = Split(text, '\n');
	//For each string
	for (auto& str : strings)
	{
		//Print it to the console anchored
		PrintAnchored(str, anchor, TextColor, leftFiller, rightFiller);
	}
}

//Similar to cout, but can output the text either on the left, middle, or right side of the screen, along with a specified color
void PrintAnchored(std::string text, Anchor anchor, tuple<Color,Color> TextColor,char leftFiller, char rightFiller)
{
	//Get the console dimensions
	auto dimensions = GetConsoleDimensions();

	//Get the width of the console screen
	int width = get<0>(dimensions);

	//Store the previous color
	auto previousColor = GetColor();

	//if the text length is greater than the length of the console width
	if (text.length() >= width)
	{
		//Simply print it to the console
		cout << text << "\n";
		//Break out of the function
		return;
	}

	//If the text is to be anchored to the left
	if (anchor == Anchor::Left)
	{
		//Set the specified color
		SetColor(TextColor);
		//Print the text
		cout << text;
		//Reset the color
		SetColor(previousColor);
		//Print the rightmost padding
		for (int i = 0; i < (width - text.length()); i++)
		{
			cout << rightFiller;
		}
		//Go to the next line
		cout << '\n';
	}
	//If the text is to be anchored in the middle
	else if (anchor == Anchor::Middle)
	{
		//Get the left and right most spacing
		int leftSpacing = (width - text.length()) / 2;
		int rightSpacing = width - text.length() - leftSpacing;
		//Print out the left spacing
		for (int i = 0; i < leftSpacing; i++)
		{
			cout << leftFiller;
		}
		//Set the text color
		SetColor(TextColor);
		//Print the text
		cout << text;
		//Reset the color
		SetColor(previousColor);
		//Print the rightmost padding
		for (int i = 0; i < rightSpacing; i++)
		{
			cout << rightFiller;
		}
		//Go to the next line
		cout << '\n';
	}
	//If the text is to be anchored on the right side
	else if (anchor == Anchor::Right)
	{
		//Print the leftmost spacing
		for (int i = 0; i < (width - text.length()); i++)
		{
			cout << leftFiller;
		}
		//Set the text color
		SetColor(TextColor);
		//Print the text and go to a new line
		cout << text << '\n';
		//Reset the color
		SetColor(previousColor);
	}
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
