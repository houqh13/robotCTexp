#pragma once



// ComRcvThread

class ComRcvThread : public CWinThread
{
	DECLARE_DYNCREATE(ComRcvThread)

protected:
	ComRcvThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~ComRcvThread();

public:
	ComRcvThread(CString comName);	//	���г�ʼ�������Ĺ��캯��
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE hCom;
	CString strCom;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
};


