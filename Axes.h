#pragma once
class Axes
{
public:
	Axes();
	~Axes();
	void show(CDC* pDC);
	static int Window_x;  // 窗口左上角的坐标
	static int Window_y; // 窗口左上角的坐标
	static int GridWidth; // 棋盘格子的宽度
	static int GridNum; // 棋盘格子的数量
	void DrawAxes(CDC* pDC);
	static CPoint TransToGrid(CPoint point); // 将屏幕坐标转换为棋盘坐标
	static CPoint TransToScreen(CPoint point); // 将棋盘坐标转换为屏幕坐标
	bool InAxes(CPoint point); // 判断点是否在棋盘内 参数：屏幕坐标
};

