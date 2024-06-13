#pragma once
#include "Axes.h"

class Chess
{
public:
	enum COLOR
	{
		WHITE,
		BLACK
	};
	static int chess_num; // 棋子数量
private:
	int num; // 序号
	int x; // 横坐标
	int y; // 纵坐标
	int chess_size = 36; // 棋子大小
	Chess::COLOR color; // 颜色
public:

	Chess();
	~Chess();
	void Set(int num, int x, int y, Chess::COLOR color);
	int GetColor() { return color; }
	int GetX() { return x; }
	int GetY() { return y; }
	void show(CDC* pDC);
	static int Window_x;  // 窗口左上角的坐标
	static int Window_y; // 窗口左上角的坐标
	static int GridWidth; // 棋盘格子的宽度

};

