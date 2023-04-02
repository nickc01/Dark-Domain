#pragma once
#include <string> //Used to gain access to "std::string"
#include <vector> //Used to gain access to "std::vector"

//The namespace for anything relating to the inventory
namespace Inventory
{
	//Adds an item to the player's inventory
	void AddItem(std::string item);
	//Removes an item from the player's inventory
	void RemoveItem(std::string item);
	//Checks to see if the player has an item or not
	bool HasItem(std::string item);
	//Clears the inventory
	void Clear();
	//Gets the amount of items in the player's inventory
	int Size();

	//Returns a vector containing all the items in the player's inventory
	const std::vector<std::string>& AllItems();
}