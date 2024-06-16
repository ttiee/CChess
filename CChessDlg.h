
// CChessDlg.h: 头文件
//

#pragma once



// CCChessDlg 对话框
class CCChessDlg : public CDialogEx
{
	// 构造
public:
	CCChessDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CRect Get_Window_Rect();
	static MainGame game;
	static int Window_Width; // 窗口宽度
	static int Window_Height; // 窗口高度

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCHESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	BOOL OnEraseBkgnd(CDC* pDC);
};
