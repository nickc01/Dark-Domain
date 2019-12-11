#pragma once

#include "Base/Room.h"


class OfficeRoom : public Room
{
	void OnStart() override;

	void OnCommand(std::string Command, std::vector<std::string> Arguments) override;

	void Inspect() override;

	std::string GetName() const override;
};