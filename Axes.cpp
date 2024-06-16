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

void Axes::show(CDC* pDC, CRect rect)
{
	//CRect rect;
	////CCChessDlg::Get_Window_Rect(&rect);
	this->Window_x = rect.Width() * 0.25 / 1;
	this->Window_y = rect.Height() * 0.1 / 1;
	this->GridWidth = (((rect.Width()) < (rect.Height())) ? (rect.Width()) : (rect.Height())) / 23;

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

void Axes::AddChess(int x, int y, Chess::COLOR color)
{
	//x++;
	//y++;
	if ((chesseboard[x][y] != Chess::BLACK) && (chesseboard[x][y] != Chess::WHITE))
	{
		Chess* chess = new Chess();
		chess->Set(Chess::chess_num, x, y, color);
		this->chesses.push_back(chess);
		Chess::chess_num++;
		chesseboard[x][y] = color;
	} 
	else
	{
	}
}

void Axes::DrawChess(CDC* pDC)
{
	for (int i = 0; i < this->chesses.size(); i++)
	{
		this->chesses[i]->show(pDC);
	}
}


// 五子棋胜利判断，横竖斜向5个棋子相连
bool Axes::Win(Chess::COLOR color)
{
	int count = 0;
	// 横向
	for (int i = 0; i < GridNum; i++)
	{
		count = 0;
		for (int j = 0; j < GridNum; j++)
		{
			if (chesseboard[i][j] == color)
			{
				count++;
				if (count == 5)
				{
					return true;
				}
			}
			else
			{
				count = 0;
			}
		}
	}
	// 纵向
	for (int i = 0; i < GridNum; i++)
	{
		count = 0;
		for (int j = 0; j < GridNum; j++)
		{
			if (chesseboard[j][i] == color)
			{
				count++;
				if (count == 5)
				{
					return true;
				}
			}
			else
			{
				count = 0;
			}
		}
	}
	// 左上到右下
	for (int i = 0; i < GridNum; i++)
	{
		count = 0;
		for (int j = 0; j < GridNum - i; j++)
		{
			if (chesseboard[j][j + i] == color)
			{
				count++;
				if (count == 5)
				{
					return true;
				}
			}
			else
			{
				count = 0;
			}
		}
	}
	for (int i = 1; i < GridNum; i++)
	{
		count = 0;
		for (int j = 0; j < GridNum - i; j++)
		{
			if (chesseboard[j + i][j] == color)
			{
				count++;
				if (count == 5)
				{
					return true;
				}
			}
			else
			{
				count = 0;
			}
		}
	}
	// 左下到右上
	for (int i = 0; i < GridNum; i++)
	{
		count = 0;
		for (int j = 0; j <= i; j++)
		{
			if (chesseboard[j][i - j] == color)
			{
				count++;
				if (count == 5)
				{
					return true;
				}
			}
			else
			{
				count = 0;
			}
		}
	}
	for (int i = 1; i < GridNum; i++)
	{
		count = 0;
		for (int j = 0; j < GridNum - i; j++)
		{
			if (chesseboard[j + i][GridNum - 1 - j] == color)
			{
				count++;
				if (count == 5)
				{
					return true;
				}
			}
			else
			{
				count = 0;
			}
		}
	}
	return false;
}

void Axes::clear()
{
	for (int i = 0; i < this->chesses.size(); i++)
	{
		delete this->chesses[i];
	}
	this->chesses.clear();
	Chess::chess_num = 0;
}