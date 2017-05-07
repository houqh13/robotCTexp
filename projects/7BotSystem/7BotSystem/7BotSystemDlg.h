
// 7BotSystemDlg.h : 头文件
//

#pragma once

#include "ComRcvThread.h"


// CMy7BotSystemDlg 对话框
class CMy7BotSystemDlg : public CDialogEx
{
// 构造
public:
	CMy7BotSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY7BOTSYSTEM_DIALOG };

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
	CComRcvThread *m_thCom3;
	CComRcvThread *m_thCom4;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonOpenCom3();
	afx_msg void OnBnClickedButtonOpenCom4();
	afx_msg void OnBnClickedButtonCloseCom3();
	afx_msg void OnBnClickedButtonCloseCom4();
	afx_msg LRESULT OnComError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnComSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
