#pragma once

#include <opencv.hpp>

using namespace cv;


// CCameraThread

class CCameraThread : public CWinThread
{
	DECLARE_DYNCREATE(CCameraThread)

protected:
	CCameraThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CCameraThread();

public:
	CCameraThread(int camID);
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	Mat frame;
	Mat result;
	VideoCapture capture;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFreshFrame(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSaveFrame(WPARAM wParam, LPARAM lParam);
	void mark();
};


