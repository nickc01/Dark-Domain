/*
	Nicholas Cullen
	11/29/19
	Dungeon Escape: A small interactive story game where you need to escape an abandoned dungeon
*/

//Gains access to the std::string class
#include <string> 
//Gains access to std::cout and std::cin
#include <iostream>
//Gains access to the std::vector class
//#include <vector> 
//Gains access to the time() function                   
#include <ctime>

#include "gameEnums.h"
#include "gameFunctions.h"
#include "gameVariables.h"

using namespace std; //Prevents me from having to type in "std::" all over the place



int main()
{
	//Reset the seed of the randomizer
	srand(time(0));

	//Set the text color to green
	SetColor(Color::Black, Color::LightGreen);

	//Print the title
	cout << "Welcome to Dungeon Escape!\n\n";

	//Set the color back to normal
	SetColor(Color::Black, Color::BrightWhite);

	//Wait for the player to press any key
	system("pause");

	//Clear the screen
	system("cls");

	//The main game loop. Repeats until it's gameOver is set to false
	do
	{
		//Reset the game's main variables
		ResetGame();

		//Start the player in the cell room and wait for them to go to the next room
		Room nextRoom = DoCellRoom();

		//Repeat until the room is set to None
		while (true)
		{
			//Set the previous room to the current room
			previousRoom = currentRoom;

			//Set the current room to the next room the player is going into
			currentRoom = nextRoom;
			//Pick the cell logic depending on the current room the player is in
			switch (currentRoom)
			{
			case Room::Cell: //If the current room is the cell
				nextRoom = DoCellRoom(); //Do the cell room logic
				continue; //Go back to the top of the loop

			case Room::Hallway: //If the current room is the hallway
				nextRoom = DoHallway(); //Do the hallway logic
				continue; //Go back to the top of the loop

			case Room::LargeDoor: //If the current room is the large door room
				nextRoom = DoLargeDoor(); //Do the large door room logic
				continue; //Go back to the top of the loop

			case Room::Office: //If the current room is the office
				nextRoom = DoOfficeRoom(); //Do the office room logic
				continue; //Go back to the top of the loop

			case Room::None: //If the room is set to none
				break; //Break out of the switch statement

			}
			break; //Break out of the loop, signifying that the game is done. This is only reached if the Room is set to None
		}
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