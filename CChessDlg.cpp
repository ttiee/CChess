
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
	ON_NOTIFY(NM_THEMECHANGED, IDC_COMBO_COLOR, &CCChessDlg::OnNMThemeChangedComboColor)
	ON_CBN_CLOSEUP(IDC_COMBO_COLOR, &CCChessDlg::OnCbnCloseupComboColor)
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
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_COLOR);
		this->game.getAxes()->color = (Axes_color)pComboBox->GetItemData(pComboBox->GetCurSel());
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


void CCChessDlg::OnNMThemeChangedComboColor(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 切换颜色
	*pResult = 0;
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
