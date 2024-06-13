
// CChessDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"

#include "CChessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int CCChessDlg::Window_Width = 1000; // 窗口宽度
int CCChessDlg::Window_Height = 800; // 窗口高度

MainGame game;
MainGame CCChessDlg::game = game;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCChessDlg 对话框



CCChessDlg::CCChessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CCHESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCChessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CCChessDlg 消息处理程序

BOOL CCChessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// 设置窗口大小
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(0, 0, Window_Width, Window_Height);

	// 设置窗口标题
	SetWindowText(_T("CChess"));

	// 初始化游戏
	this->game = game;
	this->game.InitGame();


	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCChessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBitmap bmp_bk;
		bmp_bk.LoadBitmap(IDB_BITMAP_BK_B); //加载位图资源
		CDC dc;
		dc.CreateCompatibleDC(NULL); //创建兼容DC
		CBitmap* pOldBmp = dc.SelectObject(&bmp_bk); //将位图选入DC
		BITMAP bmpInfo;
		bmp_bk.GetBitmap(&bmpInfo);
		CRect rect;
		GetClientRect(&rect);
		CDC* pDC = GetDC();
		pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		dc.SelectObject(pOldBmp);
		bmp_bk.DeleteObject();

		this->game.getAxes().show(pDC);

		ReleaseDC(pDC);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCChessDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDC* pDC = GetDC();
	Chess chess;
	if (!CCChessDlg::game.getAxes().InAxes(point))
	{
		ReleaseDC(pDC);
		return;
	}
	point = Axes::TransToGrid(point);
	chess.Set(Chess::chess_num, point.x, point.y, Chess::WHITE);
	chess.show(pDC);



	ReleaseDC(pDC);

	//AfxMessageBox(_T("Hello, World!"));

	CDialogEx::OnLButtonUp(nFlags, point);
}
