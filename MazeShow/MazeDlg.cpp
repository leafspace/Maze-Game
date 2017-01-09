
// MazeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Maze.h"
#include "MazeDlg.h"
#include "afxdialogex.h"
#include "PublicResources_Header.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LinkList FeasibleList;                                                       //表示可以行走的点列
TreeMaze LabyrinthTree;                                                      //行走路线树
Point CavalierPoint;                                                         //骑士所在的位置
Point PrincessPoint;                                                         //公主所在的位置
TreeMaze FindPrincess;                                                       //找到公主的方法

CString walkWay;
int ARRAY_SIZE = 10;                                                   //定义地图的大小
char** MAP;

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


// CMazeDlg 对话框



CMazeDlg::CMazeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAZE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMazeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMazeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CMazeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMazeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMazeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMazeDlg::OnBnClickedButton4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CMazeDlg::OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_EDIT2, &CMazeDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMazeDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMazeDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CMazeDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMazeDlg::OnEnChangeEdit6)	
END_MESSAGE_MAP()


// CMazeDlg 消息处理程序

BOOL CMazeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	this->repaint = true;

	MAP = new char*[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		MAP[i] = new char[ARRAY_SIZE];
	}
	char initMAP[10][10] = {                                   //定义地图的数据
		{ '1','1','1','1','1','1','1','1','1','1' },
		{ '1','0','0','1','0','0','0','1','0','#' },
		{ '1','0','0','1','0','0','0','1','0','1' },
		{ '1','0','0','0','0','1','1','0','0','1' },
		{ '1','0','1','1','1','0','0','0','0','1' },
		{ '1','0','0','P','1','0','0','0','0','1' },
		{ '1','0','1','0','0','0','1','0','0','1' },
		{ '1','0','1','1','1','0','1','1','0','1' },
		{ '1','1','0','0','0','0','0','0','0','1' },
		{ '1','1','1','1','1','1','1','1','1','1' },
	};
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			MAP[i][j] = initMAP[i][j];
		}
	}

	DoMaze();
	CString str;
	GetDlgItem(IDC_EDIT1)->SetWindowText(walkWay);
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("10"));

	str.Format(_T("%d"), CavalierPoint.GetX());
	GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	str.Format(_T("%d"), CavalierPoint.GetY());
	GetDlgItem(IDC_EDIT4)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetX());
	GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetY());
	GetDlgItem(IDC_EDIT6)->SetWindowText(str);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMazeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMazeDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}

	if (repaint) {                                                           //repaint作为重绘标识符，首次执行时重绘触发器失败，等开始重绘时触发重绘
		Repaint();                                                           //重绘所需要的操作
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMazeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMazeDlg::OnLButtonDown(UINT nID, CPoint point)
{
	CWnd* pWnd;
	CRect rc;
	CDC* pdc;
	pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetWindowRect(rc);
	pdc = pWnd->GetDC();
	int width = rc.Width();
	int height = rc.Height();
	int rectWidth = (width - 5) / ARRAY_SIZE;
	int rectHeight = (height - 17) / ARRAY_SIZE;

	if (point.x < 9 || point.x>9 + width || point.y < 10 || point.y>10 + height) {
		return;
	}
	else {
		int tempX = point.x - 9 - 5;
		int tempY = point.y - 10 - 17;
		tempX /= rectWidth;
		tempY /= rectHeight;
		if (MAP[tempY][tempX] == '1') {
			MAP[tempY][tempX] = '0';
		}
		else if (MAP[tempY][tempX] == '0') {
			MAP[tempY][tempX] = '1';
		}
		repaint = true;
		walkWay = "";
		DoMaze();
		GetDlgItem(IDC_EDIT1)->SetWindowText(walkWay);
		InvalidateRect(NULL, true);                                                //设置窗口无效
		UpdateWindow();                                                            //立即重绘，触发WM_PAINT
	}

}

void CMazeDlg::Repaint()
{
	CPaintDC dc(this);                                                       //准备参数
	CWnd* pWnd;
	CRect rc;
	CDC* pdc;
	CPen newPen;                                                               //用于创建新画笔   
	CPen *pOldPen;                                                             //用于存放旧画笔   

	pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetWindowRect(rc);
	pdc = pWnd->GetDC();
	int width = rc.Width();
	int height = rc.Height();

	CDC MemDC;                                                                 //首先定义一个显示设备对象   
	CBitmap MemBitmap;                                                         //定义一个位图对象
	MemDC.CreateCompatibleDC(NULL);                                            //随后建立与屏幕显示兼容的内存显示设备
	MemBitmap.CreateCompatibleBitmap(pdc, width, height);                      //下面建立一个与屏幕显示兼容的位图
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);                         //将位图选入到内存显示设备中//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	MemDC.FillSolidRect(0, 0, width, height, RGB(240, 240, 240));              //先用背景色将位图清除干净
	MemDC.Rectangle(5, 17, width - 5, height - 5);

	int rectWidth = (width - 5) / ARRAY_SIZE;
	int rectHeight = (height - 17) / ARRAY_SIZE;


	for (int i = 0; i < ARRAY_SIZE; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			int tempX = 5 + j*rectWidth;
			int tempY = 17 + i*rectHeight;
			rc.SetRect(tempX, tempY, tempX + rectWidth, tempY + rectHeight);
			if (MAP[i][j] == '1') {
				MemDC.FillSolidRect(&rc, RGB(140, 80, 30));
			}
			else if (MAP[i][j] == '0') {
				MemDC.FillSolidRect(&rc, RGB(170, 170, 170));
			}
			else if (MAP[i][j] == 'P') {
				this->SetBMPfile(&MemDC, rc, 'P');
			}
			else {
				this->SetBMPfile(&MemDC, rc, '#');
			}
		}
	}

	newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));                               //创建实心画笔，粗度为1，颜色为黑色
	pOldPen = MemDC.SelectObject(&newPen);                                     //选择新画笔，并将旧画笔的指针保存到pOldPen

	for (int i = 1; i < ARRAY_SIZE; ++i) {
		MemDC.MoveTo(5 + i*rectWidth, 17);
		MemDC.LineTo(5 + i*rectWidth, 17 + ARRAY_SIZE*rectHeight);

		MemDC.MoveTo(5, 17 + i*rectHeight);
		MemDC.LineTo(5 + ARRAY_SIZE*rectWidth, 17 + i*rectHeight);
	}

	pdc->BitBlt(0, 0, width, height, &MemDC, 0, 0, SRCCOPY);                   //将内存中的图拷贝到屏幕上进行显示

	MemBitmap.DeleteObject();                                                  //绘图完成后的清理
	MemDC.DeleteDC();
}

void CMazeDlg::SetBMPfile(CDC *MemDC, CRect rc, char people)
{
	BITMAPINFO *pBmpInfo;                                                      //记录图像细节
	BYTE *pBmpData;                                                            //图像数据
	BITMAPFILEHEADER bmpHeader;                                                //文件头
	BITMAPINFOHEADER bmpInfo;                                                  //信息头
	CFile bmpFile;                                                             //记录打开文件

	if (people == 'P') {
		if (!bmpFile.Open(_T("res//Cavalier.bmp"), CFile::modeRead | CFile::typeBinary))
			return;
	}
	else if (people == '#') {
		if (!bmpFile.Open(_T("res//Princess.bmp"), CFile::modeRead | CFile::typeBinary))
			return;
	}
	if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//为图像数据申请空间
	memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData, dataBytes);
	bmpFile.Close();

	//显示图像
	StretchDIBits(*MemDC, rc.TopLeft().x, rc.TopLeft().y, rc.Width(), rc.Height(), 0, 0,
		bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
}



void CMazeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	int array_size = _ttoi(str);

	array_size = array_size < 5 ? 5 : array_size;
	array_size = array_size > 30 ? 30 : array_size;

	srand((unsigned)time(NULL));
	if (ARRAY_SIZE != array_size) {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			delete MAP[i];
		}
		delete MAP;
		ARRAY_SIZE = array_size;
		MAP = new char*[ARRAY_SIZE];
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			MAP[i] = new char[ARRAY_SIZE];
		}
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			for (int j = 0; j < ARRAY_SIZE; ++j) {
				MAP[i][j] = (rand() % 100 <= 50) ? '1' : '0';
			}
		}

		Point cavalierPoint;                                                         //骑士所在的位置
		Point princessPoint;                                                         //公主所在的位置
		do{
			cavalierPoint.InsertData(rand() % ARRAY_SIZE, rand() % ARRAY_SIZE);
			princessPoint.InsertData(rand() % ARRAY_SIZE, rand() % ARRAY_SIZE);
		} while (cavalierPoint == princessPoint);
		MAP[cavalierPoint.GetX()][cavalierPoint.GetY()] = 'P';
		MAP[princessPoint.GetX()][princessPoint.GetY()] = '#';
	}
	
	if (ARRAY_SIZE == 10) {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			delete MAP[i];
		}
		delete MAP;
		MAP = new char*[ARRAY_SIZE];
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			MAP[i] = new char[ARRAY_SIZE];
		}
		char initMAP[10][10] = {                                   //定义地图的数据
			{ '1','1','1','1','1','1','1','1','1','1' },
			{ '1','0','0','1','0','0','0','1','0','#' },
			{ '1','0','0','1','0','0','0','1','0','1' },
			{ '1','0','0','0','0','1','1','0','0','1' },
			{ '1','0','1','1','1','0','0','0','0','1' },
			{ '1','0','0','P','1','0','0','0','0','1' },
			{ '1','0','1','0','0','0','1','0','0','1' },
			{ '1','0','1','1','1','0','1','1','0','1' },
			{ '1','1','0','0','0','0','0','0','0','1' },
			{ '1','1','1','1','1','1','1','1','1','1' },
		};
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			for (int j = 0; j < ARRAY_SIZE; ++j) {
				MAP[i][j] = initMAP[i][j];
			}
		}
	}

	DoMaze();
	str.Format(_T("%d"), ARRAY_SIZE);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	InvalidateRect(NULL, true);                                                //设置窗口无效
	UpdateWindow();                                                            //立即重绘，触发WM_PAINT
}


void CMazeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	str.Format(_T("%d"), ARRAY_SIZE);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


void CMazeDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	int array_size = _ttoi(str);


	if (pNMUpDown->iDelta == -1){                                              //如果此值为-1 , 说明点击了Spin的往下的箭头
		array_size -= 1;
	}else if (pNMUpDown->iDelta == 1){                                         //如果此值为1, 说明点击了Spin的往上的箭头
		array_size += 1;
	}
	array_size = array_size < 5 ? 5 : array_size;
	array_size = array_size > 30 ? 30 : array_size;
	*pResult = 0;

	ARRAY_SIZE = array_size;
	str.Format(_T("%d"), ARRAY_SIZE);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	int cavalierPoint_X = _ttoi(str);

	if (cavalierPoint_X < 0 || cavalierPoint_X >= ARRAY_SIZE) {
		cavalierPoint_X = 0;
		str.Format(_T("%d"), cavalierPoint_X);
		GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT4)->GetWindowText(str);
	int cavalierPoint_Y = _ttoi(str);

	if (cavalierPoint_Y < 0 || cavalierPoint_Y >= ARRAY_SIZE) {
		cavalierPoint_Y = 0;
		str.Format(_T("%d"), cavalierPoint_Y);
		GetDlgItem(IDC_EDIT4)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowText(str);
	int PrincessPoint_X = _ttoi(str);

	if (PrincessPoint_X < 0 || PrincessPoint_X >= ARRAY_SIZE) {
		PrincessPoint_X = ARRAY_SIZE - 1;
		str.Format(_T("%d"), PrincessPoint_X);
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}

void CMazeDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowText(str);
	int PrincessPoint_Y = _ttoi(str);

	if (PrincessPoint_Y < 0 || PrincessPoint_Y >= ARRAY_SIZE) {
		PrincessPoint_Y = ARRAY_SIZE - 1;
		str.Format(_T("%d"), PrincessPoint_Y);
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CMazeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	Point cavalierPoint;                                                         //骑士所在的位置
	Point princessPoint;                                                         //公主所在的位置
	
	CString str_x,str_y;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str_x);
	GetDlgItem(IDC_EDIT4)->GetWindowText(str_y);
	cavalierPoint.InsertData(_ttoi(str_x), _ttoi(str_y));
	GetDlgItem(IDC_EDIT5)->GetWindowText(str_x);
	GetDlgItem(IDC_EDIT6)->GetWindowText(str_y);
	princessPoint.InsertData(_ttoi(str_x), _ttoi(str_y));

	if (cavalierPoint == princessPoint) {
	}
	else {
		MAP[CavalierPoint.GetX()][CavalierPoint.GetY()] = MAP[PrincessPoint.GetX()][PrincessPoint.GetY()] = '0';
		CavalierPoint = cavalierPoint;
		PrincessPoint = princessPoint;
		MAP[CavalierPoint.GetX()][CavalierPoint.GetY()] = 'P';
		MAP[PrincessPoint.GetX()][PrincessPoint.GetY()] = '#';
	}
	this->OnBnClickedButton4();
	InvalidateRect(NULL, true);                                                //设置窗口无效
	UpdateWindow();                                                            //立即重绘，触发WM_PAINT
}


void CMazeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	str.Format(_T("%d"), CavalierPoint.GetX());
	GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	str.Format(_T("%d"), CavalierPoint.GetY());
	GetDlgItem(IDC_EDIT4)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetX());
	GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetY());
	GetDlgItem(IDC_EDIT6)->SetWindowText(str);

	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}
