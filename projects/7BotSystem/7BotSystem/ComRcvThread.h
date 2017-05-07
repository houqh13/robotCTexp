#pragma once



// ComRcvThread

class ComRcvThread : public CWinThread
{
	DECLARE_DYNCREATE(ComRcvThread)

protected:
	ComRcvThread();           // 动态创建所使用的受保护的构造函数
	virtual ~ComRcvThread();

public:
	ComRcvThread(CString comName);	//	带有初始化参数的构造函数
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE hCom;
	CString strCom;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
};


