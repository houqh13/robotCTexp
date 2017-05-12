#pragma once

#include <opencv.hpp>


// CCameraThread

class CCameraThread : public CWinThread
{
	DECLARE_DYNCREATE(CCameraThread)

protected:
	CCameraThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCameraThread();

public:
	CCameraThread(int camID);
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	//cv::Mat frame;
	//cv::VideoCapture capture;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFreshFrame(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSaveFrame(WPARAM wParam, LPARAM lParam);
};


