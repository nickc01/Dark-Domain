#include "Inventory.h"
#include <algorithm>

using namespace std;

vector<string> inventory;

void Inventory::AddItem(string item)
{
	inventory.push_back(item);
}

void Inventory::RemoveItem(std::string item)
{
	auto index = std::find(inventory.begin(), inventory.end(), item);
	if (index < inventory.end())
	{
		inventory.erase(index);
	}
}

bool Inventory::HasItem(std::string item)
{
	return std::find(inventory.begin(), inventory.end(), item) < inventory.end();
}

void Inventory::Clear()
{
	inventory.clear();
}

int Inventory::Size()
{
	return inventory.size();
}

const std::vector<std::string>& Inventory::AllItems()
{
	return inventory;
}
