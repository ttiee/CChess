#pragma once
class Axes
{
public:
	Axes();
	~Axes();
	void show(CDC* pDC);
	static int Window_x;  // �������Ͻǵ�����
	static int Window_y; // �������Ͻǵ�����
	static int GridWidth; // ���̸��ӵĿ��
	static int GridNum; // ���̸��ӵ�����
	void DrawAxes(CDC* pDC);
	static CPoint TransToGrid(CPoint point); // ����Ļ����ת��Ϊ��������
	static CPoint TransToScreen(CPoint point); // ����������ת��Ϊ��Ļ����
	bool InAxes(CPoint point); // �жϵ��Ƿ��������� ��������Ļ����
};

