#pragma once
//#include "CChessDlg.h"

class Axes
{
public:
	Axes();
	~Axes();
	void show(CDC* pDC, CRect rect);
	//CCChessDlg m_dlg;
	static int Window_x;  // �������Ͻǵ�����
	static int Window_y; // �������Ͻǵ�����
	static int GridWidth; // ���̸��ӵĿ��
	static int GridNum; // ���̸��ӵ�����
	static Chess::COLOR turn; // �ֵ�˭��
    std::vector<Chess*> chesses; // ����
	std::vector<std::vector<Chess::COLOR>> chesseboard{ (unsigned int)GridNum, std::vector<Chess::COLOR>(GridNum, Chess::COLOR::NONE) };
	bool AddChess(int x, int y, Chess::COLOR color); // �������
	void DrawChess(CDC* pDC); // ������
	void DrawAxes(CDC* pDC); // ������
	static CPoint TransToGrid(CPoint point); // ����Ļ����ת��Ϊ��������
	static CPoint TransToScreen(CPoint point); // ����������ת��Ϊ��Ļ����
	bool InAxes(CPoint point); // �жϵ��Ƿ��������� ��������Ļ����
	bool Win(Chess::COLOR color); // �ж��Ƿ�ʤ�� ��������ɫ
	void clear(); // �������
	void ComputerAddChess(); // ��������
	// ����
	void Regret();
};

