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
	static int chess_num; // ��������
private:
	int num; // ���
	int x; // ������
	int y; // ������
	int chess_size = 36; // ���Ӵ�С
	Chess::COLOR color; // ��ɫ
public:

	Chess();
	~Chess();
	void Set(int num, int x, int y, Chess::COLOR color);
	int GetColor() { return color; }
	int GetX() { return x; }
	int GetY() { return y; }
	void show(CDC* pDC);
	static int Window_x;  // �������Ͻǵ�����
	static int Window_y; // �������Ͻǵ�����
	static int GridWidth; // ���̸��ӵĿ��

};

