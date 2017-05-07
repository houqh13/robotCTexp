#pragma once

#include "SerialDlg.h"

// CComRcvThread

class CComRcvThread : public CWinThread
{
	DECLARE_DYNCREATE(CComRcvThread)

protected:
	CComRcvThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CComRcvThread();

public:
	CComRcvThread(CString comName);	//	带有初始化参数的构造函数
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE m_hCom;
	CString m_sCom;
	CSerialDlg *m_pSerialDlg;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReceive(WPARAM wParam, LPARAM lParam);
};


