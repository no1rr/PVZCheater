
// PVZCheaterDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PVZCheater.h"
#include "PVZCheaterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPVZCheaterDlg *g_dlg;
HANDLE g_processHandle;

// 将某个值写入植物大战僵尸内存（后面的可变参数是地址链，要以-1结尾）
void WriteMemory(void* value, DWORD valueSize, ...) {
	if (value == NULL || valueSize == 0 || g_processHandle == NULL) return;

	DWORD tempValue = 0;

	va_list addresses;
	va_start(addresses, valueSize);
	DWORD offset = 0;
	DWORD lastAddress = 0;
	while ((offset = va_arg(addresses, DWORD)) != -1) {
		lastAddress = tempValue + offset;
		::ReadProcessMemory(g_processHandle, (LPCVOID)lastAddress, &tempValue, sizeof(DWORD), NULL);
	}
	va_end(addresses);

	::WriteProcessMemory(g_processHandle, (LPVOID)lastAddress, value, valueSize, NULL);
}

void WriteMemory(void* value, DWORD valueSize, DWORD address) {
	WriteMemory(value, valueSize, address, -1);
}


//用来监控的线程
DWORD    monitorThreadFunc(LPVOID  lpThreadParameter) {
	while (1) {
		 
		//获得PVZ窗口句柄
		HWND  gameWindow = FindWindow(CString("MainWindow"), CString("植物大战僵尸中文版"));

		if (gameWindow != NULL) {
			 
			g_dlg->m_bnCd.EnableWindow(TRUE);
			g_dlg->m_bnSun.EnableWindow(TRUE);
			g_dlg->m_bnOut.EnableWindow(TRUE);
			g_dlg->m_bnTime.EnableWindow(TRUE);
			g_dlg->m_bnKill.EnableWindow(TRUE);
			g_dlg->m_bnPlant.EnableWindow(TRUE);
			g_dlg->m_bnZombie.EnableWindow(TRUE);
			g_dlg->m_bnBackground.EnableWindow(TRUE);

			 if (g_processHandle == NULL) {
				//获得PVZ进程ID
				DWORD pid;
				GetWindowThreadProcessId(gameWindow, &pid);
				
				//获得PVZ进程句柄
				g_processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			}
		}
		else  {
			       g_dlg->m_bnBackground.SetCheck(FALSE);
			       g_dlg->m_bnZombie.SetCheck(FALSE);
			       g_dlg->m_bnPlant.SetCheck(FALSE);
				   g_dlg->m_bnKill.SetCheck(FALSE);
				   g_dlg->m_bnTime.SetCheck(FALSE);
				   g_dlg->m_bnOut.SetCheck(FALSE);
			       g_dlg->m_bnSun.SetCheck(FALSE);
			       g_dlg->m_bnCd.SetCheck(FALSE);
			       g_dlg->m_bnCd.EnableWindow(FALSE);
			       g_dlg->m_bnSun.EnableWindow(FALSE);
				   g_dlg->m_bnOut.EnableWindow(FALSE);
				   g_dlg->m_bnTime.EnableWindow(FALSE);
				   g_dlg->m_bnKill.EnableWindow(FALSE);
			       g_dlg->m_bnPlant.EnableWindow(FALSE);
			       g_dlg->m_bnZombie.EnableWindow(FALSE);
			       g_dlg->m_bnBackground.EnableWindow(FALSE);	    
		       }
		
		if (g_dlg->m_bnSun.GetCheck()) {
			DWORD value = 9990;
			WriteMemory(&value, sizeof(value), 0x6A9EC0, 0x320,0x8, 0x0, 0x8, 0x144, 0x2C, 0x5560, -1);

		}
		//睡眠
		Sleep(1000);
	}
	return NULL;
}

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


// CPVZCheaterDlg 对话框



CPVZCheaterDlg::CPVZCheaterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PVZCHEATER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_STUDY);
}

void CPVZCheaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUN ,m_bnSun);
	DDX_Control(pDX, IDC_KILL, m_bnKill);
	DDX_Control(pDX, IDC_WUCD, m_bnCd);
	DDX_Control(pDX, IDC_BACKGROUND, m_bnBackground);
	DDX_Control(pDX, IDC_PLANT, m_bnPlant);
	DDX_Control(pDX, IDC_ZOMBIE, m_bnZombie);
	DDX_Control(pDX, IDC_TIME, m_bnTime);
	DDX_Control(pDX, IDC_OUT, m_bnOut);
}

BEGIN_MESSAGE_MAP(CPVZCheaterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CODE,& CPVZCheaterDlg::OnbtnClickedCode)
	ON_BN_CLICKED(IDC_FOLLOW, &CPVZCheaterDlg::OnbtnClickedFollow)
	ON_BN_CLICKED(IDC_KILL, &CPVZCheaterDlg::OnBnClickedKill)
	ON_BN_CLICKED(IDC_SUN, &CPVZCheaterDlg::OnBnClickedSun)
	ON_BN_CLICKED(IDC_WUCD, &CPVZCheaterDlg::OnBnClickedWucd)
	ON_BN_CLICKED(IDC_PLANT, &CPVZCheaterDlg::OnBnClickedPlant)
	ON_BN_CLICKED(IDC_ZOMBIE, &CPVZCheaterDlg::OnBnClickedZombie)
	ON_BN_CLICKED(IDC_BACKGROUND, &CPVZCheaterDlg::OnBnClickedBackground)
	ON_BN_CLICKED(IDC_TIME, &CPVZCheaterDlg::OnBnClickedTime)
	ON_BN_CLICKED(IDC_OUT, &CPVZCheaterDlg::OnBnClickedOut)
END_MESSAGE_MAP()


// CPVZCheaterDlg 消息处理程序

BOOL CPVZCheaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

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
	//创建一条线程，监控程序是否打开
	//int lpThreadParameter;
	m_MonitorThread = CreateThread(NULL, NULL,monitorThreadFunc, NULL, NULL, NULL);
	g_dlg = this;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPVZCheaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPVZCheaterDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPVZCheaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CPVZCheaterDlg::OnbtnClickedCode() {
	ShellExecute(
		NULL,
		CString("open"),
		CString("https://akie-hub.github.io/PVZCheater/"),
		NULL, NULL,
		SW_SHOWNORMAL
	);
}
void  CPVZCheaterDlg::OnbtnClickedFollow() {
	ShellExecute(
		NULL,
		CString("open"),
		CString("https://user.qzone.qq.com/2845506398?source=grouplist"),
		NULL, NULL,
		SW_SHOWNORMAL
	);
}





void CPVZCheaterDlg::OnBnClickedKill() {
	// TODO: 在此添加控件通知处理程序代码
	//BOOL chcked=IsDlgButtonChecked(IDC_KILL);
	if (m_bnKill.GetCheck()) { // 需要秒杀僵尸
		BYTE data[] = { 0xFF, 0x90, 0x90 };
		WriteMemory(data, sizeof(data), 0x00531310);

		BYTE data1[] = { 0x2B,0xF6,0x2B,0xC9 };
		WriteMemory(data1, sizeof(data1), 0x00531042);
	}
	else { // 不需要秒杀僵尸
		BYTE data[] = { 0x7c, 0x24, 0x20 };
		WriteMemory(data, sizeof(data), 0x00531310);

		BYTE data1[] = { 0x2B,0xF0,0x2B,0xC8 };
		WriteMemory(data1, sizeof(data1), 0x00531042);
	}

}


void CPVZCheaterDlg::OnBnClickedSun() {
	// TODO: 在此添加控件通知处理程序代码
	 
}


void CPVZCheaterDlg::OnBnClickedWucd() {
	// TODO: 在此添加控件通知处理程序代码
}


void CPVZCheaterDlg::OnBnClickedPlant() {
	// TODO: 在此添加控件通知处理程序代码
	if (m_bnPlant.GetCheck()) { // 需要植物不死
		BYTE data[] = { 0x00 };
		WriteMemory(data, sizeof(data), 0x0052FCF3);
	}
	else { // 不需要植物不死
		BYTE data[] = { 0xFC };
		WriteMemory(data, sizeof(data), 0x0052FCF3);
	}
}


void CPVZCheaterDlg::OnBnClickedZombie() {
	// TODO: 在此添加控件通知处理程序代码
}


void CPVZCheaterDlg::OnBnClickedBackground() {
	// TODO: 在此添加控件通知处理程序代码
}


void CPVZCheaterDlg::OnBnClickedTime() {
	// TODO: 在此添加控件通知处理程序代码
	if (m_bnTime.GetCheck()) { // 需要时间静止
		BYTE data[] = { 0x00 };
		WriteMemory(data, sizeof(data), 0x00413E4B);
	}
	else { // 不需要时间静止
		BYTE data[] = { 0xFF };
		WriteMemory(data, sizeof(data), 0x00413E4B);
	}
}


void CPVZCheaterDlg::OnBnClickedOut() {
	// TODO: 在此添加控件通知处理程序代码
	if (m_bnOut.GetCheck()) { // 需要僵尸秒出
		BYTE data[] = { 0xC7,0x87,0x9C,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x90,0x90,0x90,0x90 };
		WriteMemory(data, sizeof(data), 0x00413E45);
	}
	else { // 不需要僵尸秒出
		BYTE data[] = { 0x83,0x87,0x9C,0x55,0x00,0x00,0xFF,0x3B,0xF3,0x8B,0x8F,0x9C,0x55,0x00,0x00 };
		WriteMemory(data, sizeof(data), 0x00413E45);
	}
}
