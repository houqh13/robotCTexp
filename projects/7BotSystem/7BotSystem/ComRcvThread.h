#pragma once


// CComRcvThread

class CComRcvThread : public CWinThread
{
	DECLARE_DYNCREATE(CComRcvThread)

protected:
	CComRcvThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CComRcvThread();

public:
	CComRcvThread(CString comName, int ID);	//	带有初始化参数的构造函数
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE m_hCom;
	CString m_sCom;
	char m_sBuffer[256];
	int m_nID;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReceive(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMoveAngle(WPARAM wParam, LPARAM lParam);
	bool m_bMoveFinish;
};


