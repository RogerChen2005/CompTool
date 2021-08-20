
// DPQDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DPQ.h"
#include "DPQDlg.h"
#include "afxdialogex.h"
#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CDPQDlg 对话框

CDPQDlg::CDPQDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DPQ_DIALOG, pParent)
	, file1(_T(""))
	, file2(_T(""))
	, result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDPQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, file1);
	//  DDX_Text(pDX, IDC_EDIT2, file2);
	//  DDX_Text(pDX, IDC_EDIT3, result);
	DDX_Text(pDX, IDC_EDIT2, result);
	DDX_Text(pDX, IDC_EDIT3, file2);
}

BEGIN_MESSAGE_MAP(CDPQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDPQDlg::OnRun)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON2, &CDPQDlg::OnClear)
	ON_BN_CLICKED(IDC_BUTTON3, &CDPQDlg::Onhelp)
END_MESSAGE_MAP()


// CDPQDlg 消息处理程序

BOOL CDPQDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDPQDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDPQDlg::OnPaint()
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
HCURSOR CDPQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int c = 1;

void CDPQDlg::OnRun()
{
	// TODO: 在此添加控件通知处理程序代码
	int res = 0;
	CString temp;
	diff filedif = comp(file1, file2);
	temp.Format(_T("%s%d%s\r\n"),_T("result "),c,_T(" :"));
	if (filedif.dif.size() == 0) {
		temp += "    Completely same!\r\n";
	}
	else{
		CString s;
		for (int i = 0; i < filedif.dif.size(); i++) {	
			s.Format(_T("    Different on line %d :\r\n"), filedif.dif[i]);
			temp += s;
			s.Format(_T("           First appear on column %d , File1: %c while File2: %c \r\n"), filedif.pos[i], filedif.fir[i], filedif.sec[i]);
			temp += s;
		}
	}
	UpdateData(TRUE);
	result += temp;
	c++;
	UpdateData(FALSE);
}

bool isFirst = false;

void CDPQDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	WCHAR szFileName[MAX_PATH + 1] = L"";
	UINT  nChars = ::DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
	CString str = szFileName;
	UpdateData(TRUE);
	if (isFirst == false) {
		file1 = szFileName;
		isFirst = true;
	}
	else {
		file2 = szFileName;
		isFirst = false;
	}
	UpdateData(FALSE);
	CDialogEx::OnDropFiles(hDropInfo);
}

diff CDPQDlg::comp(CString f1, CString f2)
{
	diff temp;
	CStdioFile File1, File2;
	File1.Open(file1, CFile::modeRead);
	File2.Open(file2, CFile::modeRead);
	CString str1,str2;
	int cnt = 1;
	while (File1.ReadString(str1)) {
		File2.ReadString(str2);
		str1.TrimRight();
		str2.TrimRight();
		if (str1 == str2) {
		}
		else {
			temp.dif.push_back(cnt);
			for (int i = 0; true; i++) {
				if (str1[i] != str2[i]) {
					temp.pos.push_back(i + 1);
					temp.fir.push_back(str1[i]);
					temp.sec.push_back(str2[i]);
					break;
				}
			}
		}
		cnt++;
	}
	while (File2.ReadString(str2)) {
		temp.dif.push_back(cnt);
		cnt++;
	}
	return temp;
}


void CDPQDlg::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	result = "";
	c = 1;
	UpdateData(FALSE);
}


void CDPQDlg::Onhelp()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg mDlg;
	mDlg.DoModal();
}
