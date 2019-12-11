#pragma once
#include "Base/Room.h"

class LargeDoorRoom : public Room
{
	void OnStart() override;

	void OnCommand(std::string Command, std::vector<std::string> Arguments) override;

	std::string GetName() const override;
};