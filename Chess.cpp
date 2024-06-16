#include "pch.h"
#include "Chess.h"
#include "resource.h"


int Chess::Window_x = Axes::Window_x;
int Chess::Window_y = Axes::Window_y;
int Chess::GridWidth = Axes::GridWidth;
int Chess::chess_num = 0;

Chess::Chess()
{
	num = 0;
	x = 0;
	y = 0;
	color = Chess::WHITE;
}

Chess::~Chess()
{

}

void Chess::Set(int num, int x, int y, Chess::COLOR color)
{
	this->num = num;
	this->x = x;
	this->y = y;
	this->color = color;
}

void Chess::show(CDC* pDC)
{
	CBitmap bmp_mask;
	bmp_mask.LoadBitmap(IDB_BITMAP_MASK);
	CBitmap bmp_chess;
	if (color == WHITE)
	{
		bmp_chess.LoadBitmap(IDB_BITMAP_BZ);
	}
	else
	{
		bmp_chess.LoadBitmap(IDB_BITMAP_HZ);
	}
	CDC dc;
	dc.CreateCompatibleDC(NULL);
	CBitmap* pOldBmp = dc.SelectObject(&bmp_mask);
	BITMAP bmpInfo;
	bmp_mask.GetBitmap(&bmpInfo);
	CPoint point{x, y};
	point = Axes::TransToScreen(point);
	pDC->BitBlt(point.x - chess_size / 2, point.y - chess_size / 2, chess_size, chess_size, &dc, 0, 0, SRCAND);
	dc.SelectObject(&bmp_chess);
	bmp_chess.GetBitmap(&bmpInfo);
	pDC->BitBlt(point.x - chess_size / 2, point.y - chess_size / 2, chess_size, chess_size, &dc, 0, 0, SRCPAINT);
	dc.SelectObject(pOldBmp);
	bmp_mask.DeleteObject();
	bmp_chess.DeleteObject();
	dc.DeleteDC();

	Chess::chess_num++;
}