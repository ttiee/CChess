#pragma once


class MainGame
{
	Axes* axes;
	//CCChessDlg m_dlg;
	std::vector<Chess> chesses;
public:
	int time = 0;
	enum gameStatus { MENU, PLAYING, END } status;
	Axes* getAxes() { return axes; }
	std::vector<Chess> getChesses() { return chesses; }
	void set_gameStatus(gameStatus status) { this->status = status; }
	gameStatus get_gameStatus() { return status; }
	void InitGame();
	bool click_start(CPoint point, CRect rect);
	//MainGame();
};

