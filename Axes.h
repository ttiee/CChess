#pragma once
//#include "CChessDlg.h"

class Axes
{
public:
	Axes();
	~Axes();
	void show(CDC* pDC, CRect rect);
	//CCChessDlg m_dlg;
	static int Window_x;  // 窗口左上角的坐标
	static int Window_y; // 窗口左上角的坐标
	static int GridWidth; // 棋盘格子的宽度
	static int GridNum; // 棋盘格子的数量
	static Chess::COLOR turn; // 轮到谁下
    std::vector<Chess*> chesses; // 棋子
	std::vector<std::vector<Chess::COLOR>> chesseboard{ (unsigned int)GridNum, std::vector<Chess::COLOR>(GridNum, Chess::COLOR::NONE) };
	bool AddChess(int x, int y, Chess::COLOR color); // 添加棋子
	void DrawChess(CDC* pDC); // 画棋子
	void DrawAxes(CDC* pDC); // 画棋盘
	static CPoint TransToGrid(CPoint point); // 将屏幕坐标转换为棋盘坐标
	static CPoint TransToScreen(CPoint point); // 将棋盘坐标转换为屏幕坐标
	bool InAxes(CPoint point); // 判断点是否在棋盘内 参数：屏幕坐标
	bool Win(Chess::COLOR color); // 判断是否胜利 参数：颜色
	void clear(); // 清空棋盘
	void ComputerAddChess(); // 电脑下棋
	// 悔棋
	void Regret();
};

