#pragma once
#include "../stdafx.h"
#include "../mainWindow.h"
#include <list>

namespace Labyrinth
{
	class TopScore
	{
		void Show(std::set<std::pair<float, std::string>>& TOP_List);
	};
}
