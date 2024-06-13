#pragma once
#include "Axes.h"
#include "Chess.h"
#include "CChess.h"
//#include "CChessDlg.h"
#include "resource.h"
#include <vector>

class MainGame
{
	Axes axes;
	std::vector<Chess> chesses;
public:
	Axes getAxes() { return axes; }
	std::vector<Chess> getChesses() { return chesses; }
	void InitGame();
	//MainGame();
};

