﻿
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
public:
	afx_msg void OnBnClickedButtonSource();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, &CAboutDlg::OnBnClickedButtonSource)
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
	//ON_NOTIFY(NM_THEMECHANGED, IDC_COMBO_COLOR, &CCChessDlg::OnNMThemeChangedComboColor)
	ON_CBN_CLOSEUP(IDC_COMBO_COLOR, &CCChessDlg::OnCbnCloseupComboColor)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUM, &CCChessDlg::OnDeltaposSpinNum)
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

	// 设置combo box
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_COLOR);
	pComboBox->ResetContent();

	// 按照拼音首字母顺序添加颜色项并设置对应的数据
	pComboBox->AddString(_T("白色"));    // index 0
	pComboBox->SetItemData(0, (DWORD_PTR)WHITE);

	pComboBox->AddString(_T("橙色"));    // index 1
	pComboBox->SetItemData(1, (DWORD_PTR)ORANGE);

	pComboBox->AddString(_T("粉色"));    // index 2
	pComboBox->SetItemData(2, (DWORD_PTR)PINK);

	pComboBox->AddString(_T("黑色"));    // index 3
	pComboBox->SetItemData(3, (DWORD_PTR)BLACK);

	pComboBox->AddString(_T("红色"));    // index 4
	pComboBox->SetItemData(4, (DWORD_PTR)RED);

	pComboBox->AddString(_T("黄色"));    // index 5
	pComboBox->SetItemData(5, (DWORD_PTR)YELLOW);

	pComboBox->AddString(_T("灰色"));    // index 6
	pComboBox->SetItemData(6, (DWORD_PTR)GRAY);

	pComboBox->AddString(_T("金色"));    // index 7
	pComboBox->SetItemData(7, (DWORD_PTR)GOLD);

	pComboBox->AddString(_T("蓝色"));    // index 8
	pComboBox->SetItemData(8, (DWORD_PTR)BLUE);

	pComboBox->AddString(_T("绿色"));    // index 9
	pComboBox->SetItemData(9, (DWORD_PTR)GREEN);

	pComboBox->AddString(_T("品红色"));  // index 10
	pComboBox->SetItemData(10, (DWORD_PTR)MAGENTA);

	pComboBox->AddString(_T("青色"));    // index 11
	pComboBox->SetItemData(11, (DWORD_PTR)CYAN);

	pComboBox->AddString(_T("银色"));    // index 12
	pComboBox->SetItemData(12, (DWORD_PTR)SILVER);

	pComboBox->AddString(_T("紫色"));    // index 13
	pComboBox->SetItemData(13, (DWORD_PTR)PURPLE);

	pComboBox->AddString(_T("棕色"));    // index 14
	pComboBox->SetItemData(14, (DWORD_PTR)BROWN);

	pComboBox->SetCurSel(3); // 默认选择第一个


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
		CPaintDC clientDC(this);
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
				CBitmap bmp_win;
				bmp_win.LoadBitmap(IDB_BITMAP_WIN);
				CDC winDC;
				winDC.CreateCompatibleDC(&clientDC);
				CBitmap* pOldBmp = winDC.SelectObject(&bmp_win);
				BITMAP bmpInfo;
				bmp_win.GetBitmap(&bmpInfo);
				memDC.StretchBlt(rect.Width() * 0.25 / 1, rect.Height() * 0.1 / 1, rect.Width() / 2, rect.Height() / 2, &winDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
				winDC.SelectObject(pOldBmp);
				bmp_win.DeleteObject();
			}
			else if (this->game.getAxes()->Win(Chess::BLACK))
			{
				CBitmap bmp_lose;
				bmp_lose.LoadBitmap(IDB_BITMAP_LOSE);
				CDC loseDC;
				loseDC.CreateCompatibleDC(&clientDC);
				CBitmap* pOldBmp = loseDC.SelectObject(&bmp_lose);
				BITMAP bmpInfo;
				bmp_lose.GetBitmap(&bmpInfo);
				memDC.StretchBlt(rect.Width() * 0.25 / 1, rect.Height() * 0.1 / 1, rect.Width() / 2, rect.Height() / 2, &loseDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
				loseDC.SelectObject(pOldBmp);
				bmp_lose.DeleteObject();
			}
		}

		// 显示时间
		CString timeStr;
		timeStr.Format(_T("%d s"), this->game.time);
		memDC.SetTextColor(RGB(0, 0, 0));
		memDC.SetBkMode(TRANSPARENT);
		memDC.TextOutW(rect.Width() * 12 / 17, rect.Height() / 22, timeStr);

		// 显示GridNum
		CString gridNumStr;
		gridNumStr.Format(_T("%d"), this->game.getAxes()->GridNum);
		memDC.SetTextColor(RGB(0, 0, 0));
		memDC.SetBkMode(TRANSPARENT);
		memDC.TextOutW(rect.Width() * 0.87, rect.Height() / 6, gridNumStr);

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

		// 绘制 IDD_BUTTON_REGRET 按钮控件
		CWnd* pButton = GetDlgItem(IDD_BUTTON_REGRET);
		if (pButton)
		{
			CRect buttonRect;
			pButton->GetWindowRect(&buttonRect);
			ScreenToClient(&buttonRect);

			CDC buttonDC;
			buttonDC.CreateCompatibleDC(&clientDC);
			CBitmap buttonBitmap;
			buttonBitmap.CreateCompatibleBitmap(&clientDC, buttonRect.Width(), buttonRect.Height());
			CBitmap* pOldButtonBmp = buttonDC.SelectObject(&buttonBitmap);

			pButton->Print(&buttonDC, PRF_CLIENT | PRF_ERASEBKGND);

			memDC.BitBlt(buttonRect.left, buttonRect.top, buttonRect.Width(), buttonRect.Height(), &buttonDC, 0, 0, SRCCOPY);

			buttonDC.SelectObject(pOldButtonBmp);
			buttonBitmap.DeleteObject();
			buttonDC.DeleteDC();
		}

		// 绘制 IDC_COMBO_COLOR 组合框控件
		CWnd* pComboBox = GetDlgItem(IDC_COMBO_COLOR);
		if (pComboBox)
		{
			CRect comboRect;
			pComboBox->GetWindowRect(&comboRect);
			ScreenToClient(&comboRect);

			CDC comboDC;
			comboDC.CreateCompatibleDC(&clientDC);
			CBitmap comboBitmap;
			comboBitmap.CreateCompatibleBitmap(&clientDC, comboRect.Width(), comboRect.Height());
			CBitmap* pOldComboBmp = comboDC.SelectObject(&comboBitmap);

			pComboBox->Print(&comboDC, PRF_CLIENT | PRF_ERASEBKGND);

			memDC.BitBlt(comboRect.left, comboRect.top, comboRect.Width(), comboRect.Height(), &comboDC, 0, 0, SRCCOPY);

			comboDC.SelectObject(pOldComboBmp);
			comboBitmap.DeleteObject();
			comboDC.DeleteDC();
		}
		// 绘制 IDC_SPIN_NUM 控件
		CWnd* pSpin = GetDlgItem(IDC_SPIN_NUM);
		if (pSpin)
		{
			CRect spinRect;
			pSpin->GetWindowRect(&spinRect);
			ScreenToClient(&spinRect);

			CDC spinDC;
			spinDC.CreateCompatibleDC(&clientDC);
			CBitmap spinBitmap;
			spinBitmap.CreateCompatibleBitmap(&clientDC, spinRect.Width(), spinRect.Height());
			CBitmap* pOldSpinBmp = spinDC.SelectObject(&spinBitmap);

			pSpin->Print(&spinDC, PRF_CLIENT | PRF_ERASEBKGND);

			memDC.BitBlt(spinRect.left, spinRect.top, spinRect.Width(), spinRect.Height(), &spinDC, 0, 0, SRCCOPY);

			spinDC.SelectObject(pOldSpinBmp);
			spinBitmap.DeleteObject();
			spinDC.DeleteDC();
		}

		// 将内存 DC 的内容拷贝到屏幕 DC
		clientDC.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		// 清理
		memDC.SelectObject(oldBitmap);
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


	// 判断是否点击开始按钮
	if (CCChessDlg::game.click_start(point, rect) && CCChessDlg::game.get_gameStatus() != MainGame::PLAYING)
	{
		CCChessDlg::game.InitGame();
		CCChessDlg::game.set_gameStatus(MainGame::PLAYING);
		CCChessDlg::game.time = 0;
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_COLOR);
		this->game.getAxes()->color = (Axes_color)pComboBox->GetItemData(pComboBox->GetCurSel());
		// 强制窗口重绘
		Invalidate();
		UpdateWindow();
		// 播放音乐
		SoundManager::PlayStartSound();
	}
	else if (CCChessDlg::game.click_about(point, rect))
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
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
			SoundManager::PlayWinSound();
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
				SoundManager::PlayLoseSound();
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


void CCChessDlg::OnCbnCloseupComboColor()
{
	// 切换坐标系颜色
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_COLOR);
	int index = pComboBox->GetCurSel();
	if (index != CB_ERR)
	{
		DWORD_PTR data = pComboBox->GetItemData(index);
		this->game.getAxes()->color = (Axes_color)data;
		Invalidate();
	}
}


void CAboutDlg::OnBnClickedButtonSource()
{
	// 跳转到源代码页面
	ShellExecute(NULL, _T("open"), _T("https://github.com/ttiee/CChess.git"), NULL, NULL, SW_SHOWNORMAL);

}


void CCChessDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// 鼠标悬停范围，改变鼠标样式
	CRect rect;
	GetClientRect(&rect);
	if (CCChessDlg::game.click_start(point, rect) || CCChessDlg::game.click_about(point, rect))
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
	}
	else
	{
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}


	CDialogEx::OnMouseMove(nFlags, point);
}


void CCChessDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// 调整button大小
	CWnd* pWnd = GetDlgItem(IDD_BUTTON_REGRET);
	if (pWnd)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.left = cx / 50;
		rect.right = cx / 5;
		rect.top = cy / 3;
		rect.bottom = cy * 2 / 5;
		pWnd->MoveWindow(&rect);
	}

	// 调整combo box大小
	CWnd* pWnd2 = GetDlgItem(IDC_COMBO_COLOR);
	if (pWnd2)
	{
		CRect rect;
		pWnd2->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.left = cx / 50;
		rect.right = cx / 5;
		rect.top = cy * 11 / 26;
		rect.bottom = cy * 13 / 25;
		pWnd2->MoveWindow(&rect);
	}
	// 调整spin控件大小
	CWnd* pWnd3 = GetDlgItem(IDC_SPIN_NUM);
	if (pWnd3)
	{
		CRect rect;
		pWnd3->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.left = cx * 0.86;
		rect.right = cx * 0.9;
		rect.top = cy * 0.2;
		rect.bottom = cy * 0.3;
		pWnd3->MoveWindow(&rect);
	}

	Invalidate();
	UpdateWindow();
}


void CCChessDlg::OnClose()
{
	SoundManager::PlayCloseSound();

	timeKillEvent(1);	// 关闭定时器
	//timeKillEvent(2);	// 关闭定时器

	MessageBox(_T("感谢游玩！"), _T("CChess"), MB_OK | MB_ICONINFORMATION);


	CDialogEx::OnClose();
}


void CCChessDlg::OnDeltaposSpinNum(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// 调整Axex的GridNum
	if (pNMUpDown->iDelta < 0)	// 向上滚动
	{
		if (this->game.getAxes()->GridNum < 15)
		{
			this->game.getAxes()->GridNum++;
		}
	}
	else
	{
		if (this->game.getAxes()->GridNum > 5)
		{
			this->game.getAxes()->GridNum--;
		}
	}
	Invalidate();

	*pResult = 0;
}
