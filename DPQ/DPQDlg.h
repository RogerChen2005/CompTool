
// DPQDlg.h: 头文件
//
#include "vector"
#define REPLACE 0
#define FILEONELONG 1
#define FILETWOLONG 2

struct diff {
	std::vector<int> dif , pos , etp;
	std::vector<char> fir , sec;
};

#pragma once


// CDPQDlg 对话框
class CDPQDlg : public CDialogEx
{
// 构造
public:
	CDPQDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DPQ_DIALOG };
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
	CString file1;
//	CString file2;
//	CString result;
	afx_msg void OnRun();
	CString result;
	CString file2;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	diff comp(CString f1, CString f2);
	afx_msg void OnClear();
	afx_msg void Onhelp();
	afx_msg void OnLogOut();
};

