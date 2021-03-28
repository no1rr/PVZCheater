﻿
// PVZCheaterDlg.h: 头文件
//

#pragma once


// CPVZCheaterDlg 对话框
class CPVZCheaterDlg : public CDialogEx
{
// 构造
public:
	CPVZCheaterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PVZCHEATER_DIALOG };
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
	afx_msg void CPVZCheaterDlg::OnbtnClickedCode();
	afx_msg void  CPVZCheaterDlg::OnbtnClickedFollow();
	afx_msg void OnBnClickedKill();
	afx_msg void OnBnClickedSun();
	afx_msg void OnBnClickedWucd();
	afx_msg void OnBnClickedPlant();
	afx_msg void OnBnClickedZombie();
	afx_msg void OnBnClickedBackground();
	HANDLE  m_MonitorThread;
	CButton m_bnKill;
	CButton m_bnSun;
	CButton m_bnPlant;
	CButton m_bnCd;
	CButton m_bnBackground;
	CButton m_bnZombie;
	CButton m_bnTime;
	CButton m_bnOut;
	friend DWORD   monitorThreadFunc(LPVOID);
public:
	afx_msg void OnBnClickedTime();
	afx_msg void OnBnClickedOut();
};
