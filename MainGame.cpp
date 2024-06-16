#include "pch.h"
#include "MainGame.h"

void MainGame::InitGame()
{
	axes = new Axes();
	this->axes = axes;
	axes->clear();
	status = PLAYING;
}
