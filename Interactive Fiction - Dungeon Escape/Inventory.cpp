#include "Inventory.h" //Used to gain access to the Inventory Prototypes
#include <algorithm> //Used to gain access to the "std::find" algorithm
#include "gameFunctions.h" //Used to gain access to common game functions
#include <iostream> //Used to gain access to cout for printing to the console

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

vector<string> inventory; //The inventory of the player

//Adds an item to the players inventory
void Inventory::AddItem(string item)
{
	//Store the previous color
	auto previousColor = GetColor();
	//Set the text to yellow
	SetColor(Color::Black, Color::Yellow);
	//Tell the player that the item was added
	cout << '\"' << item << "\" has been added to your inventory\n";
	//Reset the color
	SetColor(previousColor);
	//Add the item to the inventory list
	inventory.push_back(item);
}

//Removes an item from the player's inventory
void Inventory::RemoveItem(std::string item)
{
	//Find the index of the item in the inventory
	auto index = std::find(inventory.begin(), inventory.end(), item);
	//If the inventory contains the item
	if (index < inventory.end())
	{
		//Store the previous color
		auto previousColor = GetColor();
		//Set the text to yellow
		SetColor(Color::Black, Color::Yellow);
		//Tell the player that the item was removed
		cout << '\"' << item << "\" has been removed from your inventory\n";
		//Reset the color
		SetColor(previousColor);
		//Remove the item from the inventory
		inventory.erase(index);
	}
}
//Check if an item is contained in the inventory
bool Inventory::HasItem(std::string item)
{
	//Find the index of the string and see if it has been found
	return std::find(inventory.begin(), inventory.end(), item) < inventory.end();
}

//Clears the inventory
void Inventory::Clear()
{
	//Clear the inventory
	inventory.clear();
}

//Get the size of the inventory
int Inventory::Size()
{
	//Return the size
	return inventory.size();
}

//Returns all the items in the inventory
const std::vector<std::string>& Inventory::AllItems()
{
	//Return the inventory vector
	return inventory;
}
