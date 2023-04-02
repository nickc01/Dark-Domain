#pragma once
#include <string> //Used to gain access to "std::string"
#include <vector> //Used to gain access to "std::vector"
#include "gameEnums.h" //Used to gain access to common game enums, such as "Color", and "Anchor"
#include <tuple> //Used to gain access to the "std::tuple<>" type



//--Functions--

//Gets a command from the player to execute. Returns false if the "QUIT" command has been entered, and returns true for any other command
bool GetCommand(std::vector<std::string>& commandInput);

//Converts a std::string to uppercase letters
void ToUpperCase(std::string& input);

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background = Color::Black, Color Text = Color::BrightWhite);

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(std::tuple<Color, Color> Colors);

//Gets the maximum width and height of the console screen
std::tuple<int,int> GetConsoleDimensions();

//Retrieves the currently set color
std::tuple<Color, Color> GetColor();

//Prints a specified amount of padding characters to the console
void PrintPadding(int amount, char paddingChar = ' ');

//Adds extra padding to a string to get it to it's desired length
std::string PadOutString(std::string value, int desiredLength,char paddingChar = ' ');

//Similar to Print Anchored, but can print text that is seperated by newlines.
void PrintAnchoredMultiline(std::string text, Anchor anchor = Anchor::Left, std::tuple<Color, Color> TextColor = { Color::Black,Color::BrightWhite }, char leftFiller = ' ', char rightFiller = ' ');

//Similar to cout, but can output the text either on the left, middle, or right side of the screen, along with a specified color
void PrintAnchored(std::string text, Anchor anchor = Anchor::Left, std::tuple<Color, Color> TextColor = {Color::Black,Color::BrightWhite}, char leftFiller = ' ', char rightFiller = ' ');

//Splits a std::string into multiple strings. This is used to obtain the arguments for a command
std::vector<std::string> Split(std::string input, char delimiter = ' ');

//Gets a number from player input
int GetNumber(std::string prefix = "/CODE/>");

//A randomizer that uses a percentage. The lower the percentage, the less this function will return true.
bool ChanceRandomizer(float percentage);

//Gets a std::string from player input
std::string GetString(bool toUpperCase = true, std::string prefix = "/>");

//Attempts to convert the inputString to a number. Returns true if the conversion is successful, and returns false otherwise.
//If the conversion was successful, the "output" parameter will be set to the converted number
bool TryConvertToNumber(std::string inputString, int& output);

//Prints out text in red color, signaling an error of some kind
void InvalidCommand(std::string output = "Unrecognized command. Type \"HELP\" for a list of valid commands\n");

void Pause();

void ClearConsole();