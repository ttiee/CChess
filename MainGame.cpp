#include "pch.h"
#include "MainGame.h"

void MainGame::InitGame()
{
	axes = new Axes();
	this->axes = axes;
	axes->clear();
	status = MENU;
	this->axes->turn = Chess::COLOR::WHITE;
	// ÉèÖÃ¼ÆÊ±Æ÷
	//time = 0;
}


bool MainGame::click_start(CPoint point, CRect rect)
{
	if (point.x > rect.Width() / 50 && point.x < rect.Width() / 5 && point.y > rect.Height() * 3 / 16 && point.y < rect.Height() / 4)
	{
		return true;
	}
	return false;
}