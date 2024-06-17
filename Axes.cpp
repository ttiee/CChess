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
Chess::COLOR Axes::turn = Chess::WHITE;


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
	// ����ͬ��ɫ����
	CPen pen;
	switch (color)
	{
	case BLACK:
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		break;
	case BROWN:
		pen.CreatePen(PS_SOLID, 1, RGB(165, 42, 42));
		break;
	case BLUE:
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		break;
	case RED:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		break;
	case GREEN:
		pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		break;
	case YELLOW:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		break;
	case WHITE:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		break;
	case GRAY:
		pen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
		break;
	case PINK:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 192, 203));
		break;
	case PURPLE:
		pen.CreatePen(PS_SOLID, 1, RGB(128, 0, 128));
		break;
	case ORANGE:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 165, 0));
		break;
	case CYAN:
		pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
		break;
	case MAGENTA:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		break;
	case SILVER:
		pen.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
		break;
	case GOLD:
		pen.CreatePen(PS_SOLID, 1, RGB(255, 215, 0));
		break;
	}

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

bool Axes::AddChess(int x, int y, Chess::COLOR color)
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
		return true;
	}
	else
	{
		return false;
	}
}

void Axes::DrawChess(CDC* pDC)
{
	for (int i = 0; i < this->chesses.size(); i++)
	{
		this->chesses[i]->show(pDC);
	}
}


// ������ʤ���жϣ�����б��5����������
bool Axes::Win(Chess::COLOR color)
{
	int count = 0;
	// ����
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
	// ����
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
	// ���ϵ�����
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
	// ���µ�����
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

//��������
//�����������
//1. ���ȼ�����4 > ��4 > ��3 > ��3 > ��2 > ��2 > ��1 > ��1
// �������ĵ��λ�����ȼ���
void Axes::ComputerAddChess()
{
	int x = 0, y = 0;
	float maxScore = -1.0;
	float score[15][15] = { 0.0 };
	const int center = GridNum / 2;

	// �������ֺ���
	auto evaluateShape = [&](int countBlack, int countWhite, int emptySpaces, bool isCurrent) -> float {
		if (countWhite == 4) return isCurrent ? 10000.0 : 9000.0; // ��ֹ���ӳ�������
		if (countBlack == 4) return isCurrent ? 9000.0 : 8000.0; // ����
		if (countWhite == 3 && emptySpaces == 1) return isCurrent ? 800.0 : 700.0; // ��ֹ���ӻ���
		if (countBlack == 3 && emptySpaces == 1) return isCurrent ? 700.0 : 600.0; // ���ӻ���
		if (countWhite == 3 && emptySpaces > 1) return isCurrent ? 600.0 : 500.0; // ��ֹ����������
		if (countBlack == 3 && emptySpaces > 1) return isCurrent ? 500.0 : 400.0; // ����������
		if (countWhite == 2 && emptySpaces == 1) return isCurrent ? 60.0 : 50.0; // ��ֹ���ӻ���
		if (countBlack == 2 && emptySpaces == 1) return isCurrent ? 50.0 : 40.0; // ���ӻ���
		if (countWhite == 2 && emptySpaces > 1) return isCurrent ? 40.0 : 30.0; // ��ֹ����������
		if (countBlack == 2 && emptySpaces > 1) return isCurrent ? 30.0 : 20.0; // ����������
		if (countWhite == 1) return isCurrent ? 10.0 : 5.0; // ��ֹ���ӻ��
		if (countBlack == 1) return isCurrent ? 5.0 : 3.0; // ���ӻ��

		return 0.0;
		};

	// �ۺ����ֺ���
	auto evaluatePosition = [&](int i, int j, bool isCurrent) -> float {
		float totalScore = 0.0;

		// ������ǰ(i, j)����8�������ϵĵ÷�
		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (dx == 0 && dy == 0) continue;

				int countBlack = 0, countWhite = 0, emptySpaces = 0;
				for (int k = -4; k <= 4; k++)
				{
					int ni = i + k * dx;
					int nj = j + k * dy;

					if (ni >= 0 && ni < GridNum && nj >= 0 && nj < GridNum)
					{
						if (chesseboard[ni][nj] == Chess::BLACK) countBlack++;
						else if (chesseboard[ni][nj] == Chess::WHITE) countWhite++;
						else emptySpaces++;
					}
				}

				totalScore += evaluateShape(countBlack, countWhite, emptySpaces, isCurrent);
			}
		}

		// ����λ�����֣���������λ�õ����ȼ�����
		float distanceToCenter = sqrt((i - center) * (i - center) + (j - center) * (j - center));
		totalScore += 40.0 / (distanceToCenter + 1);

		return totalScore;
		};

	// ��������λ�ã�����ÿ��λ�õĵ÷�
	for (int i = 0; i < GridNum; i++)
	{
		for (int j = 0; j < GridNum; j++)
		{
			if (chesseboard[i][j] != Chess::NONE) continue;

			float currentScore = evaluatePosition(i, j, true);
			float opponentScore = evaluatePosition(i, j, false);

			score[i][j] = currentScore + opponentScore;

			if (score[i][j] > maxScore)
			{
				maxScore = score[i][j];
				x = i;
				y = j;
			}
		}
	}

	// �����������ڵ÷���ߵ�λ��
	AddChess(x, y, Chess::BLACK);
	turn = Chess::WHITE;
}


void Axes::Regret()
{
	if (chesses.size() >= 2)
	{
		chesseboard[chesses[chesses.size() - 1]->GetX()][chesses[chesses.size() - 1]->GetY()] = Chess::NONE;
		chesseboard[chesses[chesses.size() - 2]->GetX()][chesses[chesses.size() - 2]->GetY()] = Chess::NONE;
		delete chesses[chesses.size() - 1];
		delete chesses[chesses.size() - 2];
		chesses.pop_back();
		chesses.pop_back();
		Chess::chess_num -= 2;
	}
	else if (chesses.size() == 1)
	{
		delete chesses[chesses.size() - 1];
		chesses.pop_back();
		Chess::chess_num -= 1;
		chesseboard[chesses[chesses.size() - 1]->GetX()][chesses[chesses.size() - 1]->GetY()] = Chess::NONE;
	}
	else {
		MessageBox(NULL, _T("�޷�����"), _T("��ʾ"), MB_OK);
	}
}















