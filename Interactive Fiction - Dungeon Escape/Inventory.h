#pragma once
#include <string>
#include <vector>

namespace Inventory
{
	void AddItem(std::string item);
	void RemoveItem(std::string item);
	bool HasItem(std::string item);
	void Clear();
	int Size();

	const std::vector<std::string>& AllItems();
}