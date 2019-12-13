/*
	Nicholas Cullen
	12/13/19
	Dungeon Escape: A small interactive story game where you need to escape an abandoned dungeon
*/

//Gains access to the std::string class
#include <string> //Used to gain access to "std::string" 
//Gains access to std::cout and std::cin
#include <iostream> //Used to gain access to cout for printing to the console
//Gains access to the time() function                   
#include <ctime> //Used to gain access to "srand" and "rand" for getting random numbers

#include "gameEnums.h" //Used to gain access to common game enums, such as "Color", and "Anchor"
#include "gameFunctions.h" //Used to gain access to common game functions
#include "Rooms/Base/Room.h" //Used to gain access to the room definition for creating and executing rooms
#include "GameVariables.h" //Used to gain access to common game variables
#include "Battle.h" //Used to gain access to the battle class. Used to start battles
#include "Inventory.h" //Used to access and modify the inventory

using namespace std; //Used to prevent me from having to type "std::cout" everywhere


//Whether the game is over or not
bool GameOver = false;


int main()
{
	//Reset the seed of the randomizer
	srand(time(0));
	do
	{
		//Reset the game variables
		Variables::Reset();
		//Reset the player's inventroy
		Inventory::Clear();
		//Reset the rooms
		Room::Reset();

		//Set the text color to green
		SetColor(Color::Black, Color::LightGreen);

		//Print the title
		cout << "Welcome to Dungeon Escape!\n\n";

		//Set the color back to normal
		SetColor(Color::Black, Color::BrightWhite);

		//Wait for the player to press any key
		system("pause");

		//Ask for the player's name
		string name = GetString(false, "Please Enter your Name:\n/>");
		
		//Store the player's name
		Variables::PlayerName = name;

		//Clear the screen
		system("cls");

		//Greet the player and tell them what they need to do
		cout << "Hello " << name << ", welcome to dungeon escape!\n";
		cout << "Your goal is to figure out a way to escape the abandoned dungeon without getting killed.\n";
		cout << "Navigate through rooms and solve the puzzle!\n";
		
		//Wait for player input
		system("pause");

		//Reset the game over flag
		GameOver = false;

		//Clear the screen
		system("cls");

		//Keep running through each of the rooms until there is no more rooms to go through
		while (Room::ExecuteNextRoom()) {}

		//Print the ending message
		cout << "\nThanks for playing!\n";

		//Ask the player if they want to play again
		cout << "Want to play again? (Y/N)\n";

		//The input loop. Repeats until the player has entered a valid option
		while (true)
		{
			//Get the player's input
			string input = GetString(true, "/YN/>");

			//If the player Yes
			if (input.find("Y") < string::npos)
			{
				//Don't end the game yet, and go back to the top of the game loop
				GameOver = false;
				//Break out of the input loop
				break;
			}
			else if (input.find("N") < string::npos)
			{
				//End the game
				GameOver = true;
				//Break out of the input loop
				break;
			}
			else
			{
				//If neither options have been entered. Tell the player that an invalid option has been entered, and try again
				InvalidCommand("Invalid option, try again\n");
			}
		}
	} while (!GameOver);
}