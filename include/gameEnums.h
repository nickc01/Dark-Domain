#pragma once


//An enum representing the foreground and background color of the console. Each color corresponds to a number below
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

//An enum representing where text should be drawn on the console
enum class Anchor
{
	Left, //Print text on the left side of the screen
	Middle, //Print text at the middle of the screen
	Right //Print text on the right side of the screen
};