
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
	// 定时器
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND() // 擦除背景
	//ON_BN_CLICKED(IDC_BUTTON1, &CCChessDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDD_BUTTON_REGRET, &CCChessDlg::OnBnClickedButtonRegret)
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
	//this->game = game;
	this->game = MainGame();
	this->game.InitGame();

	// 设置定时器
	if (!SetTimer(1, 1000, NULL))
	{
		AfxMessageBox(_T("计时器设置失败！"));
	}
	/*if (!SetTimer(2, 10, NULL))
	{
		AfxMessageBox(_T("计时器设置失败！"));
	}*/


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
		// 创建内存 DC
		CClientDC clientDC(this);
		CRect rect;
		GetClientRect(&rect);

		// 创建内存 DC 和兼容位图
		CDC memDC;
		memDC.CreateCompatibleDC(&clientDC);
		CBitmap memBitmap;
		memBitmap.CreateCompatibleBitmap(&clientDC, rect.Width(), rect.Height());
		CBitmap* oldBitmap = memDC.SelectObject(&memBitmap);

		// 用背景色填充内存 DC
		memDC.FillSolidRect(&rect, RGB(255, 255, 255));

		// 绘制背景
		CBitmap bmp_bk;
		bmp_bk.LoadBitmap(IDB_BITMAP_BK_B); // 加载位图资源
		CDC bgDC;
		bgDC.CreateCompatibleDC(&clientDC);
		CBitmap* pOldBmp = bgDC.SelectObject(&bmp_bk);
		BITMAP bmpInfo;
		bmp_bk.GetBitmap(&bmpInfo);
		memDC.StretchBlt(0, 0, rect.Width(), rect.Height(), &bgDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		bgDC.SelectObject(pOldBmp);
		bmp_bk.DeleteObject();

		if (game.get_gameStatus() == MainGame::PLAYING)
		{
			// 画棋盘
			this->game.getAxes()->show(&memDC, rect);

			// 画棋子
			this->game.getAxes()->DrawChess(&memDC);
		}

		// 画胜利线
		if (game.get_gameStatus() == MainGame::END)
		{
			if (this->game.getAxes()->Win(Chess::WHITE))
			{
				// 画胜利线
				CString str = _T("白方胜利！");
				memDC.SetTextColor(RGB(0, 0, 0));
				memDC.SetBkMode(TRANSPARENT);
				memDC.TextOutW(rect.Width() / 2, rect.Height() / 2, str);
				//MessageBox(_T("白方胜利！"));
			}
			else if (this->game.getAxes()->Win(Chess::BLACK))
			{
				// 画胜利线
				CString str = _T("黑方胜利！");
				memDC.SetTextColor(RGB(0, 0, 0));
				memDC.SetBkMode(TRANSPARENT);
				memDC.TextOutW(rect.Width() / 2, rect.Height() / 2, str);

			}
		}

		// 显示时间
		CString timeStr;
		timeStr.Format(_T("%d s"), this->game.time);
		memDC.SetTextColor(RGB(0, 0, 0));
		memDC.SetBkMode(TRANSPARENT);
		memDC.TextOutW(rect.Width() * 12 / 17, rect.Height() / 22, timeStr);

		// 显示turn
		CString turnStr;
		if (this->game.getAxes()->turn == Chess::WHITE)
		{
			turnStr = _T("白方");
		}
		else
		{
			turnStr = _T("黑方");
		}
		memDC.SetTextColor(RGB(0, 0, 0));
		memDC.SetBkMode(TRANSPARENT);
		memDC.TextOutW(rect.Width() * 12 / 16, rect.Height() / 13, turnStr);


		// 将内存 DC 的内容拷贝到屏幕 DC
		clientDC.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		// 清理
		memDC.SelectObject(oldBitmap);

		// 删除 GDI 对象
		memBitmap.DeleteObject();
		memDC.DeleteDC();

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
	// 获取窗口大小
	CRect rect;
	GetClientRect(&rect);
	if (CCChessDlg::game.click_start(point, rect) && CCChessDlg::game.get_gameStatus() != MainGame::PLAYING)
	{
		CCChessDlg::game.InitGame();
		CCChessDlg::game.set_gameStatus(MainGame::PLAYING);
		CCChessDlg::game.time = 0;
		Invalidate();
	}


	if ((CCChessDlg::game.get_gameStatus() == MainGame::PLAYING) && (CCChessDlg::game.getAxes()->turn == Chess::WHITE))
	{
		if (!CCChessDlg::game.getAxes()->InAxes(point))
		{
			return;
		}
		point = Axes::TransToGrid(point);
		if (CCChessDlg::game.getAxes()->AddChess(point.x, point.y, Chess::WHITE)) {
			CCChessDlg::game.getAxes()->turn = Chess::BLACK;
		}

		// 胜利
		if (CCChessDlg::game.getAxes()->Win(Chess::WHITE))
		{
			// 显示胜利信息, 询问是否重新开始
			AfxMessageBox(_T("白方胜利！"), MB_OK | MB_ICONINFORMATION);

			CCChessDlg::game.set_gameStatus(MainGame::END);

			// 重新开始
			//CCChessDlg::game.InitGame();
			//Invalidate();
		}

		// 电脑下棋
		if (this->game.get_gameStatus() == MainGame::PLAYING && this->game.getAxes()->turn == Chess::BLACK)
		{
			this->game.getAxes()->ComputerAddChess();
			this->game.getAxes()->turn = Chess::WHITE;

			// 胜利
			if (CCChessDlg::game.getAxes()->Win(Chess::BLACK))
			{
				// 显示胜利信息, 询问是否重新开始
				AfxMessageBox(_T("黑方胜利！"), MB_OK | MB_ICONINFORMATION);
				CCChessDlg::game.set_gameStatus(MainGame::END);
			}
		}
		
	}
	// 强制窗口重绘
	Invalidate();
	UpdateWindow();

	//AfxMessageBox(_T("Hello, World!"));

	CDialogEx::OnLButtonUp(nFlags, point);
}


CRect CCChessDlg::Get_Window_Rect()
{
	CRect rect;
	GetWindowRect(&rect);
	return rect;
}

BOOL CCChessDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; // 不擦除背景, 以便重绘背景
}

void CCChessDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(_T("Hello, World!"));
	//this->game.time++;
	switch (nIDEvent)
	{
	case 1:
		if (this->game.get_gameStatus() == MainGame::PLAYING)
		{
			this->game.time++;
		}


		Invalidate();
		//AfxMessageBox(_T("Hello, World!"));
		break;
	case 2:

		//Invalidate();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCChessDlg::OnBnClickedButtonRegret()
{
	this->game.getAxes()->Regret();
	Invalidate();
}
