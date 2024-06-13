#include "pch.h"
#include "Axes.h"
#include "Chess.h"
#include "CChess.h"
#include "CChessDlg.h"
#include "resource.h"

int Axes::Window_x = CCChessDlg::Window_Width * 0.25 / 1;
int Axes::Window_y = CCChessDlg::Window_Height * 0.1 / 1;
int Axes::GridWidth = CCChessDlg::Window_Height / 23;
int Axes::GridNum = 15;

Axes::Axes()
{
}

Axes::~Axes()
{
}

void Axes::show(CDC* pDC)
{
	DrawAxes(pDC);
}

void Axes::DrawAxes(CDC* pDC)
{
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < GridNum; i++)
	{
		pDC->MoveTo(Window_x, Window_y + i * GridWidth);
		pDC->LineTo(Window_x + (GridNum - 1) * GridWidth, Window_y + i * GridWidth);
	}
	for (int i = 0; i < GridNum; i++)
	{
		pDC->MoveTo(Window_x + i * GridWidth, Window_y);
		pDC->LineTo(Window_x + i * GridWidth, Window_y + (GridNum - 1) * GridWidth);
	}
	pDC->SelectObject(pOldPen);
}

CPoint Axes::TransToGrid(CPoint point)
{
	CPoint grid;
	grid.x = (point.x - Window_x + GridWidth / 2) / GridWidth;
	grid.y = (point.y - Window_y + GridWidth / 2) / GridWidth;
	return grid;
}

CPoint Axes::TransToScreen(CPoint point)
{
	CPoint screen;
	screen.x = point.x * GridWidth + Window_x;
	screen.y = point.y * GridWidth + Window_y;
	return screen;
}

bool Axes::InAxes(CPoint point)
{
	if (point.x < Window_x || point.x > Window_x + (GridNum - 1) * GridWidth)
	{
		return false;
	}
	if (point.y < Window_y || point.y > Window_y + (GridNum - 1) * GridWidth)
	{
		return false;
	}
	return true;
}