#pragma once
#include <string>
#include <vector>
#include "gameEnums.h"



//--Functions--

//Resets the game to its base state
//void ResetGame();

//Gets a command from the player to execute. Returns false if the "QUIT" command has been entered, and returns true for any other command
bool GetCommand(std::vector<std::string>& commandInput);

//Converts a std::string to uppercase letters
std::string& ToUpperCase(std::string& input);

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background = Color::Black, Color Text = Color::BrightWhite);

//Splits a std::string into multiple strings. This is used to obtain the arguments for a command
std::vector<std::string> Split(std::string input, char delimiter = ' ');

//Gets a number from player input
int GetNumber(std::string prefix = "/CODE/>");

//Gets a std::string from player input
std::string GetString(bool toUpperCase = true, std::string prefix = "/>");

//Attempts to convert the inputString to a number. Returns true if the conversion is successful, and returns false otherwise.
//If the conversion was successful, the "output" parameter will be set to the converted number
bool TryConvertToNumber(std::string inputString, int& output);

//Prints out text in red color, signaling an error of some kind
void InvalidCommand(std::string output = "Unrecognized command. Type \"HELP\" for a list of valid commands\n");


/*RoomEnum GetCurrentRoom();
void SetCurrentRoom(RoomEnum nextRoom);

RoomEnum GetPreviousRoom();

//--RoomEnum Functions--

//Does the main logic for the cell room
RoomEnum DoCellRoom();

//Does the main logic for the hallway
RoomEnum DoHallway();

//Does the main logic for the large door
RoomEnum DoLargeDoor();

//Does the main logic for the office room
RoomEnum DoOfficeRoom();

//Prints the introduction of the cell room the player spawns in
void CellIntro();

//Prints the introduction for the hallway
void HallwayIntro();

//Prints the introduction for the large door
void LargeDoorIntro();

//Prints the introduction for the office
void OfficeIntro();*/